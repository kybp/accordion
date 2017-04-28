# Accordion

This is a simple implementation in C89 of the solitaire game Accordion for Unix
using Curses.

## Rules

Initially, all 52 cards of a standard deck are laid out one after another. Any
card can be moved back either 1 or 3 spaces if the card already at that position
is of the same suit or rank as the card being moved. The card previously at that
position ceases to exist. The goal of the game is to reduce the entire deck into
1 card.

## Controls

    h - move the cursor back one card
    l - move the cursor forward one card
    j - move the cursor down one row
    k - move the cursor up one row
    1 - attempt to move the card under the cursor back 1 space
    3 - attempt to move the card under the cursor back 3 spaces
    r - redraw the entire screen
    q - quit the game immediately
