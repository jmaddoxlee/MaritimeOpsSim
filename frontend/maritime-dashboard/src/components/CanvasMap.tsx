import { useEffect, useRef } from "react";
import type { LiveVesselStore } from "../types/liveStore";
import type { VesselState } from "../types/telemetry";

interface CanvasMapProps {
  liveStoreRef: React.RefObject<LiveVesselStore>;
  selectedVesselId: string | null;
  onSelectVessel: (vesselId: string) => void;
}

interface ProjectedPoint {
  x: number;
  y: number;
}

const WORLD_WIDTH = 400;
const WORLD_HEIGHT = 300;

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
}

function drawVessel(
  context: CanvasRenderingContext2D,
  canvas: HTMLCanvasElement,
  vessel: VesselState,
  isSelected: boolean,
) {
  const point = projectVesselToCanvas(vessel, canvas);

  context.beginPath();
  context.arc(point.x, point.y, isSelected ? 7 : 5, 0, Math.PI * 2);

  if (vessel.isStale) {
    context.fillStyle = "#f97316";
  } else if (isSelected) {
    context.fillStyle = "#facc15";
  } else {
    context.fillStyle = "#38bdf8";
  }

  context.fill();

  const headingRadians = (vessel.heading * Math.PI) / 180;
  const headingLength = isSelected ? 18 : 12;

  context.strokeStyle = vessel.isStale ? "#fed7aa" : "#bae6fd";
  context.lineWidth = 2;
  context.beginPath();
  context.moveTo(point.x, point.y);
  context.lineTo(
    point.x + Math.cos(headingRadians) * headingLength,
    point.y + Math.sin(headingRadians) * headingLength,
  );
  context.stroke();

  if (isSelected) {
    context.strokeStyle = "#facc15";
    context.lineWidth = 2;
    context.beginPath();
    context.arc(point.x, point.y, 12, 0, Math.PI * 2);
    context.stroke();
  }
}

export function CanvasMap({
  liveStoreRef,
  selectedVesselId,
  onSelectVessel,
}: CanvasMapProps) {
  const canvasRef = useRef<HTMLCanvasElement | null>(null);
  const selectedVesselIdRef = useRef<string | null>(selectedVesselId);

  useEffect(() => {
    selectedVesselIdRef.current = selectedVesselId;
  }, [selectedVesselId]);

  useEffect(() => {
    let animationFrameId = 0;

    function render() {
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

      drawGrid(context, canvas);

      const vessels = Array.from(liveStoreRef.current.vesselsById.values());

      for (const vessel of vessels) {
        drawVessel(
          context,
          canvas,
          vessel,
          vessel.vesselId === selectedVesselIdRef.current,
        );
      }

      context.fillStyle = "rgba(226, 232, 240, 0.9)";
      context.font = "14px system-ui";
      context.fillText(`vessels: ${vessels.length}`, 16, 24);

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

    const vessels = Array.from(liveStoreRef.current.vesselsById.values());

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
