cmake_minimum_required(VERSION 3.20)

# ==================================================
# Game Configuration
# ==================================================

set(GAME_NAME "SunShine")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${GAME_NAME}
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==================================================
# SDL3
# ==================================================

include(FetchContent)

# Try to find SDL3 installed on the system first.
find_package(SDL3 CONFIG QUIET)

if(NOT SDL3_FOUND)

    message(STATUS "SDL3 was not found.")
    message(STATUS "Downloading SDL3...")

    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.0
        GIT_SHALLOW TRUE
    )

    set(SDL_TESTS OFF CACHE BOOL "" FORCE)
    set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SDL3)

    message(STATUS "SDL3 downloaded and configured.")

else()

    message(STATUS "Found system SDL3.")

endif()

# ==================================================
# Source Files
# ==================================================

file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/engine/src/*.cpp"
)

file(GLOB_RECURSE GAME_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/game/src/*.cpp"
)

# ==================================================
# Engine Library
# ==================================================

add_library(GameEngine STATIC
    ${ENGINE_SOURCES}
)

target_include_directories(GameEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)

target_link_libraries(GameEngine
    PUBLIC
        SDL3::SDL3
)

# ==================================================
# Game Executable
# ==================================================

add_executable(${GAME_NAME}
    ${GAME_SOURCES}
)

target_include_directories(${GAME_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/game/include
)

target_link_libraries(${GAME_NAME}
    PRIVATE
        GameEngine
)

# ==================================================
# Compiler Warnings
# ==================================================

if(MSVC)

    target_compile_options(GameEngine
        PRIVATE
            /W4
    )

    target_compile_options(${GAME_NAME}
        PRIVATE
            /W4
    )

else()

    target_compile_options(GameEngine
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )

    target_compile_options(${GAME_NAME}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )

endif()

# ==================================================
# Output
# ==================================================

set_target_properties(${GAME_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# ==================================================
# Build Information
# ==================================================

message(STATUS "")
message(STATUS "======================================")
message(STATUS " Game Configuration")
message(STATUS "======================================")
message(STATUS " Game: ${GAME_NAME}")
message(STATUS " Version: ${PROJECT_VERSION}")
message(STATUS " Engine sources: ${ENGINE_SOURCES}")
message(STATUS " Game sources: ${GAME_SOURCES}")
message(STATUS "======================================")
message(STATUS "")