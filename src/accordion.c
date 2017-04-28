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

/**
 * Print all of the remaining cards in the tableau to the terminal.
 */
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

/**
 * Return whether or not one card may be moved on top of another card.
 */
int matches(const struct card card1, const struct card card2)
{
    return card1.rank == card2.rank || card1.suit == card2.suit;
}

/**
 * Return whether or not the card at `position` in `deck` can be moved `n`
 * positions backward.
 */
int can_move_n(const struct deck *deck, int position, int n)
{
    return position - n >= 0 &&
        matches(deck->cards[position], deck->cards[position - n]);
}

/**
 * Move the card at `source_index` in `deck` to `destination_index` and draw
 * that card at its new location, over top of the source card. This does not
 * affect the source card in the deck or on the screen.
 */
void move_card(struct deck *deck, int destination_index, int source_index)
{
    deck->cards[destination_index] = deck->cards[source_index];
    move_to_position(destination_index);
    print_card(deck->cards[destination_index]);
}

/**
 * If it is a legal move, move the card at `position` in `deck` back `n` spaces,
 * removing the card previously `n` spaces behind `position` from play. If the
 * move is not legal, do nothing.
 */
void try_move_n(struct deck *deck, int *position, int n)
{
    int i;

    if (! can_move_n(deck, *position, n)) return;

    *position -= n;
    move_card(deck, *position, *position + n);
    --deck->total_cards;
    for (i = *position + n; i < deck->total_cards; ++i) {
        move_card(deck, i, i + 1);
    }

    move_to_position(deck->total_cards);
    for (i = 0; i < CHARS_PER_CARD; ++i) addstr(" ");
}

/**
 * Return whether or not there are any legal moves available in the deck.
 */
int is_game_over(const struct deck *deck)
{
    int i;

    for (i = 0; i < deck->total_cards; ++i) {
        if (can_move_n(deck, i, 1) || can_move_n(deck, i, 3)) {
            return 0;
        }
    }

    return 1;
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
    case '1': try_move_n(deck, position, 1); break;
    case '3': try_move_n(deck, position, 3); break;
    case 'q': die("You quit with %d piles.\n", deck->total_cards);
    }

    if (new_position >= 0 && new_position < deck->total_cards) {
        *position = new_position;
    }
}

static void print_outcome(const struct deck *deck)
{
    if (deck->total_cards == 1) {
        die("You won!\n");
    } else {
        die("You lost with %d piles remaining.\n", deck->total_cards);
    }
}

void accordion(struct deck *deck)
{
    int position = 0;

    print_deck(deck);
    move_to_position(position);

    while (! is_game_over(deck)) {
        handle_input(getch(), deck, &position);
        move_to_position(position);
        refresh();
    }

    print_outcome(deck);
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
