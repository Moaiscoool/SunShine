#include <engine/platform/window.hpp>
#include <SDL3/SDL.h>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    if (windowInit(&window, &renderer, "SunShine", 1280, 720) != 0) {
        return -1; 
    }

    bool active = true;
    int targetframerate = 60;
    
    int num_keys;
    const bool *keystate = SDL_GetKeyboardState(&num_keys); 

    SDL_Event event;

    SDL_FRect rect = { 300.0f, 225.0f, 200.0f, 150.0f };

    float x = 0;
    float y = 0;

    while (active) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT){
                active = false;
            }
        }

        SDL_Color black = {0, 0, 0, 255};

        drawBackground(renderer, black);

        drawRect(renderer, x, y, 200.0f, 150.0f, {255, 50, 50, 255});


        SDL_RenderPresent(renderer);

        if (keystate[SDL_SCANCODE_W]){
            y--;
        }

        if (keystate[SDL_SCANCODE_S]){
            y++;
        }

        if (keystate[SDL_SCANCODE_A]){
            x--;
        }

        if (keystate[SDL_SCANCODE_D]){
            x++;
        }

        if (keystate[SDL_SCANCODE_ESCAPE]){
            active = false;
        }

        SDL_Delay(1000 / targetframerate);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
