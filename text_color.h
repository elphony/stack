#ifndef TEXT_COLOR_H
#define TEXT_COLOR_H

#include <stdio.h>

enum Color {
    COLOR_BLACK = 30, // system code
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE
};

int color_fprintf(FILE* stream, Color code, const char* string, ...);

#endif // TEXT_COLOR_H