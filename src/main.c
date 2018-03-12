#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "game.h"
#include "system.h"
#include "block.h"

void handleKeyDownEvent(SDL_Event *event)
{
	switch (event->key.keysym.sym) {
		case SDLK_q:
			gGame.state.quit = true;
			break;
	}
}

/* Handle things that need to be done on quit, also quits SDL Subsystems */
void quit(struct _Game *game);

int main(void)
{
	/* Initialize system, create window and renderer */
	if (!system_init(&gGame.mainWindow, &gGame.mainRenderer)) {
		fprintf(stderr, "Could not initialize game, exiting.\n");
		exit(1);
	}

	initGame(&gGame);

	SDL_Event event;
	/* Main loop */
	while (!gGame.state.quit) {

		/* Event handling */
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					handleKeyDownEvent(&event);
					break;
			}
		}

		/* Render */
		SDL_SetRenderDrawColor(gGame.mainRenderer, 23, 23, 23, 255);
		SDL_RenderClear(gGame.mainRenderer);
		drawBoard(&gGame.mainRenderer, gGame.state.currentBoard);
		SDL_RenderPresent(gGame.mainRenderer);
	}

	quit(&gGame);

	return 0;
}

void quit(struct _Game *game)
{
	/* Close open files if any */

	/* Free memory/surfaces if any */

	/* Quit SDL Subsystems */
	IMG_Quit();
	SDL_DestroyRenderer(game->mainRenderer);
	SDL_DestroyWindow(game->mainWindow);
	SDL_Quit();
}
