using MaritimeOps.Ingestion.Telemetry;

namespace MaritimeOps.Ingestion.Tests;

public sealed class TelemetryMetricsTests
{
    [Fact]
    public void MetricsCountersIncrement()
    {
        TelemetryMetrics metrics = new();

        metrics.IncrementReceived(72);
        metrics.IncrementQueued();
        metrics.IncrementDecoded();
        metrics.IncrementBadPacket();
        metrics.IncrementDropped();

        Assert.Equal(1, metrics.ReceivedPackets);
        Assert.Equal(72, metrics.ReceivedBytes);
        Assert.Equal(1, metrics.QueuedPackets);
        Assert.Equal(1, metrics.DecodedPackets);
        Assert.Equal(1, metrics.BadPackets);
        Assert.Equal(1, metrics.DroppedPackets);
    }
}