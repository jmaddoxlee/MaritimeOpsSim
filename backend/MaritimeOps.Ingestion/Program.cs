using MaritimeOps.Ingestion.Telemetry;
using MaritimeOps.Ingestion.WebSockets;
using System.Net.WebSockets;
using System.Threading.Channels;

WebApplicationBuilder builder = WebApplication.CreateBuilder(args);

builder.Services.AddSingleton<TelemetryMetrics>();
builder.Services.AddSingleton<ProtobufPacketDecoder>();
builder.Services.AddSingleton<VesselStateRegistry>();
builder.Services.AddSingleton<TelemetryPacketProcessor>();
builder.Services.AddSingleton<WebSocketClientManager>();

builder.Services.AddSingleton(_ => 
    Channel.CreateBounded<UdpTelemetryPacket>(
        new BoundedChannelOptions(10_000)
        {
            FullMode = BoundedChannelFullMode.Wait,
            SingleReader = true,
            SingleWriter = true
        }
    )
);

builder.Services.AddSingleton(serviceProvider =>
    serviceProvider.GetRequiredService<Channel<UdpTelemetryPacket>>().Reader
);

builder.Services.AddSingleton(serviceProvider =>
    serviceProvider.GetRequiredService<Channel<UdpTelemetryPacket>>().Writer
);

builder.Services.AddHostedService<UdpTelemetryReceiver>();
builder.Services.AddHostedService<TelemetryDecoderWorker>();
builder.Services.AddHostedService<TelemetryMetricsReporter>();
builder.Services.AddHostedService<WebSocketTelemetryBroadcaster>();

WebApplication app = builder.Build();

app.UseWebSockets();

app.Map(
    "/ws/telemetry",
    async (
        HttpContext context,
        WebSocketClientManager webSocketClientManager
    ) =>
    {
        if (!context.WebSockets.IsWebSocketRequest)
        {
            context.Response.StatusCode = StatusCodes.Status400BadRequest;
            await context.Response.WriteAsync("WebSocket request expected.");
            return;
        }

        using WebSocket webSocket =
            await context.WebSockets.AcceptWebSocketAsync();

        Guid clientId = webSocketClientManager.AddClient(webSocket);

        await webSocketClientManager.ReceiveUntilClosedAsync(
            clientId,
            webSocket,
            context.RequestAborted
        );
    }
);

app.MapGet("/", () => "MaritimeOps.Ingestion is running.");

app.MapGet("/health", () => Results.Ok(new
{
    status = "ok",
    service = "MaritimeOps.Ingestion"
}));

app.MapGet("/metrics", (
    TelemetryMetrics metrics,
    VesselStateRegistry vesselStateRegistry,
    WebSocketClientManager webSocketClientManager
) => Results.Ok(new
{
    packetsReceived = metrics.ReceivedPackets,
    packetsDecoded = metrics.DecodedPackets,
    badPackets = metrics.BadPackets,
    droppedPackets = metrics.DroppedPackets,
    receivedBytes = metrics.ReceivedBytes,
    queuedPackets = metrics.QueuedPackets,
    trackedVesselCount = vesselStateRegistry.TrackedVesselCount,
    activeVesselCount = vesselStateRegistry.ActiveVesselCount,
    staleVesselCount = vesselStateRegistry.GetStaleVesselCount(DateTimeOffset.UtcNow),
    stateUpdateCount = vesselStateRegistry.StateUpdateCount,
    connectedClients = webSocketClientManager.ConnectedClientCount
}));

app.MapGet("/vessels", (
    VesselStateRegistry vesselStateRegistry
) => Results.Ok(
    vesselStateRegistry.GetSnapshotWithStaleStatus(DateTimeOffset.UtcNow)
));

app.Run();
