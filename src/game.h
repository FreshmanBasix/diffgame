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
		Board *currentBoard;
	} state;
};

/* Global game struct */
extern struct _Game gGame;

void initGame(struct _Game *game);
#endif
