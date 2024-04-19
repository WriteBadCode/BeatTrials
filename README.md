# BeatTrials

[Short description of your project here]

## Directory Structure

This project is organized into the following directories:

* **CMakeLists.txt:** The main build configuration file for your project using CMake.
* **.vscode/:** Configuration files for Visual Studio Code:
    * `c_cpp_properties.json`: Defines IntelliSense and other C/C++ language features.
    * `settings.json`: General settings for your Visual Studio Code workspace.
    * `tasks.json`: Defines tasks for running builds and other actions within the IDE.
* **ext/:** Third-party libraries managed with vcpkg:
    * **vcpkg_installed/:** Installation directory for vcpkg dependencies.
        * **vcpkg/:** Internal vcpkg directory (usually not modified directly).
        * **x64-windows/:** Architecture-specific installation for Windows (may vary for other platforms).
    * **vcpkg.json:** Configuration file for managing vcpkg dependencies.
* **SocketServer/:** Directory for the socket server component:
    * **.vscode/tasks.json:** Defines tasks for building the socket server within Visual Studio Code.
    * **build/:** Build output directory for the socket server (generated during compilation).
    * **include/:** Header files for the socket server project.
    * **src/main.cpp:** The main source code file for the socket server.
* **RythmGame/:** Directory for the rhythm game component:
    * **.vscode/tasks.json:** Defines tasks for building the rhythm game within Visual Studio Code.
    * **assets/:** Resource files for the rhythm game (images, sounds, etc.).
    * **build/:** Build output directory for the rhythm game (generated during compilation).
    * **include/:** Header files for the rhythm game project.
    * **src/main.cpp:** The main source code file for the rhythm game.

## vcpkg Setup and Installation

### vcpkg Setup

1. Navigate to the vcpkg installation directory (usually `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg`).
2. Run the following command to integrate vcpkg with your project and redirect the download port to the `ext` directory:

   ```bash
   cd "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg"
   .\vcpkg.exe integrate install --overlay-ports="<path/to/your/project/ext>"
