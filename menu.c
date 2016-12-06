//
// Created by Yana Agun Siswanto on 12/6/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"

address_menu createMenu(char *name) {
    address_menu menuBaru = (address_menu) malloc(sizeof(menu));
    if(menuBaru == NULL) {
        printf("Galat; Ga bisa malloc");
        exit(1);
    }
    menuBaru->name = name;
    menuBaru->next = NULL;
    return menuBaru;
}

void appendMenu(address_menu Menu, char *name) {
    if(Menu->next == NULL){
        Menu->next = createMenu(name);
    } else {
        appendMenu(Menu->next, name);
    }
}

int menuCount(menu Menu) {
    if(Menu.next != NULL) {
        return 1 + menuCount(*Menu.next);
    } else {
        return 1;
    }
}

void createNcursesMenuItemFromMenu(ITEM **ncursesItem, menu Menu, void *handler){
    address_menu tmp = &Menu;
    int m_count = menuCount(Menu);
    for(int i = 0; i < m_count ; i++) {
        ncursesItem[i] = new_item(tmp->name, tmp->name);
        tmp = tmp->next;
        set_item_userptr(ncursesItem[i], handler);
    }
}

void debugMenu(address_menu Menu) {
    printf("%s\n", Menu->name);
    if(Menu->next != NULL) {
        debugMenu(Menu->next);
    }
}

