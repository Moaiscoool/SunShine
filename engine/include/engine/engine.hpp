#pragma once

// Global
#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <sstream>

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
#include <engine/core/logger.hpp>
#include <engine/core/commands.hpp>
#include <engine/core/engine.hpp>


// engine/graphics
#include <engine/graphics/renderer.hpp>

// engine/platform
#include <engine/platform/window.hpp>

// engine/scene
#include <engine/scene/scene.hpp>