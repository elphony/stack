#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "text_color.h"

int color_fprintf(FILE *stream, Color code, const char* string, ...) {
    assert(stream != NULL);
    assert(string != NULL);
    va_list ap;
    va_start(ap, string);

    const int max_size_str = 10;
    char str[max_size_str] = {};
    fprintf(stream, "\033[1;%dm", code);
    int count = vfprintf(stream, string, ap);
    fprintf(stream, "\033[0m");
    return count;
}