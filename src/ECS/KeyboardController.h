#pragma once

#include "../Game.h"
#include "ECS.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("walk");
				break;
			default:
				break;
			}
		} 
		else if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("idle");
				break;
			case SDLK_a:
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}
	}
};
