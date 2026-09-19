#pragma once
#include <engine/engine.hpp>

class Engine;

class ConsoleEngine {
    public:
        using CommandHandler = std::function<void(const std::vector<std::string>& args)>;

        void Init(Engine* engine);
        void Shutdown();
        void RegisterCommand(const std::string& name, CommandHandler handler);
    
        void DebugLog(const std::string& message);
        void InfoLog(const std::string& message);
        void WarningLog(const std::string& message);
        void ErrorLog(const std::string& message);
    
        void UpdateConsoleInput();

        void ExecuteConsoleCommand(const std::string& full_line);

    private:
        std::string current_input_buffer;
        std::unordered_map<std::string, CommandHandler> commands;

        void PrintLogLine(const std::string& prefix, const std::string& message, const std::string& color_code = "\033[0m");

    #ifdef SUNSHINE_POSIX
        void SetTerminalRawMode(bool enable);
        bool POSIX_kbhit();
    #endif
};
