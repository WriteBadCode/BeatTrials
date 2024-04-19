cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0128 NEW)  # Enable warnings for CMake 3.12 and above
cmake_policy(SET CMP0156 NEW)  # Enable warnings for CMake 3.16 and above

project(MyWebSocketGame)

# Define project subdirectories with comments
set(GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")  # Current directory (game)
set(SERVER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SocketServer")  # Subdirectory for server code
set(RYTHM_GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RythmGame")  # Subdirectory for game code

# Set CMAKE_PREFIX_PATH to vcpkg installation directory (assuming vcpkg is used)
set(CMAKE_PREFIX_PATH "${GAME_DIR}/ext/vcpkg_installed/x64-windows")

# Find libraries (assuming vcpkg takes care of include paths)
find_package(websocketpp CONFIG REQUIRED)  # Find websocketpp library
find_package(Boost REQUIRED COMPONENTS filesystem system)  # Find Boost with specific components
find_package(SFML COMPONENTS graphics system REQUIRED)  # Find SFML with graphics and system components

# Build WebSocket Server target
add_executable(websocket_server ${SERVER_DIR}/src/main.cpp)
target_link_libraries(websocket_server websocketpp::websocketpp Boost::filesystem Boost::system)

# Build Rythm Game target
add_executable(rythm_game ${RYTHM_GAME_DIR}/src/main.cpp)
target_link_libraries(rythm_game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} websocketpp::websocketpp Boost::filesystem Boost::system)

# Set output directory for built executables (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")