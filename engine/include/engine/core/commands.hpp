#pragma once
#include <engine/engine.hpp>

class Engine;

void registerCommands(Engine* engine);

void ShutdownCommand(Engine* engine);
void EchoCommand(Engine* engine, const std::vector<std::string>& args);