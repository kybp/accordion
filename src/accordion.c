#include <curses.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"
#include "util.h"

/**
 * The amounts of empty space to display on each side of the tableau
 */
#define TOP_MARGIN   2
#define LEFT_MARGIN  4
#define RIGHT_MARGIN 4

#define SPACE_BETWEEN_CARDS 2
#define SPACE_BETWEEN_LINES 1

/**
 * Return the number of cards that should be displayed in each row, according to
 * SPACE_BETWEEN_CARDS, SPACE_BETWEEN_LINES, RIGHT_MARGIN, and the current
 * terminal width.
 */
int get_cards_per_row(void)
{
    const int max_x = getmaxx(stdscr);
    const int another_card = SPACE_BETWEEN_CARDS + CHARS_PER_CARD;

    int columns = LEFT_MARGIN + CHARS_PER_CARD + RIGHT_MARGIN;
    int number_of_cards = 1;

    if (columns >= max_x) {
        die("Screen is too narrow (%d columns; need at least %d)\n",
            max_x, columns);
    }

    while (columns + another_card < max_x) {
        ++number_of_cards;
        columns += another_card;
    }

    return number_of_cards;
}

/**
 * Move the cursor to point at the `index`th card in the tableau.
 */
void move_to_position(int index)
{
    const int cards_per_row = get_cards_per_row();
    const int column = index % cards_per_row;
    const int row    = index / cards_per_row;
    const int x = LEFT_MARGIN +
        CHARS_PER_CARD      * column +
        SPACE_BETWEEN_CARDS * column;
    const int y = TOP_MARGIN + row + SPACE_BETWEEN_CARDS * row;
    move(y, x);
}

void print_deck(const struct deck *deck)
{
    int i;

    for (i = 0; i < deck->total_cards; ++i) {
        move_to_position(i);
        print_card(deck->cards[i]);
    }
}

void redraw_deck(const struct deck *deck)
{
    clear();
    print_deck(deck);
}

void handle_input(int input, struct deck *deck, int *position)
{
    const int cards_per_row = get_cards_per_row();
    int new_position = -1;

    switch (input) {
    case 'h': new_position = *position - 1; break;
    case 'l': new_position = *position + 1; break;
    case 'k': new_position = *position - cards_per_row; break;
    case 'j': new_position = *position + cards_per_row; break;
    case 'r': redraw_deck(deck); break;
    case 'q': die("You quit with %d piles.\n", deck->total_cards);
    }

    if (new_position >= 0 && new_position < deck->total_cards) {
        *position = new_position;
    }
}

void accordion(struct deck *deck)
{
    int position = 0;

    print_deck(deck);
    move_to_position(position);

    for (;;) {
        handle_input(getch(), deck, &position);
        move_to_position(position);
        refresh();
    }
}

int main(void)
{
    struct deck deck;

    srand(time(NULL));

    fill_deck(&deck);
    shuffle(&deck);

    initscr();
    cbreak();
    noecho();

    accordion(&deck);

    endwin();
    return 0;
}
