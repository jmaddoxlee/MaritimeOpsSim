import { useEffect, useRef, useState } from "react";
import type {
  ConnectionStatus,
  TelemetryMessage,
  TelemetrySnapshot,
} from "../types/telemetry";
import type { LiveVesselStore } from "../types/liveStore";

const DEFAULT_WS_URL = "ws://localhost:5048/ws/telemetry";

function getWebSocketUrl(): string {
  return import.meta.env.VITE_TELEMETRY_WS_URL ?? DEFAULT_WS_URL;
}

function isSnapshot(message: TelemetryMessage): message is TelemetrySnapshot {
  return message.type === "snapshot";
}

export function useTelemetrySocket() {
  const liveStoreRef = useRef<LiveVesselStore>({
    vesselsById: new Map(),
    lastSnapshotTimeUtc: null,
    activeVesselCount: 0,
    staleVesselCount: 0,
    connectedClientCount: 0,
  });

  const socketRef = useRef<WebSocket | null>(null);
  const reconnectTimerRef = useRef<number | null>(null);
  const shouldReconnectRef = useRef(true);

  const [connectionStatus, setConnectionStatus] =
    useState<ConnectionStatus>("connecting");

  const [renderCount, setRenderCount] = useState(0);

  useEffect(() => {
    shouldReconnectRef.current = true;

    function connect(status: ConnectionStatus = "connecting") {
      setConnectionStatus(status);

      const socket = new WebSocket(getWebSocketUrl());
      socketRef.current = socket;

      socket.onopen = () => {
        setConnectionStatus("connected");
      };

      socket.onmessage = (event) => {
        try {
          const message = JSON.parse(event.data) as TelemetryMessage;

          if (isSnapshot(message)) {
            liveStoreRef.current.lastSnapshotTimeUtc = message.timestampUtc;
            liveStoreRef.current.activeVesselCount = message.activeVesselCount;
            liveStoreRef.current.staleVesselCount = message.staleVesselCount;

            for (const vessel of message.vessels) {
              liveStoreRef.current.vesselsById.set(vessel.vesselId, vessel);
            }

            return;
          }

          if (message.type === "heartbeat") {
            liveStoreRef.current.connectedClientCount =
              message.connectedClientCount;
          }
        } catch (error) {
          console.error("Failed to parse telemetry message", error);
        }
      };

      socket.onerror = () => {
        setConnectionStatus("disconnected");
      };

      socket.onclose = () => {
        socketRef.current = null;

        if (!shouldReconnectRef.current) {
          setConnectionStatus("disconnected");
          return;
        }

        setConnectionStatus("reconnecting");

        reconnectTimerRef.current = window.setTimeout(() => {
          connect("reconnecting");
        }, 1000);
      };
    }

    connect();

    const uiRefreshTimer = window.setInterval(() => {
      // This is intentionally low-frequency React state.
      // Live telemetry remains in liveStoreRef so every packet does not cause a React render.
      setRenderCount((current) => current + 1);
    }, 250);

    return () => {
      shouldReconnectRef.current = false;

      if (reconnectTimerRef.current !== null) {
        window.clearTimeout(reconnectTimerRef.current);
      }

      window.clearInterval(uiRefreshTimer);

      socketRef.current?.close();
    };
  }, []);

  return {
    liveStoreRef,
    connectionStatus,
    renderCount,
  };
}
