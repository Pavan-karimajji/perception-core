# Perception Core Protobuf + Conan Integration Handoff

## Goal Completed

Implemented protobuf interface generation from `modules/interfaces` and wired `perception-core` to build successfully for:

- `sil`
- `standalone`
- `gtest` (including test execution)

Also switched dependency flow to use Conan-cached protobuf by default (no repeated full protobuf source build in normal workflow).

---

## Final Build Status

Verified successfully with:

- `build_sil.bat` -> PASS
- `build_standalone.bat` -> PASS
- `build_gtest.bat` -> PASS (`2/2` tests passed)

`standalone` executable verified:

- `build-standalone/src/platform/standalone/Release/perception_standalone.exe`

---

## Key Implementation Changes

## 1) Interfaces protobuf generation expanded

File:

- `modules/interfaces/CMakeLists.txt`

Updated generated proto set:

- `proto/common/common.proto`
- `proto/isp/frame.proto`
- `proto/perception/detection.proto`
- `proto/perception/track.proto`
- `proto/perception/free_space.proto`

This ensures all types used by perception component/standalone/tests are generated.

---

## 2) `find_package(AdasInterfaces)` now builds interfaces target in dev-tree

File:

- `modules/interfaces/cmake/AdasInterfacesConfig.cmake`

Added logic to `add_subdirectory()` `modules/interfaces` from consumer projects when `adas-interfaces` target is not already present.  
Effect: `perception-core` resolves `AdasInterfaces::AdasInterfaces` and gets generated protobuf artifacts without manual prebuild step.

---

## 3) Protobuf generation logic (`proto_generate.cmake`) reworked

File:

- `modules/interfaces/cmake/proto_generate.cmake`

Major updates:

- Default mode: prebuilt protobuf only (`ADAS_FETCH_PROTOBUF=OFF`)
- Optional fallback: source fetch/build only if `-DADAS_FETCH_PROTOBUF=ON`
- Added Conan-aware resolution order and target mapping
- Forced `protoc` selection from Conan build context when available (`protobuf_BUILD::protoc`)
- Added compatibility aliasing for target naming differences (`protobuf::protobuf` vs `protobuf::libprotobuf`)

Outcome:

- No mandatory protobuf source rebuild for normal development
- Better control of `protoc`/runtime pairing

---

## 4) Conan dependency management added for perception-core

File:

- `modules/perception-core/conanfile.py`

Implemented Conan 2 recipe with:

- `requires = ("protobuf/3.21.12",)`
- `tool_requires = ("protobuf/3.21.12",)`
- custom `generate()` using:
  - `CMakeToolchain`
  - `CMakeDeps` with build-context activation for protobuf:
    - `build_context_activated = ["protobuf"]`
    - `build_context_suffix = {"protobuf": "_BUILD"}`

Purpose:

- Host/runtime protobuf libs from Conan cache
- Build-tool `protoc` from Conan cache
- Avoid random system `protoc`/header mismatches

---

## 5) Build scripts updated to use Conan toolchain and cache

Files:

- `modules/perception-core/build_sil.bat`
- `modules/perception-core/build_standalone.bat`
- `modules/perception-core/build_gtest.bat`

Changes:

- run `conan install .. --output-folder . --build=missing -s build_type=Release`
- configure with Conan toolchain:
  - `-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake`
- use `cmake --fresh` to avoid stale cached configure state
- explicitly set expected testing mode in scripts
  - SIL/standalone: `BUILD_TESTING=OFF`
  - gtest: `BUILD_TESTING=ON`

Extra in standalone script:

- cleans stale generated interfaces folder before configure:
  - `_deps\adas-interfaces\generated`

---

## 6) Perception-core source cleanup to use real protobuf types

Updated sources removed dependency on temporary stubs where required:

- `src/component/detection/CameraDetector.cpp`
- `src/component/tracking/MultiObjectTracker.cpp`
- `src/component/free_space/FreeSpaceDetector.cpp`
- `tests/unit/test_detector.cpp`
- `tests/unit/test_tracker.cpp`
- `src/platform/standalone/main.cpp`

Notable standalone fix:

- removed `proto_stubs.hpp` include
- added required generated headers:
  - `isp/frame.pb.h`
  - `perception/track.pb.h`
  - `perception/free_space.pb.h`

This resolved MSVC unresolved externals and incomplete-type errors.

---

## 7) Conan cache behavior (what to expect)

- First-time dependency install/build may take time (protobuf/zlib package build/download).
- Subsequent builds are faster and reuse cache under:
  - `C:\Users\Pavan\.conan2\...`

---

## Known IDE/IntelliSense Note

If `.bat` builds pass but Visual Studio shows many `Error (active)` protobuf include/version errors:

- usually IntelliSense context mismatch (e.g., wrong solution/configuration)
- use the generated solution under the configured build dir:
  - `modules/perception-core/build-standalone/adas-perception-core.sln`
- use `x64 + Release` (the scripts build Release)

These editor-only active errors do not necessarily reflect compiler errors.

---

## Commands for Tomorrow

From `modules/perception-core`:

1. `build_sil.bat`
2. `build_standalone.bat`
3. `build_gtest.bat`

Run executable:

1. `build-standalone\src\platform\standalone\Release\perception_standalone.exe`

---

## Files Changed in This Integration

- `modules/interfaces/CMakeLists.txt`
- `modules/interfaces/cmake/AdasInterfacesConfig.cmake`
- `modules/interfaces/cmake/proto_generate.cmake`
- `modules/perception-core/conanfile.py`
- `modules/perception-core/build_sil.bat`
- `modules/perception-core/build_standalone.bat`
- `modules/perception-core/build_gtest.bat`
- `modules/perception-core/src/component/detection/CameraDetector.cpp`
- `modules/perception-core/src/component/tracking/MultiObjectTracker.cpp`
- `modules/perception-core/src/component/free_space/FreeSpaceDetector.cpp`
- `modules/perception-core/src/platform/standalone/main.cpp`
- `modules/perception-core/tests/unit/test_detector.cpp`
- `modules/perception-core/tests/unit/test_tracker.cpp`

---

## Suggested Next Work (optional)

- Add a dedicated Debug workflow (`-s build_type=Debug`) if Debug IDE use is required daily.
- Reduce gtest fetch warning noise by setting `DOWNLOAD_EXTRACT_TIMESTAMP` in test `FetchContent`.
- Migrate protobuf version from `3.21.12` when project is ready (current works but upstream marks protobuf 3.x legacy).
