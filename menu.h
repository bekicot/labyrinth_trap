//
// Created by Yana Agun Siswanto on 12/6/16.
//

#ifndef LABIRIN_TRAP_MENU_H
#define LABIRIN_TRAP_MENU_H

#include <menu.h>
typedef struct Menu *address_menu;

typedef struct Menu {
    char *name;
    address_menu next;
} menu;

int menuCount(menu Menu);
void appendMenu(address_menu Menu, char *name);
address_menu createMenu(char *name);

void createNcursesMenuItemFromMenu(ITEM **ncursesItem, menu Menu, void *handler);

//Untuk debugging ;)
void debugMenu(address_menu Menu);

#endif //LABIRIN_TRAP_MENU_H
