#ifndef BOARD_H
#define BOARD_H
#include <stdlib.h>
#include "block.h"
#include "SDL2/SDL.h"

#define BOARD_ROWS		15
#define BOARD_COLUMNS	15

#define RED_SPLIT 		RAND_MAX/5
#define GREEN_SPLIT		(RAND_MAX/5)*2
#define BLUE_SPLIT		(RAND_MAX/5)*3
#define YELLOW_SPLIT	(RAND_MAX/5)*4
#define ORANGE_SPLIT	RAND_MAX

typedef struct _Board {
	SDL_Rect *board;
	int seed;
	Block* blocks[BOARD_ROWS][BOARD_COLUMNS];
	bool blockMap[BOARD_ROWS][BOARD_COLUMNS];
} Board;

/* Allocates memory and creates an empty board */
Board* createBoard(void);

/* Frees all memory allocated in Board struct brd */
void destroyBoard(Board *brd);

/* Populates board brd with blocks based on level lvl */
void populateBoard(Board *brd, int lvl);

/* Draws board brd to renderer rend */
void drawBoard(SDL_Renderer **rend, Board *brd);

/* Selects all similar blocks that are "chained" based on initial
 * block (index of block on board) */
void selectBlocks(Board *board, int blockCol, int blockRow);

/* Recursively search board depth-first to find connected blocks, should be treated as
 * a private function, and only be called from non-static functions */
//static void selectBlock(Board *board, int blockCol, int blockRow, BlockColor color);
#endif
