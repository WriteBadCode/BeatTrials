cmake_minimum_required(VERSION 3.20)
project(MyWebSocketGame)

# Define project subdirectories
set(GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Game")
set(SERVER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Game/SocketServer")
set(RYTHM_GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Game/RythmGame")

# Find websocketpp library (assuming it's built as a shared library)
find_package(websocketpp REQUIRED)
include_directories(${websocketpp_INCLUDE_DIRS})

# Find Boost library and specify components
find_package(Boost REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

# Build WebSocket Server
add_executable(websocket_server ${SERVER_DIR}/build/main.cpp)
target_link_libraries(websocket_server websocketpp Boost::filesystem Boost::system)

# Find SFML library
find_package(SFML REQUIRED COMPONENTS graphics system)
include_directories(${SFML_INCLUDE_DIRS})

# Build SFML Game
add_executable(rythm_game ${RYTHM_GAME_DIR}/build/main.cpp)
target_link_libraries(rythm_game SFML::graphics SFML::system websocketpp Boost::filesystem Boost::system)

# Optional: Set build directory (if you want to keep build artifacts separate)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
