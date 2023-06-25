#pragma once
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent : public Component {

public:
	Vector2D position;
	Vector2D velocity;

	int height;
	int width;
	float scale;

	int speed = 3;

	TransformComponent(): position(){}
	

	TransformComponent(float x, float y, int h, int w, float sc = 1.0f) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.x = velocity.y = 0;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};