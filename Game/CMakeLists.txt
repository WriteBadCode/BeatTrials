cmake_minimum_required(VERSION 3.20)
project(MyWebSocketGame)

# Define project subdirectories with comments
set(GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")  # Current directory (game)
set(SERVER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SocketServer")  # Subdirectory for server code
set(RHYTHM_GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RhythmGame")  # Subdirectory for game code

# Set CMAKE_PREFIX_PATH to vcpkg installation directory (assuming vcpkg is used)
set(CMAKE_PREFIX_PATH "${GAME_DIR}/ext/vcpkg_installed/x64-windows")

# Find libraries (assuming vcpkg takes care of include paths)
find_package(websocketpp CONFIG REQUIRED)  # Find websocketpp library
find_package(Boost REQUIRED COMPONENTS filesystem system)  # Find Boost with specific components
find_package(SFML COMPONENTS graphics system window REQUIRED)  # Find SFML with graphics and system components

# Build WebSocket Server target
add_executable(websocket_server ${SERVER_DIR}/src/main.cpp)
target_link_libraries(websocket_server websocketpp::websocketpp Boost::filesystem Boost::system)

# Build Rhythm Game target
add_executable(rhythm_game ${RHYTHM_GAME_DIR}/src/main.cpp)
target_link_libraries(rhythm_game sfml-graphics sfml-system websocketpp::websocketpp Boost::filesystem Boost::system)

# Set output directory for built executables (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

# Get the directory containing all DLL files
set(DLL_DIR "${CMAKE_PREFIX_PATH}/debug/bin")

# List all DLL files in the directory
file(GLOB DLL_FILES "${DLL_DIR}/*.dll")

# Copy all DLL files to the output directory
foreach(DLL ${DLL_FILES})
    add_custom_command(TARGET rhythm_game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DLL}"
        $<TARGET_FILE_DIR:rhythm_game>
    )
endforeach()

# Define a custom target for cleaning
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/Debug"
)

# Add clean-all as a dependency of the clean-all target
add_custom_target(clean-all-all)
add_dependencies(clean-all-all clean-all)
