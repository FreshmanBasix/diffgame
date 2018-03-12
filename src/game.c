#include "game.h"
#include "board.h"
#include "block.h"

/* Global game struct */
struct _Game gGame;

/* Initializes game state and creates a new board */
void initGame(struct _Game *game)
{
	loadBlockTextures();
	game->state.currentBoard = createBoard();
	populateBoard(game->state.currentBoard, 1);
	game->state.quit = false;
}
