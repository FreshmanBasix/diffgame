#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include "block.h"
#include "SDL2/SDL.h"

#define BOARD_OFFSET_X 0
#define BOARD_OFFSET_Y 0

#define BOARD_ROWS		15
#define BOARD_COLUMNS	15

#define BOARD_MIN_LEVEL 1
#define BOARD_MAX_LEVEL 3

#define POPULATION_DELAY 8

#define RED_SPLIT 		RAND_MAX/5
#define GREEN_SPLIT		(RAND_MAX/5)*2
#define BLUE_SPLIT		(RAND_MAX/5)*3
#define YELLOW_SPLIT	(RAND_MAX/5)*4
#define ORANGE_SPLIT	RAND_MAX

typedef struct _Board {
	SDL_Rect *board;
	int seed;
	int currentLevel;

	Block *blocks[BOARD_ROWS][BOARD_COLUMNS];
	bool blockMap[BOARD_ROWS][BOARD_COLUMNS];
	bool connectMap[BOARD_ROWS][BOARD_COLUMNS];

	bool updating;
	bool populating;
	int num_updating_blocks;
	int num_selected;
} Board;

/* Allocates memory and creates an empty board */
Board* createBoard(void);

/* Frees all memory allocated in Board struct brd */
void destroyBoard(Board *board);

/* Populates board brd with blocks based on level lvl */
void populateBoard(Board *board);

/* Draws board brd to renderer rend */
void drawBoard(SDL_Renderer **rend, Board *brd);

/* Recursively search board depth-first to find connected blocks, should be treated as
 * a private function, and only be called from non-static functions */
//static void selectBlock(Board *board, int blockCol, int blockRow, BlockColor color);

/* Selects all similar blocks that are "chained" based on initial
 * block (index of block on board) */
void selectBlocks(Board *board, int x, int y);

/* Find out if there is a block at coordinates x and y */
bool blockAtPos(Board *board, int posx, int posy);

/* Find out if position (x, y) is inside board */
bool positionWithinBoard(int x, int y);

/* Destroys selected blocks connected from block at position x and y */
void destroyBlocks(Board *board);

/* Deselects all blocks, returning them to normal state */
void deselectAllBlocks(Board *board);

/* Sinks all blocks to correct position on board */
void sinkBlocks(Board *board);

/* Update all blocks that are still updating, if no blocks are updated
 * then set board to no longer updating */
void updateBoard(Board *board);

/* Checks if there are no more moves to be made on board */
bool noMoreMoves(Board *board);

/* Freezes all blocks on board */
void freezeBlocks(Board *board);

#endif
