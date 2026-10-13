#include <game/game.hpp>

void registerScenes(Engine* engine) {
    engine->sceneManager.Register(std::make_unique<TestScene>());
}