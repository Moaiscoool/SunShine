#include "core/render.hpp"
#include <SDL3/SDL.h>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    SDL_Window* window = nullptr;

    windowInit(&window, "SunShine", 1280, 720);

    bool active = 1;
    
    int update = 0;

    while(1){
        std::cout << update;
        update++;
        SDL_Delay(30);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
