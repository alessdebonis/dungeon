#include "input.h"

#ifdef _WIN32
    #include <conio.h>

    char getKey() {
        return _getch();
    }

#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdio>

    char getKey() {
        struct termios oldconfig;
        struct termios newconfig;
        char key;

        tcgetattr(STDIN_FILENO, &oldconfig);

        newconfig = oldconfig;
        newconfig.c_lflag = newconfig.c_lflag & ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &newconfig);

        key = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldconfig);

        return key;
    }

#endif