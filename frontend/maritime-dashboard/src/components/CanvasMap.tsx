import { useEffect, useRef } from "react";
import type { RefObject } from "react";
import type { LiveVesselStore } from "../types/liveStore";
import type { VesselState } from "../types/telemetry";
import {
  getVesselStatusLabel,
  hasRestrictedZoneWarning,
  isLowFuel,
  isSignalDegraded,
} from "../utils/telemetryStatus";

interface CanvasMapProps {
  liveStoreRef: RefObject<LiveVesselStore>;
  selectedVesselId: string | null;
  onSelectVessel: (vesselId: string) => void;
}

interface ProjectedPoint {
  x: number;
  y: number;
}

interface Viewport {
  minX: number;
  maxX: number;
  minY: number;
  maxY: number;
}

const WORLD_WIDTH = 400;
const WORLD_HEIGHT = 300;

const MAP_VIEWPORT: Viewport = {
  minX: 0,
  maxX: WORLD_WIDTH,
  minY: 0,
  maxY: WORLD_HEIGHT,
};

function isVesselInsideViewport(vessel: VesselState, viewport: Viewport) {
  return (
    vessel.x >= viewport.minX &&
    vessel.x <= viewport.maxX &&
    vessel.y >= viewport.minY &&
    vessel.y <= viewport.maxY
  );
}

function projectVesselToCanvas(
  vessel: VesselState,
  canvas: HTMLCanvasElement,
): ProjectedPoint {
  const padding = 32;

  const usableWidth = canvas.width - padding * 2;
  const usableHeight = canvas.height - padding * 2;

  return {
    x: padding + (vessel.x / WORLD_WIDTH) * usableWidth,
    y: padding + (vessel.y / WORLD_HEIGHT) * usableHeight,
  };
}

function getVesselColor(vessel: VesselState, isSelected: boolean): string {
  if (isSelected) {
    return "#facc15";
  }

  if (vessel.isStale) {
    return "#f97316";
  }

  if (hasRestrictedZoneWarning(vessel)) {
    return "#ef4444";
  }

  if (isLowFuel(vessel)) {
    return "#fb7185";
  }

  if (isSignalDegraded(vessel)) {
    return "#a78bfa";
  }

  return "#38bdf8";
}

function drawGrid(
  context: CanvasRenderingContext2D,
  canvas: HTMLCanvasElement,
) {
  context.fillStyle = "#07111f";
  context.fillRect(0, 0, canvas.width, canvas.height);

  context.strokeStyle = "rgba(148, 163, 184, 0.18)";
  context.lineWidth = 1;

  for (let x = 0; x <= canvas.width; x += 50) {
    context.beginPath();
    context.moveTo(x, 0);
    context.lineTo(x, canvas.height);
    context.stroke();
  }

  for (let y = 0; y <= canvas.height; y += 50) {
    context.beginPath();
    context.moveTo(0, y);
    context.lineTo(canvas.width, y);
    context.stroke();
  }

  context.fillStyle = "rgba(125, 211, 252, 0.08)";
  context.fillRect(32, 32, canvas.width - 64, canvas.height - 64);

  context.strokeStyle = "rgba(125, 211, 252, 0.35)";
  context.strokeRect(32, 32, canvas.width - 64, canvas.height - 64);

  context.fillStyle = "rgba(226, 232, 240, 0.65)";
  context.font = "12px system-ui";
  context.fillText("simulation map viewport", 42, canvas.height - 42);
}

function drawVessel(
  context: CanvasRenderingContext2D,
  canvas: HTMLCanvasElement,
  vessel: VesselState,
  isSelected: boolean,
) {
  const point = projectVesselToCanvas(vessel, canvas);
  const color = getVesselColor(vessel, isSelected);

  const headingRadians = (vessel.heading * Math.PI) / 180;
  const headingLength = isSelected ? 22 : 15;

  context.strokeStyle = color;
  context.lineWidth = isSelected ? 3 : 2;
  context.beginPath();
  context.moveTo(point.x, point.y);
  context.lineTo(
    point.x + Math.cos(headingRadians) * headingLength,
    point.y + Math.sin(headingRadians) * headingLength,
  );
  context.stroke();

  context.beginPath();
  context.arc(point.x, point.y, isSelected ? 7 : 5, 0, Math.PI * 2);
  context.fillStyle = color;
  context.fill();

  if (vessel.isStale) {
    context.strokeStyle = "rgba(251, 146, 60, 0.9)";
    context.lineWidth = 2;
    context.setLineDash([4, 4]);
    context.beginPath();
    context.arc(point.x, point.y, 11, 0, Math.PI * 2);
    context.stroke();
    context.setLineDash([]);
  }

  if (isSelected) {
    context.strokeStyle = "#facc15";
    context.lineWidth = 2;
    context.beginPath();
    context.arc(point.x, point.y, 15, 0, Math.PI * 2);
    context.stroke();

    context.fillStyle = "rgba(250, 204, 21, 0.95)";
    context.font = "13px system-ui";
    context.fillText(vessel.vesselId, point.x + 12, point.y - 12);
  }
}

