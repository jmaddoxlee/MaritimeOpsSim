using System.Net;
using System.Net.Sockets;
using System.Threading.Channels;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class UdpTelemetryReceiver : BackgroundService
{
    private const int defaultUdpPort = 5005;

    private readonly ChannelWriter<UdpTelemetryPacket> _packetWriter;
    private readonly TelemetryMetrics _metrics;
    private readonly ILogger<UdpTelemetryReceiver> _logger;

    private UdpClient? _udpClient;

    public UdpTelemetryReceiver(
        ChannelWriter<UdpTelemetryPacket> packetWriter,
        TelemetryMetrics metrics,
        ILogger<UdpTelemetryReceiver> logger
    )
    {
        _packetWriter = packetWriter;
        _metrics = metrics;
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

                _metrics.IncrementReceived(result.Buffer.Length);

                UdpTelemetryPacket packet = new(
                    result.Buffer,
                    result.RemoteEndPoint,
                    DateTimeOffset.UtcNow
                );

                if (_packetWriter.TryWrite(packet))
                {
                    _metrics.IncrementQueued();
                } 
                else
                {
                    _metrics.IncrementDropped();

                    _logger.LogInformation(
                        "Received UDP packet: bytes={PacketLength}, sender={SenderEndpoint}",
                        result.Buffer.Length,
                        result.RemoteEndPoint
                    );
                }
            }

            _packetWriter.TryComplete();
        } catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested)
        {
            _logger.LogInformation("UDP telemetry receiver stopping.");
            _packetWriter.TryComplete();
        } catch (SocketException exception)
        {
            _packetWriter.TryComplete(exception);
            _logger.LogError(exception, "UDP telemetry receiver failed.");
            throw;
        }
    }

    public override void Dispose()
    {
        _udpClient?.Dispose();
        base.Dispose();
    }
}