# adas-perception-core

Camera perception pipeline: object detection, classification, tracking, free space.

## Build

```bash
git submodule update --init
mkdir build && cd build
cmake .. -DTARGET_TYPE=sil -DBUILD_TESTING=ON -DAdasInterfaces_DIR=../interfaces/cmake
cmake --build .
ctest
```

When using the 1v-superproject checkout, `AdasInterfaces_DIR` is usually `../../interfaces/cmake` from `modules/perception-core/build`.

## Layout

- `src/component/` — Middleware-agnostic algorithm code (detection, tracking, …)
- `src/platform/sil/` — SIL (ROS2) node wrappers
- `src/platform/standalone/` — File-based executables for bring-up
- `src/platform/autosar/` — Adaptive AUTOSAR service adapters
- `src/platform/tda4vm/`, `src/platform/orin/` — SoC placeholders (see README in each)
- `src/project/` — Project-specific configs, feature macros, calibration overrides (see README)
- `include/` — Component-internal headers
- `tests/` — Unit and integration tests
- `config/` — Default configuration YAML

## Interfaces implemented

- `IObjectDetector` — from interfaces
- `IObjectTracker` — from interfaces
- `IFreeSpaceDetector` — from interfaces

## Windows quick build

From this directory (Git Bash or `cmd`):

- `build_sil.bat` — `TARGET_TYPE=sil` → `build-sil/`
- `build_standalone.bat` — `TARGET_TYPE=standalone` → `build-standalone/` and `perception_standalone.exe`

Scripts resolve `AdasInterfaces_DIR` automatically for superproject (`modules/interfaces`) or a sibling `interfaces` clone.
