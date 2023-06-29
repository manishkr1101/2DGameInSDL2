#pragma once
#include "ECS.h"
#include "../Vector2D.h"
#include "../Constants.h"

class TransformComponent : public Component {
private:
	Vector2D prevPosition;
public:
	Vector2D position;
	Vector2D velocity;

	int height;
	int width;
	float scale;

	int speed = 200;

	TransformComponent() {
		position.zero();
	}
	

	TransformComponent(float x, float y, int w, int h, float sc = 1.0f) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.zero();
	}

	void update() override {
		prevPosition = position;
		position.x += (velocity.x * speed) / Constant::FPS;
		position.y += (velocity.y * speed) / Constant::FPS;
	}

	void rollBackPosition() {
		position = prevPosition;
	}
};