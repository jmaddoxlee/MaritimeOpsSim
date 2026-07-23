namespace MaritimeOps.Ingestion.Telemetry;

public sealed class TelemetryMetrics
{
    private long _receivedPackets;
    private long _receivedBytes;
    private long _queuedPackets;
    private long _decodedPackets;
    private long _badPackets;
    private long _droppedPackets;

    public long ReceivedPackets => Interlocked.Read(ref _receivedPackets);
    public long ReceivedBytes => Interlocked.Read(ref _receivedBytes);
    public long QueuedPackets => Interlocked.Read(ref _queuedPackets);
    public long DecodedPackets => Interlocked.Read(ref _decodedPackets);
    public long BadPackets => Interlocked.Read(ref _badPackets);
    public long DroppedPackets => Interlocked.Read(ref _droppedPackets);

    public void IncrementReceived(int byteCount)
    {
        Interlocked.Increment(ref _receivedPackets);
        Interlocked.Add(ref _receivedBytes, byteCount);
    }

    public void IncrementQueued()
    {
        Interlocked.Increment(ref _queuedPackets);
    }

    public void IncrementDecoded()
    {
        Interlocked.Increment(ref _decodedPackets);
    }

    public void IncrementBadPacket()
    {
        Interlocked.Increment(ref _badPackets);
    }

    public void IncrementDropped()
    {
        Interlocked.Increment(ref _droppedPackets);
    }
}