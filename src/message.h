#ifndef MESSAGE_H
#define MESSAGE_H

/**
 * Display the NUL-terminated string `message` to the user in the message area
 * inside the margin at the top of the screen, first clearing the last printed
 * message.
 */
void display_message(const char *message);

void message_unknown_key(int key);

/**
 * Clean up and exit the program, printing the `printf`-style `format_string`.
 */
void die(const char *format_string, ...);

#endif
