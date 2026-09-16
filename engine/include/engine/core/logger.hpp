#pragma once
#include <engine/engine.hpp>

void InitConsoleEngine();
void UpdateConsoleInput();
void ShutdownConsoleEngine();

void DebugLog(std::string message);
void InfoLog(std::string message);
void WarnLog(std::string message);
void ErrorLog(std::string message);

inline std::string current_input_buffer = "";