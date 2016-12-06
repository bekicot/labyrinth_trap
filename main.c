#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stdarg.h>
#include "menu.h"

#define WINDOW_MAX_HEIGHT 40
#define WINDOW_MIN_TOP    5
#define WINDOW_MIN_LEFT   5

//Mode

#define MENU_SELECT_MODE  0
#define PLAY_MODE         1

#define TOGGLE_MODE(mode)  mode ^= (mode + 2) / 2;


WINDOW *createNewwin(int height, int width, int starty, int startx);
WINDOW *mainWindow;
WINDOW *menuWindow;
WINDOW *tooltips;

int mode = 0;
void manageMenu(WINDOW *menuWindow, MENU *ncurses_menu_utama, int key);
char *selectedMenu = "INITIALSTRING";
void setSelectedMenu(char *selected){
    selectedMenu = selected;
}
void menuHandler(char *name)
{
    selectedMenu = name;
}
void sendTooltips(const char *format, ...){
    va_list args;
    char buffer[BUFSIZ];
    va_start(args, format);
    vsnprintf(buffer, sizeof buffer, format, args);
    va_end(args);

    int x, y;
    getmaxyx(tooltips, y,x);
    werase(tooltips);
    box(tooltips, 0, 0);
    mvwprintw(tooltips, y / 2, 2, buffer);
    wrefresh(tooltips);
}


int main() {


    ITEM **ncurses_menu_item;

    MENU *ncurses_menu_utama;

    address_menu menu_utama = createMenu("Main");

    appendMenu(menu_utama, "Buat Peta");
    appendMenu(menu_utama, "Peta 1");
//    appendMenu(menu_utama, "Peta 2");

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    menuWindow = createNewwin(WINDOW_MAX_HEIGHT - 5, 20, WINDOW_MIN_TOP, WINDOW_MIN_LEFT + 80);
    mainWindow = createNewwin(WINDOW_MAX_HEIGHT, 80, WINDOW_MIN_TOP, WINDOW_MIN_LEFT);
    tooltips   = createNewwin(5, 20, WINDOW_MIN_TOP + 35, WINDOW_MIN_LEFT + 80);

    keypad(menuWindow, TRUE);
    keypad(mainWindow, TRUE);

    ncurses_menu_item = (ITEM **)calloc(menuCount(*menu_utama) + 1, sizeof(ITEM *));
    createNcursesMenuItemFromMenu(ncurses_menu_item, *menu_utama, menuHandler);
    ncurses_menu_utama = new_menu((ITEM **) ncurses_menu_item);
    menu_opts_off(ncurses_menu_utama, O_SHOWDESC);

    set_menu_win(ncurses_menu_utama, menuWindow);
    set_menu_sub(ncurses_menu_utama, derwin(menuWindow, 6, 38, 3, 2));

    post_menu(ncurses_menu_utama);
    wrefresh(menuWindow);
    int c;

    WINDOW *windows[2] = { menuWindow, mainWindow };

    while((c = wgetch(windows[mode])) != KEY_F(1))
    {
        if(strcmp(selectedMenu, "Buat Peta") == 0){
            endwin();
        } else {
            switch(c)
            {
                case KEY_DOWN:
                    menu_driver(ncurses_menu_utama, REQ_DOWN_ITEM);
                    break;
                case KEY_UP:
                    menu_driver(ncurses_menu_utama, REQ_UP_ITEM);

                    break;
                case 10 : {
                    sendTooltips("enter");
                    ITEM *cur;
                    void (*p)(char *);
                    cur = current_item(ncurses_menu_utama);
                    p = item_userptr(cur);
                    p((char *)item_name(cur));
                    pos_menu_cursor(ncurses_menu_utama);
                    break;
                }
            }

        }

    }

    return 0;
}

WINDOW *createNewwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);
    return local_win;
}

