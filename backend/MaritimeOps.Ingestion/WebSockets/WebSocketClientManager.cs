using System.Collections.Concurrent;
using System.Net.WebSockets;
using System.Text;
using System.Text.Json;

namespace MaritimeOps.Ingestion.WebSockets;

public sealed class WebSocketClientManager
{
    private readonly ConcurrentDictionary<Guid, WebSocket> _clients = new();

    private readonly JsonSerializerOptions _jsonOptions = new()
    {
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase
    };

    private readonly ILogger<WebSocketClientManager> _logger;

    public WebSocketClientManager(ILogger<WebSocketClientManager> logger)
    {
        _logger = logger;
    }

    public int ConnectedClientCount => _clients.Count;

    public Guid AddClient(WebSocket webSocket)
    {
        Guid clientId = Guid.NewGuid();

        _clients.TryAdd(clientId, webSocket);

        _logger.LogInformation(
            "WebSocket client connected. clientId={ClientId}, connectedClients={ConnectedClientCount}",
            clientId,
            ConnectedClientCount
        );

        return clientId;
    }

    public async Task ReceiveUntilClosedAsync(
        Guid clientId,
        WebSocket webSocket,
        CancellationToken cancellationToken
    )
    {
        byte[] buffer = new byte[4096];

        try
        {
            while (
                webSocket.State == WebSocketState.Open &&
                !cancellationToken.IsCancellationRequested
            )
            {
                WebSocketReceiveResult result = await webSocket.ReceiveAsync(
                    buffer,
                    cancellationToken
                );

                if (result.MessageType == WebSocketMessageType.Close)
                {
                    break;
                }
            }
        }
        catch (OperationCanceledException) when (cancellationToken.IsCancellationRequested)
        {
            // Normal shutdown.
        }
        catch (WebSocketException exception)
        {
            _logger.LogWarning(
                exception,
                "WebSocket client disconnected unexpectedly. clientId={ClientId}",
                clientId
            );
        }
        finally
        {
            RemoveClient(clientId);

            if (webSocket.State == WebSocketState.Open ||
                webSocket.State == WebSocketState.CloseReceived)
            {
                await webSocket.CloseAsync(
                    WebSocketCloseStatus.NormalClosure,
                    "Closing",
                    CancellationToken.None
                );
            }
        }
    }

    public async Task BroadcastAsync(
        object message,
        CancellationToken cancellationToken
    )
    {
        string json = JsonSerializer.Serialize(message, _jsonOptions);
        byte[] payload = Encoding.UTF8.GetBytes(json);

        foreach ((Guid clientId, WebSocket webSocket) in _clients.ToArray())
        {
            if (webSocket.State != WebSocketState.Open)
            {
                RemoveClient(clientId);
                continue;
            }

            try
            {
                await webSocket.SendAsync(
                    payload,
                    WebSocketMessageType.Text,
                    endOfMessage: true,
                    cancellationToken
                );
            }
            catch (Exception exception) when (
                exception is WebSocketException ||
                exception is OperationCanceledException ||
                exception is ObjectDisposedException
            )
            {
                _logger.LogWarning(
                    exception,
                    "Failed to send WebSocket message. Removing client. clientId={ClientId}",
                    clientId
                );

                RemoveClient(clientId);
            }
        }
    }

    private void RemoveClient(Guid clientId)
    {
        if (_clients.TryRemove(clientId, out _))
        {
            _logger.LogInformation(
                "WebSocket client removed. clientId={ClientId}, connectedClients={ConnectedClientCount}",
                clientId,
                ConnectedClientCount
            );
        }
    }
}