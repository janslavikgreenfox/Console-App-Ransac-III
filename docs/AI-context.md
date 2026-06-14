<!--
AI-friendly project context for chatbots and agents.
Generated: 2026-06-14
-->
# AI Context: Console-App-Ransac-III

Purpose
-------
This repository implements RANSAC-based model fitting and a small console application demonstrating usage. It contains a static library (`RansacLibrary`), an executable, and unit tests.

Quick facts
-----------
- Primary build system: CMake (CMakeLists.txt at repo root)
- Platforms: Desktop (Windows dev environment verified in workspace)
- Language: C++ (Visual Studio / MSVC project files present)

Top-level layout
----------------
- `StaticLibrary/` — core library sources and headers; builds `RansacLibrary` (static).
- `Executable/` — small console program that links the static library and produces example output CSVs.
- `tests/` — unit tests (GTest-based) covering table, fitting strategies, and RANSAC behavior.
- `docs/` — documentation and this AI context file.
- `CMakeLists.txt`, `CMakePresets.json` — top-level project configuration and presets.

Key files to inspect
--------------------
- `StaticLibrary/CMakeLists.txt` — lists library sources and exported include directory.
- `StaticLibrary/include/` — public headers; start here to understand the public API (interfaces and models).
- `StaticLibrary/src/` — implementation of column, table, model fitting, and RANSAC strategy.
- `Executable/CMakeLists.txt` and `Executable/src/` — simple runner demonstrating the library API and producing CSV output.
- `tests/` — unit tests; useful entry points for understanding expected behaviors and examples of library usage.

Build & run (developer notes)
-----------------------------
These commands assume a typical CMake workflow on Windows. Adjust generator and build dir as needed.

1. Configure and generate build files:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
```

2. Build the solution (Debug):

```powershell
cmake --build build --config Debug
```

3. Run the executable built under `build/Executable/Debug/` (or via Visual Studio). Example:

```powershell
.\build\Executable\Debug\Executable.exe
```

Run tests
---------
Unit tests are implemented with Google Test (GTest) and compile into test executables. CTest is a test runner integrated with CMake that can invoke those executables when tests are registered with `add_test()` in the build system. Using CTest provides aggregated reporting, filtering, parallel execution, and CI integration.

Run tests with CTest (recommended when using CMake integration):

```powershell
cmake --build build --config Debug --target RUN_TESTS
ctest --test-dir build --output-on-failure
```

Or run the Google Test executable directly (paths vary by build and config). Example:

```powershell
.\build\tests\Debug\test.exe --gtest_filter=*
```

GTest supports its own flags (e.g. `--gtest_filter`, `--gtest_repeat`) which can be useful when running the executable directly.

What to tell an agent when asking for help
-----------------------------------------
- Specify the goal clearly: e.g., "Add a new fit strategy to support polynomial models" or "Find failing tests related to TableBuilder".
- Provide the target scope: file, folder, or component (e.g., `StaticLibrary/src/RANSACFitStrategy.cpp`).
- For build issues, include the exact CMake configure/build output and platform details (Windows + Visual Studio version).

Navigation tips for code changes
-------------------------------
- Start at `StaticLibrary/include/` for public interfaces (e.g., `ILinearModelFitStrategy.h`, `Table.h`).
- Implementation lives in `StaticLibrary/src/` with corresponding filenames (e.g., `RANSACFitStrategy.cpp`).
- Tests in `tests/` show intended behavior and are a good source of regression checks.

Maintenance notes
-----------------
- The static library target is named `RansacLibrary` in CMake; linking targets should refer to this name.
- Keep public headers in `StaticLibrary/include` and export them via `target_include_directories` as PUBLIC.

Contact / provenance
--------------------
Author repository: local workspace `Console-App-Ransac-III` (see root `README.md` for additional notes).

Useful commands summary
-----------------------
- Configure: `cmake -S . -B build -G "Visual Studio 17 2022" -A x64`
- Build: `cmake --build build --config Debug`
- Run tests: `ctest --test-dir build --output-on-failure`

End of context file.
