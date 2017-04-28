#include <stdlib.h>
#include <curses.h>
#include "cards.h"
#include "util.h"

void fill_deck(struct deck *deck)
{
    int suit, rank;

    deck->total_cards = 0;
    for (suit = 0; suit < number_of_suits; ++suit) {
        for (rank = 0; rank < number_of_ranks; ++rank) {
            deck->cards[deck->total_cards].rank = rank;
            deck->cards[deck->total_cards].suit = suit;
            ++deck->total_cards;
        }
    }
}

void shuffle(struct deck *deck)
{
    int i;

    for (i = deck->total_cards - 1; i >= 0; --i) {
        const int j = rand() % (i + 1);
        struct card temp = deck->cards[j];
        deck->cards[j] = deck->cards[i];
        deck->cards[i] = temp;
    }
}

void print_rank(enum rank rank)
{
    switch (rank) {
    case ace:   addstr("A"); break;
    case deuce: addstr("2"); break;
    case trey:  addstr("3"); break;
    case four:  addstr("4"); break;
    case five:  addstr("5"); break;
    case six:   addstr("6"); break;
    case seven: addstr("7"); break;
    case eight: addstr("8"); break;
    case nine:  addstr("9"); break;
    case ten:   addstr("T"); break;
    case jack:  addstr("J"); break;
    case queen: addstr("Q"); break;
    case king:  addstr("K"); break;
    default: die("print_rank: Invalid card rank: %d\n", rank);
    }
}

void print_suit(enum suit suit)
{
    switch (suit) {
    case clubs:    addstr("C"); break;
    case diamonds: addstr("D"); break;
    case hearts:   addstr("H"); break;
    case spades:   addstr("S"); break;
    default: die("print_suit: Invalid card suit: %d\n", suit);
    }
}

void print_card(const struct card card)
{
    print_rank(card.rank);
    print_suit(card.suit);
}
