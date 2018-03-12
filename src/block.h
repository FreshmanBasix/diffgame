#ifndef BLOCK_H
#define BLOCK_H
#include "SDL2/SDL.h"

#define BLOCK_SIZE_WIDTH 15
#define BLOCK_SIZE_HEIGHT 15

struct _BlockTextures {
	SDL_Texture *plainBlock;
};

extern struct _BlockTextures gBlockTextures;

typedef enum {
	SPECIAL,
	WHITE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	ORANGE
} BlockColor;

typedef struct _Block {
	SDL_Rect block;
	BlockColor color;
	SDL_Texture *texture;
} Block;

Block* createBlock(int x, int y, BlockColor color, SDL_Texture* texture);
void destroyBlock(Block *block);
void loadBlockTextures(void);
#endif
