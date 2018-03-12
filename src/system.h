#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define WINDOW_SIZE_HEIGHT 600
#define WINDOW_SIZE_WIDTH 800

/* Initializes SDL Subsystems, returns true on success, false otherwise.
 * Also destroys renderer/window etc on failure. */
bool system_init(SDL_Window **win, SDL_Renderer **rend);

/* Initalize SDL_image, returns true on success, false otherwise. */
bool initializeImageLoading();

SDL_Texture* loadTexture(SDL_Renderer *rend, const char *path);
#endif
