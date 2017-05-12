#include <stdlib.h>
#include <curses.h>
#include "cards.h"
#include "message.h"

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

static char char_from_rank(enum rank rank)
{
    switch (rank) {
    case ace:   return 'A';
    case deuce: return '2';
    case trey:  return '3';
    case four:  return '4';
    case five:  return '5';
    case six:   return '6';
    case seven: return '7';
    case eight: return '8';
    case nine:  return '9';
    case ten:   return 'T';
    case jack:  return 'J';
    case queen: return 'Q';
    case king:  return 'K';
    default: die("print_rank: Invalid card rank: %d\n", rank);
    }

    return '\0';                /* never reached */
}

static char char_from_suit(enum suit suit)
{
    switch (suit) {
    case clubs:    return 'C';
    case diamonds: return 'D';
    case hearts:   return 'H';
    case spades:   return 'S';
    default: die("print_suit: Invalid card suit: %d\n", suit);
    }

    return '\0';                /* never reached */
}

void string_from_card(char *destination, const struct card card)
{
    destination[0] = char_from_rank(card.rank);
    destination[1] = char_from_suit(card.suit);
    destination[2] = '\0';
}

void print_card(const struct card card)
{
    addch(char_from_rank(card.rank));
    addch(char_from_suit(card.suit));
}
