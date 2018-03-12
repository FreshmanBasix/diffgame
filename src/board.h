#ifndef BOARD_H
#define BOARD_H
#include <stdlib.h>
#include "block.h"
#include "SDL2/SDL.h"

#define BOARD_ROWS		30
#define BOARD_COLUMNS	30

#define RED_SPLIT 		RAND_MAX/5
#define GREEN_SPLIT		(RAND_MAX/5)*2
#define BLUE_SPLIT		(RAND_MAX/5)*3
#define YELLOW_SPLIT	(RAND_MAX/5)*4
#define ORANGE_SPLIT	RAND_MAX

typedef struct _Board {
	SDL_Rect *board;
	Block* blocks[BOARD_ROWS * BOARD_COLUMNS];
} Board;

Board* createBoard(void);
void destroyBoard(Board *brd);
void populateBoard(Board *brd, int lvl);
void drawBoard(SDL_Renderer **rend, Board *brd);
#endif
