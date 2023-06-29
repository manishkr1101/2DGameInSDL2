#include "Game.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Collision.h"


Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

Manager manager;

auto& wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
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
	SDL_RenderSetScale(renderer, Constant::SCALE, Constant::SCALE);
	okay("enabled scaling factor : %f", Constant::SCALE);
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 1);
	okay("Renderer created");

	isRunning = true;

	map = new Map();
	
	//ecs implementation
	tile0.addComponent<TileComponent>(10, 200, 32, 32, 0);
	tile1.addComponent<TileComponent>(10, 250, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(10, 300, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("grass");

	player.addComponent<TransformComponent>(0.0f, 0.0f, 128, 128, 0.5f);
	player.addComponent<SpriteComponent>(Constant::PLAYER_SPRITE);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 20, 300);
	wall.addComponent<SpriteComponent>(Constant::DIRT_SPRITE);
	wall.addComponent<ColliderComponent>("wall");

}

void Game::handleEvents() {
	
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

	for (const auto colA : Game::colliders) {
		for (const auto colB : Game::colliders) {
			if (colA!=colB && Collision::AABB(*colA, *colB)) {
				colA->entity->getComponent<TransformComponent>().rollBackPosition();
			}
		}
	}

	
}

void Game::render()
{
	SDL_RenderClear(renderer);
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

void Game::addTile(int id, int x, int y) {
	auto& entity(manager.addEntity());
	entity.addComponent<TileComponent>(x, y, 32, 32, id);
}