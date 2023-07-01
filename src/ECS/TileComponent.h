#pragma once

#include "ECS.h"
#include "../TextureManager.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		destRect = { xpos, ypos, 64, 64 };
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
