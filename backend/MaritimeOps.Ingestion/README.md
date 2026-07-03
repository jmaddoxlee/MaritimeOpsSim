# MaritimeOps.Ingestion

C#/.NET ingestion layer for MaritimeOpsSim.

This service will receive C++ simulation telemetry over UDP, decode telemetry packets, maintain latest vessel state, broadcast live updates over WebSockets, and eventually persist telemetry to TimescaleDB.
