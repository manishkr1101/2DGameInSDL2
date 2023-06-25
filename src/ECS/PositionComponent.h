#pragma once
#include "ECS.h"

class PositionComponent : public Component {
private:
	int xpos;
	int ypos;

public:
	PositionComponent(): xpos(0), ypos(0){}
	PositionComponent(int x, int y) {
		xpos = x;
		ypos = y;
		okay("initialized xpos: %d, ypos: %d", xpos, ypos);
	}
	int x() { return xpos; }
	int y() { return ypos; }

	void init() override {
		
	}

	void update() override {
		xpos++;
		ypos++;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};