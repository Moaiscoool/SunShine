#include <engine/engine.hpp>

void updateDeltaTime(){
    Uint64 currentCounter = SDL_GetPerformanceCounter();
    deltaTime =
        static_cast<double>(currentCounter - previousCounter) /
        static_cast<double>(performanceFrequency);
        
    previousCounter = currentCounter;

    deltaTime = std::min(deltaTime, 0.1);
}