#ifndef GAMESTATE_GAMEOVER_H
#define GAMESTATE_GAMEOVER_H


typedef struct {
    int winner;
} GameStateGameOver;


void gamestate_gameover_enter(int winner);
void gamestate_gameover_update();

#endif // GAMESTATE_GAMEOVER_H
