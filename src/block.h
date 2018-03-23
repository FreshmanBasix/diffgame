#ifndef BLOCK_H
#define BLOCK_H
#include <stdbool.h>
#include "SDL2/SDL.h"

#define BLOCK_SIZE_WIDTH 30
#define BLOCK_SIZE_HEIGHT 30

#define BLOCK_ACCELERATION 2
#define BLOCK_MAX_VELOCITY 20

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
#define RED_R 0xCA
#define RED_G 0x3B
#define RED_B 0x35

#define GREEN_R 0x8A
#define GREEN_G 0xC1
#define GREEN_B 0x3C

#define BLUE_R 0x00
#define BLUE_G 0x75
#define BLUE_B 0xC4

#define YELLOW_R 0xF9
#define YELLOW_G 0xCE
#define YELLOW_B 0x20

#define ORANGE_R 0xE8
#define ORANGE_G 0x90
#define ORANGE_B 0x2C

typedef struct _Block {
	SDL_Rect block;
	BlockColor color;
	SDL_Texture *texture;
	bool selected;
	bool updating;
	int velocity;
	int targetX;
	int targetY;
} Block;

Block* createBlock(int x, int y, BlockColor color, SDL_Texture* texture);
void destroyBlock(Block *block);
void loadBlockTextures(void);
void drawBlock(SDL_Renderer *rend, Block *block);
void updateBlock(Block *block);

#endif
