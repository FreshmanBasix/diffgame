#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "board.h"

struct _Game {
	SDL_Window *mainWindow;
	SDL_Renderer *mainRenderer;
	struct {
		bool quit;
		bool gameOver;
		Board *currentBoard;
	} state;
};

/* Global game struct */
extern struct _Game gGame;

/* Initializes game struct */
void initGame(struct _Game *game);

/* Updates levels, items etc. */
void updateGameStatus(struct _Game *game);

#endif
