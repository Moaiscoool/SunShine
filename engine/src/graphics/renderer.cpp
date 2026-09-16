#include <engine/engine.hpp>

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