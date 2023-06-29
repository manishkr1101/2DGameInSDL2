#pragma once

#include "ECS.h"
#include "TranformComponent.h"
#include "SpriteComponent.h"

class TileComponent : public Component {
public:
	TransformComponent* tranform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tileRect = { x, y , w, h };
		tileID = id;

		switch (tileID) {
		case 0:
			path = Constant::DIRT_SPRITE; 
			break;
		case 1:
			path = Constant::GRASS_SPRITE;
			break;
		case 2:
			path = Constant::WATER_SPRITE;
			break;
		}
	}

	void init() override {
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h);
		tranform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
		okay("SpriteComponent got added to Tile with path: %s", path);
	}

};
