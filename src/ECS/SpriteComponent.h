#pragma once
#include "ECS.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	std::map<const char*, Animation> animations;

public:
	int animIndex = 0;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	SpriteComponent() = default;

	SpriteComponent(const char* path) {
		setTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated) {
		setTex(path);
		animated = isAnimated;

		animations.emplace("idle", Animation(0, 3, 100));
		animations.emplace("walk", Animation(1, 8, 150));
		
		play("idle");
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

		srcRect.y = animIndex * transform->height;

		destRect.x = (int) transform->position.x;
		destRect.y = (int) transform->position.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

	void setTex(const char* texPath) {
		setTex(TextureManager::LoadTexture(texPath));
	}

	void setTex(SDL_Texture* tex) {
		texture = tex;
	}
};