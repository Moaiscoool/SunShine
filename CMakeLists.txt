cmake_minimum_required(VERSION 3.20)

project(MyGame
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# --------------------------------------------------
# SDL3
# --------------------------------------------------

# First try to find SDL3 already installed on the system.
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

    # Don't build SDL's extra examples/tests.
    set(SDL_TESTS OFF CACHE BOOL "" FORCE)
    set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SDL3)

    message(STATUS "SDL3 downloaded and configured.")
else()
    message(STATUS "Found system SDL3.")
endif()

# --------------------------------------------------
# Game
# --------------------------------------------------

add_executable(MyGame
    src/main.cpp
)

target_include_directories(MyGame
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MyGame
    PRIVATE
        SDL3::SDL3
)

# --------------------------------------------------
# Compiler warnings
# --------------------------------------------------

if(MSVC)
    target_compile_options(MyGame PRIVATE /W4)
else()
    target_compile_options(MyGame PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# --------------------------------------------------
# Output
# --------------------------------------------------

set_target_properties(MyGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)