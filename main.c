#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stdarg.h>
#include "menu.h"
#include "mapCreator/mapCreator.h"

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
void drawOnMain(char character, int y, int x) {
    mvwaddch(mainWindow, y, x, character);
    wrefresh(mainWindow);
}
void removeOnMain(int y, int x){
    mvwaddch(mainWindow, y, x, ' ');
    wrefresh(mainWindow);
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
int validatePeta(map Peta) {
    if(!Peta.in)
        return 1;
    if(!Peta.out)
        return 2;
    return 0;
}

void drawUsingKey(int key, int *y, int *x) {
    switch(key){
        case KEY_UP:
            endwin();
            (*y)--;
            mvwaddch(mainWindow, *y, *x, '0');
            break;
        case KEY_DOWN:
            *y = *y + 1;
            mvwaddch(mainWindow, *y, *x, '0');
            break;
        case KEY_RIGHT: {
            *x = *x + 1;
            mvwaddch(mainWindow, *y, *x, '0');
            break;
        }
        case KEY_LEFT: {
            *x = *x - 1;
            mvwaddch(mainWindow, *y, *x, '0');
            break;
        }
    }
    wrefresh(mainWindow);
}

//void drawPixel(list *yangSudahDiDraw, )

int main() {


    ITEM **ncurses_menu_item;

    MENU *ncurses_menu_utama;

    address_menu menu_utama = createMenu("Main");

    appendMenu(menu_utama, "Buat Peta");
//    appendMenu(menu_utama, "Peta 1");
//    appendMenu(menu_utama, "Peta 2");

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

    menuWindow = createNewwin(WINDOW_MAX_HEIGHT , 30, WINDOW_MIN_TOP, WINDOW_MIN_LEFT + 80);
    mainWindow = createNewwin(WINDOW_MAX_HEIGHT, 80, WINDOW_MIN_TOP, WINDOW_MIN_LEFT);
    tooltips   = createNewwin(5, 110, WINDOW_MIN_TOP + 41, WINDOW_MIN_LEFT);

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
    int drawing = 0;
    int sedangBuatPeta = 0;
    int setPintuMasuk = 0;
    int setPintuKeluar = 0;
    address lastPixel;
    coordinate currentCursor;
    WINDOW *windows[2] = { menuWindow, mainWindow };

    sendTooltips("tekan atas bawah untuk memilih menu lalu tekan enter; f1 untuk keluar");
    while((c = wgetch(windows[mode])) != KEY_F(1))
    {
        if(strcmp(selectedMenu, "Buat Peta") == 0){
            map petaBaru;
            if(!sedangBuatPeta){
                createEmptyMap(&petaBaru, 80, 40);
                sedangBuatPeta = 1;
            }
            switch(validatePeta(petaBaru)) {
                case 1:
                    sendTooltips("Tekan 'M' dan klik lokasi untuk menentukan pintu masuk");
                    break;
                default :
                    sendTooltips("Tekan 'Spasi' untuk pause/mulai membuat jalur; tekan 'k' dan arahkan ke salah satu wilayah dengan '0' untuk menentukan pintu keluar; tekan double 'esc' untuk selesai;");
                    break;
            }
            switch(c) {
                case 32:
                    if(drawing){
                        drawing = 0;
                    } else {
                        drawing = 1;
                    }
                    break;
                case 115:
                    drawing = 0;
                    break;
                case  100:
                    drawing = 2;
                    break;
                case 112:
                    drawing = 3;
                case KEY_MOUSE: {
                    MEVENT event;
                    getmouse(&event);
                    if(wmouse_trafo(mainWindow, &event.y, &event.x, false)){
                       if(drawing == 1){
                           if(lastPixel != NULL) {
                               drawOnMain('0', event.y, event.x);
                               if(lastPixel->position.x > event.x){
                                   addRight(&petaBaru, lastPixel->position.x, lastPixel->position.y);
                               }else{
                                   addLeft(&petaBaru, lastPixel->position.x, lastPixel->position.y);
                               }
                               if(lastPixel->position.y > event.y){
                                   addBottom(&petaBaru, lastPixel->position.x, lastPixel->position.y);
                               } else {
                                   addTop(&petaBaru, lastPixel->position.x, lastPixel->position.y);
                               }
                           }
                       }
                        if(drawing == 2)
                            removeOnMain(event.y, event.x);
                        if(event.bstate == BUTTON1_CLICKED || event.bstate == BUTTON1_PRESSED) {
                            if(setPintuMasuk){
                                createIn(&petaBaru, event.x, event.y);
                                drawing = 1;
                                setPintuMasuk = 0;
                                lastPixel = petaBaru.in;
                            }
                            if(setPintuKeluar){
                               setOut(&petaBaru, search(petaBaru, event.x, event.y));
                                if(search(petaBaru,event.x, event.y)) {
                                    sendTooltips("blah");
                                }
                                setPintuKeluar = 0;
                            }
                        }

                    }
                    break;
                }
                case 27 : {
                    switch(validatePeta(petaBaru)){
                        case 1:
                            sendTooltips("Hey, peta belum ada pintu masuk");
                            break;
                        case 2:
                            sendTooltips("Hey, peta belum ada pintu keluar");
                            break;
                    }
                    if(validatePeta(petaBaru) > 0){

                    }
                }
                case 109:
                    setPintuMasuk = 1;
                    drawing = 0;
                    break;
                case 107:
                    setPintuKeluar = 1;
                    drawing = 0;
                    break;

            }
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
                    ITEM *cur;
                    void (*p)(char *);
                    cur = current_item(ncurses_menu_utama);
                    p = item_userptr(cur);
                    p((char *)item_name(cur));
                    pos_menu_cursor(ncurses_menu_utama);
                    if(selectedMenu == "Buat Peta")
                        sendTooltips("Tekan 'M' dan klik lokasi untuk menentukan pintu masuk");
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
