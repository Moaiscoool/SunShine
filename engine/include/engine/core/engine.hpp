#pragma once
#include <engine/engine.hpp>

void registerScenes(Engine* engine);

class Engine {
    private:
        bool active = false;
        int targetframerate = 60;
        int num_keys;
        const bool *keystate = SDL_GetKeyboardState(&num_keys); 
        SDL_Event event;

        float x = 0;
        float y = 0;

    public:
        ConsoleEngine console;
        RenderEngine renderEngine;
        SceneManager sceneManager;

        bool Init();
        void Update();
        void Shutdown();
};