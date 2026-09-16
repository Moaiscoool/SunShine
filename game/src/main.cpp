#include <engine/engine.hpp>
#include <SDL3/SDL.h>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    Engine engine;
    engine.init();
    engine.run();
    engine.shutdown();
}
