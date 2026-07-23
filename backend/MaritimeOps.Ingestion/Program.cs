using MaritimeOps.Ingestion.Telemetry;
using System.Threading.Channels;

WebApplicationBuilder builder = WebApplication.CreateBuilder(args);

builder.Services.AddSingleton<TelemetryMetrics>();
builder.Services.AddSingleton<ProtobufPacketDecoder>();
builder.Services.AddSingleton<VesselStateRegistry>();
builder.Services.AddSingleton<TelemetryPacketProcessor>();

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

WebApplication app = builder.Build();

app.MapGet("/", () => "MaritimeOps.Ingestion is running.");

app.MapGet("/health", () => Results.Ok(new
{
    status = "ok",
    service = "MaritimeOps.Ingestion"
}));

app.MapGet("/metrics", (
    TelemetryMetrics metrics,
    VesselStateRegistry vesselStateRegistry
) => Results.Ok(new
{
    receivedPackets = metrics.ReceivedPackets,
    receivedBytes = metrics.ReceivedBytes,
    queuedPackets = metrics.QueuedPackets,
    decodedPackets = metrics.DecodedPackets,
    badPackets = metrics.BadPackets,
    droppedPackets = metrics.DroppedPackets,
    activeVesselCount = vesselStateRegistry.ActiveVesselCount,
    stateUpdateCount = vesselStateRegistry.StateUpdateCount
}));

app.MapGet("/vessels", (
    VesselStateRegistry vesselStateRegistry
) => Results.Ok(vesselStateRegistry.GetSnapshot()));

app.Run();
