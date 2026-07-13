using MaritimeOps.Ingestion.Telemetry;

WebApplicationBuilder builder = WebApplication.CreateBuilder(args);

builder.Services.AddHostedService<UdpTelemetryReceiver>();

WebApplication app = builder.Build();

app.MapGet("/", () => "MaritimeOps.Ingestion is running.");

app.MapGet("/heat", () => Results.Ok(new
{
    status = "ok",
    service = "MaritimeOps.Ingestion"
}));

app.Run();
