#include <stdbool.h>
#include "system.h"

bool system_init(SDL_Window **win, SDL_Renderer **rend)
{
	/* Initialize SDL Subsystems */
	int sdl_init_flags = SDL_INIT_VIDEO;
	if ((SDL_Init(sdl_init_flags)) < 0) {
		fprintf(stderr, "Could not initialize SDL! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if (!initializeImageLoading()) {
		fprintf(stderr, "Could not initialize image library!\n");
		SDL_Quit();
		return false;
	}

	*win = SDL_CreateWindow(
			"diffgame",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 0);
	if(win == NULL) {
		fprintf(stderr, "Could not create window! SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	*rend = SDL_CreateRenderer(*win, -1, renderer_flags);
	if(rend == NULL) {
		fprintf(stderr, "Could not create renderer! SDL Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(*win);
		SDL_Quit();
		return false;
	}

	return true;
}

bool initializeImageLoading()
{
	int image_init_flags, initted;
	image_init_flags = IMG_INIT_PNG;
	initted = IMG_Init(image_init_flags);
	if ((initted&image_init_flags) != image_init_flags) {
		fprintf(stderr, "Could not initialize IMG! IMG Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

SDL_Texture* loadTexture(SDL_Renderer *rend, const char *path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *tmpSurface = NULL;

	tmpSurface = IMG_Load(path);
	newTexture = SDL_CreateTextureFromSurface(rend, tmpSurface);
	if (newTexture == NULL) {
		fprintf(stderr, "Failed to load image at %s! IMG Error: %s\n", path, IMG_GetError());
	}
	SDL_FreeSurface(tmpSurface);

	return newTexture;
}


