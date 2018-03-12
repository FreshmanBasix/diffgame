#ifndef BLOCK_H
#define BLOCK_H
#include "SDL2/SDL.h"

#define BLOCK_SIZE_WIDTH 18
#define BLOCK_SIZE_HEIGHT 18

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

/* List of RGB codes for all Block Colors */
#define RED_R 255
#define RED_G 0
#define RED_B 0

#define GREEN_R 0
#define GREEN_G 255
#define GREEN_B 0

#define BLUE_R 0
#define BLUE_G 0
#define BLUE_B 255

#define YELLOW_R 255
#define YELLOW_G 255
#define YELLOW_B 0

#define ORANGE_R 255
#define ORANGE_G 150
#define ORANGE_B 0

typedef struct _Block {
	SDL_Rect block;
	BlockColor color;
	SDL_Texture *texture;
} Block;

Block* createBlock(int x, int y, BlockColor color, SDL_Texture* texture);
void destroyBlock(Block *block);
void loadBlockTextures(void);
void drawBlock(SDL_Renderer *rend, Block *block);
#endif
