#include <engine/engine.hpp>

#define CURSOR_SAVE          "\033[s"
#define CURSOR_RESTORE       "\033[u"
#define CLEAR_LINE           "\033[2K"
#define RESET_COLOR          "\033[0m"
#define COLOR_YELLOW         "\033[33m"
#define COLOR_RED            "\033[31m"
#define COLOR_CYAN           "\033[36m"

#ifdef SUNSHINE_POSIX
void SetTerminalRawMode(bool enable){
    static struct termios oldt, newt;
    if (enable){
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else{
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

bool POSIX_kbhit(){
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}
#endif

void InitConsoleEngine(){
#ifdef SUNSHINE_POSIX
    SetTerminalRawMode(true);
#endif
    std::cout << "> " << std::flush;
}

void ShutdownConsoleEngine(){
    #ifdef SUNSHINE_POSIX
        SetTerminalRawMode(false);
    #endif
}

void PrintLogLine(const std::string& prefix, const std::string& message, const std::string& color_code = RESET_COLOR){
    std::cout << "\r" << CLEAR_LINE;
    std::cout << color_code << prefix << message << RESET_COLOR << "\n";
    std::cout << "> " << current_input_buffer;
    std::cout << CURSOR_SAVE;
    std::cout.flush();
}

void DebugLog(std::string message){ PrintLogLine("SunShine Debug: ", message);}
void InfoLog(std::string message){ PrintLogLine("SunShine Info: ", message, COLOR_CYAN);}
void WarningLog(std::string message){ PrintLogLine("SunShine Warning: ", message, COLOR_YELLOW);}
void ErrorLog(std::string message){ PrintLogLine("SunShine Error: ", message, COLOR_RED);}

void ExecuteConsoleCommand(const std::string& command){
    InfoLog("Executing command: " + command);
}

void UpdateConsoleInput(){
    bool has_key = false;
    
#if defined(SUNSHINE_WINDOWS)
    has_key = _kbhit();
#elif defined(SUNSHINE_POSIX)
    has_key = POSIX_kbhit();
#endif

    if (has_key){
        char c = 0;
#if defined(SUNSHINE_WINDOWS)
        c = _getch();
#elif defined(SUNSHINE_POSIX)
        read(STDIN_FILENO, &c, 1);
#endif
        if (c == '\n' || c == '\r'){
            if (!current_input_buffer.empty()){
                std::cout << "\r" << CLEAR_LINE << std::flush;
                ExecuteConsoleCommand(current_input_buffer);
                current_input_buffer = "";
            }
            std::cout << "\r" << CLEAR_LINE << "> " << std::flush;
        }
        else if (c == 8 || c == 127){
            if (!current_input_buffer.empty()){
                current_input_buffer.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        }
        else if (c >= 32 && c <= 126){
            current_input_buffer += c;
            std::cout << c << std::flush;
        }
    }
}