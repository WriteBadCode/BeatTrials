# BeatTrials

BeatTrials is an optional multiplayer rhythm game that includes a WebSocket server component.

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

## vcpkg Setup

1. Run the following command to integrate vcpkg with your project and redirect the download port to the `ext` directory:
    ```bash
    cd "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg"
    .\vcpkg.exe integrate install --overlay-ports="<path/to/your/project/ext>"
    ```

2. Run the following command to initiate vcpkg:
    ```bash
    vcpkg install
    ```

3. Return to the file directory where `CMakeLists.txt` is located (should be in the `Game` directory).

4. Run the following command to make a directory to build the project:
    ```bash
    mkdir build
    cd build
    ```

5. Create the CMake building files:
    ```bash
    cmake ..
    ```

6. Build the actual project:
    ```bash
    cmake --build .
    ```

## How to Run

To run the project, open file explorer, navigate to the `Debug` directory inside your `build` folder, then select the `.exe` executable you want to run.

## How to Refresh

To refresh the project, run the following command:
```bash
cmake --build . --config Debug

How to Clean .exe

To clean the .exe files, run the following command:

bash

cmake --build . --target clean

How to Destroy the Debug File

To completely remove the Debug folder, run the following command:

bash

cmake --build . --target clean-all

Note: The "destroying the debug file" command is a custom command. Check CMakeLists.txt for more info.

arduino


This format should provide clear instructions for users on how to set up, build, run, and clean the project.