#pragma once
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
private:
	Vector2D prevPosition;
public:
	Vector2D position;
	Vector2D velocity;

	int height;
	int width;
	float scale;

	int speed = 3;

	TransformComponent() {
		position.zero();
	}
	

	TransformComponent(float x, float y, int h, int w, float sc = 1.0f) {
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
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	void rollBackPosition() {
		position = prevPosition;
	}
};