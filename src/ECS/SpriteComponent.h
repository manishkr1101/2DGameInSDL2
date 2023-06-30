#pragma once
#include "ECS.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	SpriteComponent(const char* path, int frames, int speed) {
		texture = TextureManager::LoadTexture(path);
		animated = true;
		this->frames = frames;
		this->speed = speed;
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int> ((SDL_GetTicks() / speed) % frames);
		}

		destRect.x = (int) transform->position.x;
		destRect.y = (int) transform->position.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
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