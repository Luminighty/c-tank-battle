#ifndef GAMESTATE_MENU_H
#define GAMESTATE_MENU_H


typedef void (*OnMenuClickedCallback)(void*);


typedef struct {
    const char* label;
    OnMenuClickedCallback callback;
} MenuOption;


typedef struct {
    int option_count;
    MenuOption options[8];
} GameStateMenu;


#endif // GAMESTATE_TURN_MENU_H
