Hello, this is the template of the RythmGame we're making

BeatTrials/
│
├── CMakeLists.txt
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── settings.json
│   └── tasks.json
│
├── ext/
│   ├── vcpkg_installed/
│   │   ├── vcpkg/
│   │   └── x64-windows/
│   └── vcpkg.json
│
├── SocketServer/
│   ├── .vscode/
│   │   └── tasks.json
│   ├── build/
│   ├── include/
|   └── src/main.cpp
│
└── RythmGame/
    ├── .vscode/
    │   └── tasks.json
    ├── assets/
    ├── build/
    ├── include/
    └── src/main.cpp

The following is the vcpkg set up, redirecting the download port to the current directory

cd "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg"
.\vcpkg.exe integrate install --overlay-ports="Path to your project ext directory here"

The following is the installation command. (the required dependencies are listed in the ext/vcpkg.json)

vcpkg install


