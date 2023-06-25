#include "Game.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

Game::Game(): isRunning(false), window(NULL)
{
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	Uint32 flags = SDL_WINDOW_SHOWN;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		err("Couldn't initialize SDL, error: %s", SDL_GetError());
		return;
	}
	okay("Subsystem initialized");

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window == NULL) {
		err("Couldn't initialize window, error: %s", SDL_GetError());
		return;
	}
	okay("Window created: %dx%d", width, height);

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) return;
	SDL_RenderSetScale(renderer, 1.5, 1.5);
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 1);
	okay("Renderer created");

	isRunning = true;

	map = new Map();
	
	//ecs implementation
	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>(Constant::PLAYER_SPRITE);
	
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	if (player.getComponent<TransformComponent>().position.x > 100) {
		player.getComponent<SpriteComponent>().setTex(Constant::ENEMY_SPRITE);
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	okay("Game cleaned");
}

bool Game::running()
{
	return isRunning;
}
