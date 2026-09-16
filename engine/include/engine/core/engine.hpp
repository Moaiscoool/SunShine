#pragma once
#include <engine/engine.hpp>

class Engine {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool active = false;
        int targetframerate = 60;
        int num_keys;
        const bool *keystate = SDL_GetKeyboardState(&num_keys); 
        SDL_Event event;

    float x = 0;
    float y = 0;

    public:
        bool init();
        void run();
        void shutdown();
};