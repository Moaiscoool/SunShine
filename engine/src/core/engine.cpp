#include <engine/engine.hpp>

bool Engine::init(){
    window = nullptr;
    renderer = nullptr;
    
    ConsoleEngine console;
    console.Init(this);
    registerCommands(this);

    if (windowInit(this, &window, &renderer, "SunShine", 1280, 720) != 0) {
        return -1; 
    }

    active = true;
    return 1;
}

void Engine::run(){
    while(active){
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT){
                active = false;
            }
        }

        console.UpdateConsoleInput();
        
        drawBackground(renderer, Silver);

        drawRect(renderer, x, y, 50.0f, 50.0f, {0, 50, 50, 255});


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
}

void Engine::shutdown(){
    console.Shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();
}