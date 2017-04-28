#ifndef CARDS_H
#define CARDS_H

/**
 * The number of characters a card's representation occupies. One character for
 * the suit and one for the rank.
 */
#define CHARS_PER_CARD 2

enum suit { clubs, diamonds, hearts, spades, number_of_suits };

enum rank {
    ace, deuce, trey, four, five, six, seven, eight,
    nine, ten, jack, queen, king, number_of_ranks
};

struct card { enum rank rank; enum suit suit; };

struct deck {
    struct card cards[52];
    int total_cards;
};

/**
 * Populate the given deck with all 52 cards, unshuffled.
 */
void fill_deck(struct deck *deck);

/**
 * Randomly rearrange the cards in the given deck.
 */
void shuffle(struct deck *deck);

/**
 * Print a one-character representation of the given rank at the current cursor
 * position.
 */
void print_rank(enum rank rank);

/**
 * Print a one-character representation of the given suit at the current cursor
 * position.
 */
void print_suit(enum suit suit);

/**
 * Print a one-character representation of the given rank at the current cursor
 * position.
 */
void print_card(const struct card card);

#endif
