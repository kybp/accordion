#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"
#include "games.h"

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
