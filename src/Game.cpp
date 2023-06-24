#include "Game.h"


GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

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

	player = new GameObject(Constant::PLAYER_SPRITE, 0, 0);
	enemy = new GameObject(Constant::ENEMY_SPRITE, 50, 50);

	map = new Map();
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
	player->Update();
	enemy->Update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	player->Render();
	enemy->Render();
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
