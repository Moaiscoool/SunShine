#include <engine/engine.hpp>

bool Engine::Init(){

    console.Init(this);
    sceneManager.Init(this);
    registerCommands(this);
    registerScenes(this);

    if (!renderEngine.Init(this)) {
        return false;
    }

    active = true;

    return true;
}

void Engine::Update(){
    while(active){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_QUIT){
                active = false;
            }
        }
        
        updateDeltaTime();

        console.UpdateConsoleInput();
        
        renderEngine.drawBackground(Silver);
        renderEngine.drawRect(x, y, 50.0f, 50.0f, {0, 50, 50, 255});
        renderEngine.render();

        
        float dx = 0.0f, dy = 0.0f;
        if (keystate[SDL_SCANCODE_W]) dy -= 1.0f;
        if (keystate[SDL_SCANCODE_S]) dy += 1.0f;
        if (keystate[SDL_SCANCODE_A]) dx -= 1.0f;
        if (keystate[SDL_SCANCODE_D]) dx += 1.0f;

        float len = std::sqrt(dx * dx + dy * dy);
        if (len > 0.0f) { dx /= len; dy /= len; }

        const float speed = 200.0f;
        x += dx * speed * deltaTime;
        y += dy * speed * deltaTime;

        if (keystate[SDL_SCANCODE_ESCAPE]) {
            active = false;
        }

        SDL_Delay(1000 / targetframerate);
    }
}

void Engine::Shutdown(){
    active = false;
    console.Shutdown();
    renderEngine.Shutdown();
    SDL_Quit();
}