#include "core/render.hpp"
#include <iostream>

int windowInit(SDL_Window** window, const char* windowName, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return -1; 
    }

    *window = SDL_CreateWindow(windowName, width, height, 0);

    if (*window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1; 
    }

    std::cout << "Window \"" << windowName << "\" Creation Succeeded\n";
    
    return 0;
}
