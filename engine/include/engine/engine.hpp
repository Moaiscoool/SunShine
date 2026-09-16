#pragma once

// Global
#include <SDL3/SDL.h>
#include <iostream>
#include <string>

// Windows/ Linux
#if defined(_WIN32) || defined(_WIN64)
    #define SUNSHINE_WINDOWS
    #include <engine/window.hpp>
#else
    #define SUNSHINE_POSIX
    #include <engine/linux.hpp>
#endif

// engine
// engine/core
#include <engine/core/engine.hpp>
#include <engine/core/logger.hpp>

// engine/graphics
#include <engine/graphics/renderer.hpp>

// engine/platform
#include <engine/platform/window.hpp>

// engine/scene
#include <engine/scene/scene.hpp>