#pragma once

// Global
#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <sstream>
#include <iterator>
#include <memory>
#include <cmath>

// Windows / Linux
#if defined(_WIN32) || defined(_WIN64)
    #define SUNSHINE_WINDOWS
    #include <engine/window.hpp>
#else
    #define SUNSHINE_POSIX
    #include <engine/linux.hpp>
#endif

// scene
#include <engine/scene/scene.hpp>

// graphics
#include <engine/graphics/renderer.hpp>

// platform
#include <engine/platform/window.hpp>

// core
#include <engine/core/time.hpp>
#include <engine/core/logger.hpp>
#include <engine/core/commands.hpp>
#include <engine/core/engine.hpp>