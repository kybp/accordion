#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "util.h"

void die(const char *format_string, ...)
{
    va_list argp;
    endwin();
    va_start(argp, format_string);
    vfprintf(stderr, format_string, argp);
    exit(0);
}
