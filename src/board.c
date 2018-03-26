#include <time.h>
#include <stdbool.h>
#include "board.h"
#include "block.h"

Board* createBoard(void)
{
	/* Allocate memory for board and initialize blocks array
	 * to only contain null pointers (destroyBoard will probably crash if non-null) */
	Board *newBoard = (Board*) malloc(sizeof(Board));
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			newBoard->blocks[i][j] = NULL;
			newBoard->blockMap[i][j] = false;
		}
	}

	/* Set a random seed for the board used when generating random stuff,
	 * based on unix time in seconds */
	srand(time(NULL));
	newBoard->seed = rand();
	srand(newBoard->seed);

	newBoard->updating = false;

	return newBoard;
}

void destroyBoard(Board *board)
{
	/* Free all blocks */
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			free(board->blocks[i][j]);
		}
	}
	/* Free blocks array (not sure if needed) */
	free(board->blocks);
	/* Free board */
	free(board);
}

/* Fill the block array in board with random blocks based on level */
void populateBoard(Board *board)
{
	int lvl, lvlBreak;

	board->updating = true;

	bool allPopulated = true;

	if (board->currentLevel < BOARD_MIN_LEVEL)
		board->currentLevel = BOARD_MIN_LEVEL;
	else if (board->currentLevel > BOARD_MAX_LEVEL)
		board->currentLevel = BOARD_MAX_LEVEL;

	lvl = board->currentLevel;

	/* lvlBreak should indicate what blocks are going to be included in the
	 * current level, by capping rand-values to certain color caps */
	switch (lvl) {
		case 1:
			lvlBreak = BLUE_SPLIT;		// Level 1 are only red, green and blue
			break;
		case 2:
			lvlBreak = YELLOW_SPLIT;	// Level 2 includes yellow blocks
			break;
		case 3:
			lvlBreak = ORANGE_SPLIT;	// Level 3 includes orange blocks TODO special blocks
			break;
		case 4:
			break;
		default:
			break;
	}

	int blockx, blocky;
	int split;
	BlockColor color;
	/* Creates a new row of blocks, skips columns that are full */
	for (int j = 0; j < BOARD_COLUMNS; ++j) {
		if (board->blocks[0][j] != NULL)
			continue;
		else
			allPopulated = false;

		Block *tmpBlock;
		split = rand() % lvlBreak;		// level specific block colors
		if (split < RED_SPLIT)
			color = RED;
		else if (split < GREEN_SPLIT)
			color = GREEN;
		else if (split < BLUE_SPLIT)
			color = BLUE;
		else if (split < YELLOW_SPLIT)
			color = YELLOW;
		else if (split < ORANGE_SPLIT)
			color = ORANGE;
		else
			color = WHITE; // error color

		blockx = j * BLOCK_SIZE_WIDTH;
		blocky = 0 * BLOCK_SIZE_HEIGHT;
		tmpBlock = createBlock(blockx, blocky, color, gBlockTextures.plainBlock);
		tmpBlock->updating = true;
		board->blocks[0][j] = tmpBlock;
	}

	if (allPopulated) {
		board->populating = false;
	} else {
		board->populating = true;
		sinkBlocks(board);
	}
}

void drawBoard(SDL_Renderer **rend, Board *board) {
	Block *tmpBlock;
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			tmpBlock = board->blocks[i][j];
			/* Check if block is removed */
			if (tmpBlock == NULL)
				continue;
			/* TODO Should this really be set here? */
			tmpBlock->selected = board->blockMap[i][j];
			drawBlock(*rend, tmpBlock);
		}
	}
}

/* Recursively get all blocks depth-first that match color and return number of selected blocks,
 * depending on selectOption results will either be marked in selection map or counting map */
static int selectBlock(Board *board, int x, int y, BlockColor color, bool selectOption)
{
	int sum = 0;

	/* Return if
	 * no block || block frozen || wrong color ||
	 * already marked || illegal coordinates */
	if (selectOption) {
		if (board->blockMap[y][x] == true)
			return sum;
	} else {
		if (board->connectMap[y][x] == true)
			return sum;
	}

	if (board->blocks[y][x] == NULL
		|| board->blocks[y][x]->color == FROZEN
		|| board->blocks[y][x]->color != color
		|| x < 0
		|| x >= BOARD_COLUMNS
		|| y < 0
		|| y >= BOARD_ROWS
	) return sum;
	else {
		if (selectOption)
			board->blockMap[y][x] = true;
		else
			board->connectMap[y][x] = true;
		sum++;
	}

	/* Search left, up, right, down */

	if (x > 0) // check if at left border
		sum += selectBlock(board, (x - 1), y, color, selectOption);
	if (x < BOARD_COLUMNS - 1) // check if at right border
		sum += selectBlock(board, (x + 1), y, color, selectOption);
	if (y > 0) // check if at top border
		sum += selectBlock(board, x, (y - 1), color, selectOption);
	if (y < BOARD_ROWS - 1) // check if at bottom border
		sum += selectBlock(board, x, (y + 1), color, selectOption);

	return sum;
}

/* Recursively selects all connected blocks based on one block (index), only if 
 * number of blocks are greater than one */
