# Gaze Engine
Gaze Engine is a tiny game engine.

## Prerequisites

To build Gaze, you must first install the following tools.

### Windows 10/11
- Visual Studio 2019 (or more recent)
- CMake 3.23 (or more recent)
- Git 2.1 (or more recent)

[//]: # (### macOS >= 10.15 &#40;x86_64&#41;)

[//]: # (- Xcode 12.3 &#40;or more recent&#41;)

[//]: # (- CMake 3.19 &#40;or more recent&#41;)

[//]: # (- Git 2.1 &#40;or more recent&#41;)

[//]: # (## Build Gaze)

[//]: # ()
[//]: # (### Build on Windows)

[//]: # (```)

[//]: # (cmake -S . -B build)

[//]: # (```)

[//]: # ()
[//]: # (### Build on macOS)

[//]: # ()
[//]: # (To compile Gaze, you must have the most recent version of Xcode installed.)

[//]: # (Then run 'cmake' from the project's root directory, to generate a project of Xcode.)

[//]: # ()
[//]: # (```)

[//]: # (cmake -S . -B build -G "Xcode")

[//]: # (```)

[//]: # (and you can build the project with)

[//]: # (```)

[//]: # (cmake --build build --config Release)

[//]: # (```)