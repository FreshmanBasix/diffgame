#include "block.h"
#include "system.h"
#include "game.h"

/* Global struct to keep block textures */
struct _BlockTextures gBlockTextures;

Block* createBlock(int x, int y, BlockColor color, SDL_Texture* texture)
{
	Block *newBlock = (Block*) malloc(sizeof(Block));

	newBlock->color = color;
	newBlock->texture = texture;

	newBlock->block.h = BLOCK_SIZE_HEIGHT;
	newBlock->block.w = BLOCK_SIZE_WIDTH;
	newBlock->block.x = x;
	newBlock->block.y = y;

	return newBlock;
}

void destroyBlock(Block *block)
{
	free(block);
}

void loadBlockTextures(void) {
	gBlockTextures.plainBlock = loadTexture(gGame.mainRenderer, "./art_assets/block/plainblock.png");
	if (gBlockTextures.plainBlock == NULL) {
		fprintf(stderr, "Failed to load plainblock texture\n");
		/* Fallback texture here */
	}
}