function drawLegend(context: CanvasRenderingContext2D) {
  const items = [
    ["active", "#38bdf8"],
    ["selected", "#facc15"],
    ["stale", "#f97316"],
    ["low fuel", "#fb7185"],
    ["signal", "#a78bfa"],
    ["restricted", "#ef4444"],
  ];

  const startX = 16;
  let y = 48;

  context.font = "12px system-ui";

  for (const [label, color] of items) {
    context.fillStyle = color;
    context.beginPath();
    context.arc(startX, y - 4, 5, 0, Math.PI * 2);
    context.fill();

    context.fillStyle = "rgba(226, 232, 240, 0.85)";
    context.fillText(label, startX + 14, y);

    y += 18;
  }
}

function drawDebugOverlay(
  context: CanvasRenderingContext2D,
  fps: number,
  drawnVessels: number,
  totalVessels: number,
) {
  context.fillStyle = "rgba(15, 23, 42, 0.72)";
  context.fillRect(12, 12, 190, 24);

  context.fillStyle = "rgba(226, 232, 240, 0.92)";
  context.font = "13px system-ui";
  context.fillText(
    `FPS: ${fps} | drawn: ${drawnVessels}/${totalVessels}`,
    20,
    29,
  );
}

export function CanvasMap({
  liveStoreRef,
  selectedVesselId,
  onSelectVessel,
}: CanvasMapProps) {
  const canvasRef = useRef<HTMLCanvasElement | null>(null);
  const selectedVesselIdRef = useRef<string | null>(selectedVesselId);

  const fpsRef = useRef(0);
  const frameCountRef = useRef(0);
  const lastFpsUpdateRef = useRef(performance.now());

  useEffect(() => {
    selectedVesselIdRef.current = selectedVesselId;
  }, [selectedVesselId]);

  useEffect(() => {
    let animationFrameId = 0;

    function render(now: number) {
      const canvas = canvasRef.current;

      if (!canvas) {
        animationFrameId = window.requestAnimationFrame(render);
        return;
      }

      const context = canvas.getContext("2d");

      if (!context) {
        animationFrameId = window.requestAnimationFrame(render);
        return;
      }

      frameCountRef.current += 1;

      if (now - lastFpsUpdateRef.current >= 1000) {
        fpsRef.current = frameCountRef.current;
        frameCountRef.current = 0;
        lastFpsUpdateRef.current = now;
      }

      drawGrid(context, canvas);

      const allVessels = Array.from(liveStoreRef.current.vesselsById.values());

      const visibleVessels = allVessels.filter((vessel) =>
        isVesselInsideViewport(vessel, MAP_VIEWPORT),
      );

      for (const vessel of visibleVessels) {
        drawVessel(
          context,
          canvas,
          vessel,
          vessel.vesselId === selectedVesselIdRef.current,
        );
      }

      drawLegend(context);

      drawDebugOverlay(
        context,
        fpsRef.current,
        visibleVessels.length,
        allVessels.length,
      );

      animationFrameId = window.requestAnimationFrame(render);
    }

    animationFrameId = window.requestAnimationFrame(render);

    return () => {
      window.cancelAnimationFrame(animationFrameId);
    };
  }, [liveStoreRef]);

  function handleCanvasClick(event: React.MouseEvent<HTMLCanvasElement>) {
    const canvas = canvasRef.current;

    if (!canvas) {
      return;
    }

    const rect = canvas.getBoundingClientRect();

    const scaleX = canvas.width / rect.width;
    const scaleY = canvas.height / rect.height;

    const clickX = (event.clientX - rect.left) * scaleX;
    const clickY = (event.clientY - rect.top) * scaleY;

    const vessels = Array.from(
      liveStoreRef.current.vesselsById.values(),
    ).filter((vessel) => isVesselInsideViewport(vessel, MAP_VIEWPORT));

    let nearestVessel: VesselState | null = null;
    let nearestDistance = Number.POSITIVE_INFINITY;

    for (const vessel of vessels) {
      const point = projectVesselToCanvas(vessel, canvas);

      const distance = Math.hypot(point.x - clickX, point.y - clickY);

      if (distance < nearestDistance) {
        nearestDistance = distance;
        nearestVessel = vessel;
      }
    }

    if (nearestVessel && nearestDistance <= 18) {
      onSelectVessel(nearestVessel.vesselId);
    }
  }

  return (
    <div className="map-shell">
      <canvas
        ref={canvasRef}
        className="map-canvas"
        width={900}
        height={560}
        onClick={handleCanvasClick}
      />
    </div>
  );
}
