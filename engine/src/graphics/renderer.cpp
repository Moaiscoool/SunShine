#include <engine/engine.hpp>

struct rect {
    int x;
    int y;
    int width; 
    int height;
    SDL_Color color;
};

int RenderEngine::drawBackground(SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    return 0;
}

int RenderEngine::drawRect(float x, float y, float width, float height, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
    return 0;
}

void RenderEngine::render(){
    SDL_RenderPresent(renderer);
}

bool RenderEngine::Init(Engine* engine){
    window = nullptr;
    renderer = nullptr;

    if (windowInit(engine, &window, &renderer, "SunShine", 1280, 720) != 0){
        return false; 
    }

    return true;
}

void RenderEngine::Shutdown(){
    SDL_DestroyWindow(window);
}