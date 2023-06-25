#pragma once
#include "ECS.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
		
	}

	void init() override {
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 128;
		destRect.w = destRect.h = 64;
	}

	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void setTex(const char* texPath) {
		setTex(TextureManager::LoadTexture(texPath));
	}

	void setTex(SDL_Texture* tex) {
		texture = tex;
	}
};