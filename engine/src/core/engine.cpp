#include <engine/engine.hpp>



bool Engine::init(){
    window = nullptr;
    renderer = nullptr;
    
    if (windowInit(&window, &renderer, "SunShine", 1280, 720) != 0) {
        return -1; 
    }

    InitConsoleEngine();

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

        UpdateConsoleInput();
        
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

        if (current_input_buffer == "exit"){
            active = false;
        }
    }
}

void Engine::shutdown(){
    ShutdownConsoleEngine();
    SDL_DestroyWindow(window);
    SDL_Quit();
}