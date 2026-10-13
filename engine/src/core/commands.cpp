#include <engine/engine.hpp>

void EchoCommand(Engine* engine, const std::vector<std::string>& args) {
    std::string result;
    for (const auto& arg : args) {
        result += arg + " ";
    }

    engine->console.InfoLog("Echo output: " + result);
}

void ShutdownCommand(Engine* engine){
    engine->Shutdown();
}

void LoadSceneCommand(Engine* engine, const std::vector<std::string>& args) {
    if (args.empty()) { engine->console.ErrorLog("Usage: loadScene <id>"); return; }
    engine->sceneManager.LoadScene(args[0]);
}

void registerCommands(Engine* engine){
    engine->console.RegisterCommand("shutdown", [engine](const std::vector<std::string>& args) {
        ShutdownCommand(engine);
    });

    engine->console.RegisterCommand("echo", [engine](const std::vector<std::string>& args) {
        EchoCommand(engine, args);
    });

    engine->console.RegisterCommand("loadScene", [engine](const std::vector<std::string>& args) {
        LoadSceneCommand(engine, args);
    });
}