#include "TextureManager.h"
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
    SDL_Surface* tempSurface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (texture == NULL)
        err("Failed to load texture: %s", SDL_GetError());
    SDL_FreeSurface(tempSurface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
