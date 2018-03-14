#include "board.h"
#include "block.h"

Board* createBoard(void)
{
	Board *newBoard = (Board*) malloc(sizeof(Board));
	return newBoard;
}

void destroyBoard(Board *brd)
{
	/* TODO IMPORTANT Free all block pointers */
	free(brd->blocks);
	free(brd);
}

/* Fill the block array in board with random blocks based on level */
void populateBoard(Board *brd, int lvl) {

	/* TODO */
	/* Get random content based on level
	 * (i.e. How many different colors of blocks, special blocks etc.) */
	switch (lvl) {
		case 1:
			break;
		default:
			break;
	}

	int blockx, blocky;
	int split;
	BlockColor color;
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			Block *tmpBlock = (Block*) malloc(sizeof(Block));

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

			blockx = i * BLOCK_SIZE_HEIGHT;
			blocky = j * BLOCK_SIZE_WIDTH;
			tmpBlock = createBlock(blockx, blocky, color, gBlockTextures.plainBlock);
			brd->blocks[i][j] = tmpBlock;
		}
	}
}

void drawBoard(SDL_Renderer **rend, Board *board) {
	Block *tmpBlock;
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			tmpBlock = board->blocks[i][j];
			/* TODO Should this really be set here? */
			tmpBlock->selected = board->blockMap[i][j];
			drawBlock(*rend, tmpBlock);
		}
	}
}

/* Recursively get all blocks depth-first that match color */
static void selectBlock(Board *board, int x, int y, BlockColor color)
{
	printf("Selecting block [%d][%d]\n", y, x);
	printf("current color: %d, target color: %d\n", board->blocks[x][y]->color, color);
	
	/* Return if wrong color || already marked || illegal coordinates */
	if (board->blocks[y][x]->color != color
		|| board->blockMap[y][x]
		|| x < 0
		|| x >= BOARD_COLUMNS
		|| y < 0
		|| y >= BOARD_ROWS
	) return;
	else board->blockMap[y][x] = true;

	/* Search left, up, right, down */

	if (x > 0) // check if at left border
		selectBlock(board, (x - 1), y, color);
	if (x < BOARD_COLUMNS - 1) // check if at right border
		selectBlock(board, (x + 1), y, color);
	if (y > 0) // check if at top border
		selectBlock(board, x, (y - 1), color);
	if (y < BOARD_ROWS - 1) // check if at bottom border
		selectBlock(board, x, (y + 1), color);
}

/* Recursively selects all connected blocks based on one block (index) */
void selectBlocks(Board *board, int x, int y)
{
	/* "clear" blockMap, set all blocks as false */
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			board->blockMap[i][j] = false;
		}
	}

	/* Get color to match blocks with */
	BlockColor color = board->blocks[y][x]->color;

	selectBlock(board, x, y, color);
}
