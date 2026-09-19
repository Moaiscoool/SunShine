#include <engine/engine.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    Engine engine;
    engine.init();
    engine.run();
    engine.shutdown();
}
