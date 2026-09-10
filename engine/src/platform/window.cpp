#include <engine/platform/window.hpp>
#include <SDL3/SDL.h>
#include <iostream>

int windowInit(SDL_Window** window, SDL_Renderer** renderer, const char* windowName, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return -1; 
    }

    if (!SDL_CreateWindowAndRenderer(windowName, width, height, SDL_WINDOW_RESIZABLE, window, renderer)) {
        SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowPosition(*window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    if (*window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1; 
    }

    std::cout << "Window \"" << windowName << "\" Creation Succeeded\n";
    
    return 0;
}

int drawBackground(SDL_Renderer* renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    return 0;
}

int drawRect(SDL_Renderer* renderer, float x, float y, float width, float height, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
    return 0;
}