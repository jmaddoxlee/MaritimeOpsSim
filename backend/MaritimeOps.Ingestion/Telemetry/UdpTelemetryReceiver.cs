using System.Net;
using System.Net.Sockets;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class UdpTelemetryReceiver : BackgroundService
{
    private const int defaultUdpPort = 5005;

    private readonly ILogger<UdpTelemetryReceiver> _logger;

    private UdpClient? _udpClient;

    public UdpTelemetryReceiver(ILogger<UdpTelemetryReceiver> logger)
    {
        _logger = logger;
    } 

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        _udpClient = new UdpClient(new IPEndPoint(IPAddress.Any, defaultUdpPort));

        _logger.LogInformation(
             "UDP telemetry receiver listening on port {Port}",
             defaultUdpPort
        );

        try
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                UdpReceiveResult result = await _udpClient.ReceiveAsync(stoppingToken); 

                _logger.LogInformation(
                    "Received UDP packet: bytes={PacketLength}, sender={SenderEndpoint}",
                    result.Buffer.Length,
                    result.RemoteEndPoint
                );
            }
        } catch (OperationCanceledException)
        {
            _logger.LogInformation("UDP telemetry receiver stopping.");
        } catch (SocketException exception)
        {
            _logger.LogError(
                exception,
                 "UDP telemetry receiver socket error."
            );
        }
    }

    public override void Dispose()
    {
        _udpClient?.Dispose();
        base.Dispose();
    }
}