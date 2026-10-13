#pragma once
#include <engine/engine.hpp>

inline double deltaTime = 0.0;
inline Uint64 previousCounter = SDL_GetPerformanceCounter();
inline const Uint64 performanceFrequency = SDL_GetPerformanceFrequency();

void updateDeltaTime();