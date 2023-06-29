#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "../util/log.h"

#include "Map.h"
#include "ECS/ColliderComponent.h"

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
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	bool isRunning;
	SDL_Window* window;
	
};

#endif