#include <engine/engine.hpp>
#include <game/game.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    Engine engine;
    engine.Init();
    engine.Update();
}
