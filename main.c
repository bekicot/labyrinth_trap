//
//  main.c
//  labirin_trap
//
//  Created by Yana Agun Siswanto on 11/6/16.
//  Copyright © 2016 Yana Agun Siswanto. All rights reserved.
//

#include <stdio.h>
#include <ncurses.h>
#include "map.h"
#include "position.h"
#include "victim.h"
#include "maps/map_1.h"

void test();
void playGame();
void keyPress(map m, victim *v);

int main(int argc, char *argv[]) {
    // Start The game. I have a plan to separata the menu and the game. It will be usefull once i created the menu later.
    playGame();
}

void playGame() {
    // Initialize window for map
    WINDOW *playArea;
    // Initialize map
    map currentMap;

    /* Ncurses Initialization Functions */
    // Initialize Screen
    initscr();
    // Suppress output. To prevent unintended characters echoed to screen
    noecho();
    // Disable line buffering. Allow characters available to program without the need to press return
    cbreak();
    // Refresh the screen. It also Flushes any buffered modification to the screen.
    refresh();
    // Disable cursor
    curs_set(0);

    /* Map Configuration */
    // Initialize Map
    playArea = newwin(MAP_HEIGHT, MAP_WIDTH, 0, 10);
    // Create border around map
    box(playArea, 0, 0);
    // Load Level 1 Map
    currentMap = map_1(playArea);
    // Initialize actors and assign it to map
    victim v = createVictim(currentMap);
    // Loops to catch key input, i also planned to add AI (Guards, Moving Particles) to this area.
    // The pattern may not the best pattern as i bruteforce it. It's agile ;). Suggestions are welcome
    // And yess, currently you have to press control + c to exit
    while(1) {
        // Catching keypress and Delegate it to Actor.
        keyPress(currentMap, &v);
    }
    // Clear Created Window
    delwin(playArea);
    endwin();
}

void keyPress(map m, victim *v) {
    // Catch pressed keys without interupting the program
    int key = getch();
    // Parse pressed keys
    switch(key) {
        case 'A':
            moveVictim(m, v, MOVE_UP);
            break;
        case 'D':
            moveVictim(m, v, MOVE_LEFT);
            break;
        case 'C':
            moveVictim(m, v, MOVE_RIGHT);
            break;
        case 'B':
            moveVictim(m, v, MOVE_DOWN);
            break;

    }
}
