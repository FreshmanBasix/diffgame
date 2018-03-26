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
	populateBoard(game->state.currentBoard);
	game->state.quit = false;
}

static bool isGameOver(Board *board)
{
	/* Since this is only called if there are no more moves
	 * on board, we can check for game over by checking if
	 * the top row of the board has been filled with blocks */
	for (int i = 0; i < BOARD_COLUMNS; ++i) {
		if (board->blocks[0][i] == NULL)
			return false;
	}

	return true;
}

static void nextLevel(struct _Game *game)
{
	Board *currentBoard = game->state.currentBoard;
	
	/* Start by freezing all remaing blocks on board */
	freezeBlocks(currentBoard);

	/* Return if game over */
	if (isGameOver(currentBoard)) {
		game->state.gameOver = true;
		return;
	}

	if (currentBoard->currentLevel >= BOARD_MAX_LEVEL)
		currentBoard->currentLevel = BOARD_MAX_LEVEL;
	else
		currentBoard->currentLevel++;

	populateBoard(currentBoard);
}

void updateGameStatus(struct _Game *game)
{
	if (game->state.gameOver)
		return;
	/* If no more moves, go to next level */
	if (noMoreMoves(game->state.currentBoard)) {
		nextLevel(game);
	}

}
