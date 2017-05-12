#include <curses.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "message.h"

static void move_to_message_area()
{
    move(TOP_MARGIN / 2, RIGHT_MARGIN);
}

void display_message(const char *message)
{
    static int last_message_length = 0;

    int message_length = strlen(message);
    int i, original_x, original_y;
    getyx(stdscr, original_y, original_x);

    move_to_message_area();
    addstr(message);
    for (i = message_length; i < last_message_length; ++i) {
        addch(' ');
    }

    last_message_length = message_length;
    move(original_y, original_x);
}

void message_unknown_key(int key)
{
    char message[20];
    sprintf(message, "Invalid key: %c", key);
    display_message(message);
}

void die(const char *format_string, ...)
{
    va_list argp;
    endwin();
    va_start(argp, format_string);
    vfprintf(stderr, format_string, argp);
    exit(0);
}
