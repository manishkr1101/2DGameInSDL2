#pragma once
#include "ECS.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
		
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 128;
		destRect.w = destRect.h = 64;
	}

	void update() override {
		destRect.x = (int) transform->position.x;
		destRect.y = (int) transform->position.y;
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