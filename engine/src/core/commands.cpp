#include <engine/engine.hpp>

void registerCommands(Engine* engine){
    engine->console.RegisterCommand("shutdown", [engine](const std::vector<std::string>& args) {
        ShutdownCommand(engine);
    });

    engine->console.RegisterCommand("echo", [engine](const std::vector<std::string>& args) {
        EchoCommand(engine, args);
    });
}

void EchoCommand(Engine* engine, const std::vector<std::string>& args) {
    std::string result;
    for (const auto& arg : args) {
        result += arg + " ";
    }

    engine->console.InfoLog("Echo output: " + result);
}

void ShutdownCommand(Engine* engine){
    engine->shutdown();
}