#if defined(__linux__) || defined(__APPLE__)
    #define SUNSHINE_POSIX
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>
#endif