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

void drawBlock(SDL_Renderer *rend, Block *block) {
	uint8_t color_r, color_g, color_b;
	switch(block->color) {
		case RED:
			color_r = RED_R;
			color_g = RED_G;
			color_b = RED_B;
			break;
		case GREEN:
			color_r = GREEN_R;
			color_g = GREEN_G;
			color_b = GREEN_B;
			break;
		case BLUE:
			color_r = BLUE_R;
			color_g = BLUE_G;
			color_b = BLUE_B;
			break;
		case YELLOW:
			color_r = YELLOW_R;
			color_g = YELLOW_G;
			color_b = YELLOW_B;
			break;
		case ORANGE:
			color_r = ORANGE_R;
			color_g = ORANGE_G;
			color_b = ORANGE_B;
			break;
		default:
			/* Set default to WHITE */
			color_r = 255;
			color_g = 255;
			color_b = 255;
			break;
	}

	SDL_SetTextureColorMod(block->texture, color_r, color_g, color_b);
	SDL_RenderCopy(rend, block->texture, NULL, &block->block);
}
