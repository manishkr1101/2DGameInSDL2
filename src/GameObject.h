#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "../util/log.h"

class GameObject {
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:

	int xPos;
	int yPos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
