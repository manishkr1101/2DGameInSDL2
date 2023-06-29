#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);
	if (objTexture == NULL)
		err("Texture can not be loaded from %s. Error: %s", textureSheet, SDL_GetError());

	xPos = x;
	yPos = y;
	srcRect = { 0, 0, 128, 128 };
	destRect = { 0 };
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	xPos++;
	destRect = { xPos, yPos, 2 * srcRect.w, 2 * srcRect.h };
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
