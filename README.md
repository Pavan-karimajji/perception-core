# adas-perception-core

Camera perception pipeline: object detection, classification, tracking, free space.

## Build

```bash
# Standalone SIL build
git submodule update --init   # pulls adas-interfaces
mkdir build && cd build
cmake .. -DTARGET_TYPE=sil -DBUILD_TESTING=ON
make -j$(nproc)
ctest
```

## Structure
- `src/detection/` — Object detection (ML-based)
- `src/classification/` — Object classification
- `src/tracking/` — Multi-object tracking (Kalman + Hungarian)
- `src/free_space/` — Free space detection
- `adapters/` — Middleware wrappers (ros2, autosar, standalone)
- `tests/` — Unit and integration tests
- `config/` — Default configuration YAML

## Interfaces implemented
- `IObjectDetector` — from adas-interfaces
- `IObjectTracker` — from adas-interfaces
- `IFreeSpaceDetector` — from adas-interfaces
