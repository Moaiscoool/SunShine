#include <engine/engine.hpp>

#define CURSOR_SAVE          "\033[s"
#define CURSOR_RESTORE       "\033[u"
#define CLEAR_LINE           "\033[2K"
#define RESET_COLOR          "\033[0m"
#define COLOR_YELLOW         "\033[33m"
#define COLOR_RED            "\033[31m"
#define COLOR_CYAN           "\033[36m"

void ConsoleEngine::Init(Engine* engine) {
    #ifdef SUNSHINE_POSIX
        SetTerminalRawMode(true);
    #endif
    std::cout << "> " << std::flush;
}

void ConsoleEngine::Shutdown() {
    #ifdef SUNSHINE_POSIX
        SetTerminalRawMode(false);
    #endif
}

    void ConsoleEngine::RegisterCommand(const std::string& name, CommandHandler handler) {
        commands[name] = handler;
}

void ConsoleEngine::DebugLog(const std::string& message)   { PrintLogLine("SunShine Debug: ", message); }
void ConsoleEngine::InfoLog(const std::string& message)    { PrintLogLine("SunShine Info: ", message, COLOR_CYAN); }
void ConsoleEngine::WarningLog(const std::string& message) { PrintLogLine("SunShine Warning: ", message, COLOR_YELLOW); }
void ConsoleEngine::ErrorLog(const std::string& message)   { PrintLogLine("SunShine Error: ", message, COLOR_RED); }

void ConsoleEngine::UpdateConsoleInput() {
    bool has_key = false;

    #if defined(SUNSHINE_WINDOWS)
        has_key = _kbhit();
    #elif defined(SUNSHINE_POSIX)
        has_key = POSIX_kbhit();
    #endif

    if (has_key) {
        char c = 0;
    #if defined(SUNSHINE_WINDOWS)
        c = _getch();
    #elif defined(SUNSHINE_POSIX)
        read(STDIN_FILENO, &c, 1);
    #endif

        if (c == '\n' || c == '\r') {
            if (!current_input_buffer.empty()) {
                std::cout << "\r" << CLEAR_LINE << std::flush;
                ExecuteConsoleCommand(current_input_buffer);
                current_input_buffer = "";
            }
            std::cout << "\r" << CLEAR_LINE << "> " << std::flush;
        }
        else if (c == 8 || c == 127) {
            if (!current_input_buffer.empty()) {
                current_input_buffer.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        }
        else if (c >= 32 && c <= 126) {
            current_input_buffer += c;
            std::cout << c << std::flush;
        }
    }
}

void ConsoleEngine::PrintLogLine(const std::string& prefix, const std::string& message, const std::string& color_code) {
    std::cout << "\r" << CLEAR_LINE;
    std::cout << color_code << prefix << message << RESET_COLOR << "\n";
    std::cout << "> " << current_input_buffer;
    std::cout << CURSOR_SAVE;
    std::cout.flush();
}

void ConsoleEngine::ExecuteConsoleCommand(const std::string& full_line) {
    std::stringstream ss(full_line);
    std::string command_name;
    ss >> command_name;

    std::vector<std::string> args;
    std::string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }

    auto it = commands.find(command_name);
    if (it != commands.end()) {
        it->second(args);
    } else {
        ErrorLog("Unknown command: " + command_name);
    }
}

#ifdef SUNSHINE_POSIX
void ConsoleEngine::SetTerminalRawMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

bool ConsoleEngine::POSIX_kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}
#endif