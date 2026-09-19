#include <engine/engine.hpp>

int windowInit(Engine* engine, SDL_Window** window, SDL_Renderer** renderer, const char* windowName, int width, int height) {
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

    std::string windowNameString(windowName);
    //InfoLog("Window \"" + windowNameString+ "\" Creation Succeeded");
    
    return 0;
}