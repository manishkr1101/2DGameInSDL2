#pragma once
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent : public Component {

public:
	Vector2D position;

	TransformComponent(): position(){}
	TransformComponent(int x, int y) {
		position.x = x;
		position.y = y;
	}
	

	void init() override {
		
	}

	void update() override {
		position = position + UNIT_VECTOR;
	}

	void setPos(int x, int y) {
		
	}
};