void selectBlocks(Board *board, int x, int y)
{
	/* "clear" blockMap */
	deselectAllBlocks(board);

	/* Get color to match blocks with */
	Block *tmpBlock;
	if ((tmpBlock = board->blocks[y][x]) == NULL) // make sure a block exists
		return;

	/* Only select if number of connected blocks are greater than or equal to two */
	/* TODO since this means only one block is selected, try
	 * deselecting the single block, instead of entire board */
	if (selectBlock(board, x, y, tmpBlock->color, true) < 2)
		deselectAllBlocks(board);
}

bool positionWithinBoard(int x, int y)
{
	if (x < BOARD_OFFSET_X
		|| x > (BOARD_OFFSET_X + (BLOCK_SIZE_WIDTH * BOARD_COLUMNS - 1))
		|| y < BOARD_OFFSET_Y
		|| y > (BOARD_OFFSET_Y + (BLOCK_SIZE_HEIGHT * BOARD_ROWS - 1))
	) return false;
	else return true;
}

bool blockAtPos(Board *board, int posx, int posy)
{
	int index_y, index_x;

	if (!positionWithinBoard(posx, posy))
		return false;

	index_x = posx / BLOCK_SIZE_WIDTH;
	index_y = posy / BLOCK_SIZE_HEIGHT;

	return board->blocks[index_y][index_x] != NULL;
}

/* Update new position for block at index x,y */
static void sinkBlock(Board *board, int x, int y)
{
	int newY = y;
	while (newY < BOARD_ROWS - 1 && board->blocks[newY + 1][x] == NULL)
		newY++;
	if (newY == y)
		return;

	if (board->blocks[newY][x] != NULL) {
		fprintf(stderr, "Can't sink block, position index [%d][%d] occupied, exiting\n", y, x);
		exit(1);
	} else {
		board->blocks[newY][x] = board->blocks[y][x];
		board->blocks[newY][x]->targetY = newY * BLOCK_SIZE_HEIGHT;
		board->blocks[y][x] = NULL;
	}
}

void sinkBlocks(Board *board)
{
	/* Go through blocks from bottom up */
	for (int y = BOARD_ROWS - 1; y >= 0; --y) {
		for (int x = 0; x < BOARD_COLUMNS; ++x) {
			if (board->blocks[y][x] && board->blocks[y][x]->updating) {
				sinkBlock(board, x, y);
			}
		}
	}
}

static void markColumnUpdating(Board *board, int col)
{
	for (int row = 0; row < BOARD_ROWS; ++row) {
		if (board->blocks[row][col])
			board->blocks[row][col]->updating = true;
	}
}

void destroyBlocks(Board *board)
{
	bool columnsAffected[BOARD_COLUMNS] = { false };

	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			/* Destroy all blocks that are selected */
			if (board->blockMap[i][j] == true) {
				destroyBlock(board->blocks[i][j]);
				board->blocks[i][j] = NULL;
				columnsAffected[j] = true;
			}
		}
	}

	for (int i = 0; i < BOARD_COLUMNS; ++i) {
		if (columnsAffected[i]) {
			markColumnUpdating(board, i);
		}
	}

	board->updating = true;
	sinkBlocks(board);
	deselectAllBlocks(board);
}

void deselectAllBlocks(Board* board)
{
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			board->blockMap[i][j] = false;
		}
	}
}

/* Update all blocks on board */
void updateBoard(Board *board)
{
	static int populateDelay = 0;

	bool allDone = true;

	Block *currentBlock = NULL;

	if (board->populating) {
		allDone = false;
		populateDelay++;
		if (populateDelay % POPULATION_DELAY == 0)
			populateBoard(board);
	}

	for (int y = 0; y < BOARD_ROWS; ++y) {
		for (int x = 0; x < BOARD_COLUMNS; ++x) {
			currentBlock = board->blocks[x][y];
			if (currentBlock != NULL && currentBlock->updating) {
				allDone = false;
				updateBlock(currentBlock);
			}
		}
	}

	board->updating = !allDone;
}

static int numberOfConnectedBlocks(Board *board, int x, int y)
{
	/* Clear connectMap */
	for (int y = 0; y < BOARD_ROWS; ++y) {
		for (int x = 0; x < BOARD_COLUMNS; ++x) {
			board->connectMap[y][x] = false;
		}
	}

	if (board->blocks[y][x] == NULL)
		return 0;
	/* Call selectBlock with selectOption false */
	int sum = selectBlock(board, x, y, board->blocks[y][x]->color, false);
	return sum;
}

bool noMoreMoves(Board *board)
{
	for (int y = 0; y < BOARD_ROWS; ++y) {
		for (int x = 0; x < BOARD_COLUMNS; ++x) {
			if (numberOfConnectedBlocks(board, x, y) > 1)
				return false;
		}
	}

	return true;
}

void freezeBlocks(Board *board)
{
	for (int y = 0; y < BOARD_ROWS; ++y) {
		for (int x = 0; x < BOARD_COLUMNS; ++x) {
			if (board->blocks[y][x] != NULL)
				freezeBlock(board->blocks[y][x]);
		}
	}
}
