#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "../util/log.h"
#include "Constants.h"
#include "Map.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen=false);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Renderer* renderer;

private:
	bool isRunning;
	SDL_Window* window;
	
};

