#include "TextureManager.h"
#include "Game.h"

std::map<const char*, SDL_Texture*> TextureManager::loadedTextures;

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
    if (loadedTextures.find(filename) != loadedTextures.end())
        return loadedTextures[filename];

    SDL_Surface* tempSurface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (texture == NULL)
        err("Failed to load texture: %s", SDL_GetError());
    SDL_FreeSurface(tempSurface);
    loadedTextures.emplace(filename, texture);
    return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, const SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}

void TextureManager::clean() {
    for (auto key_value : loadedTextures) {
        SDL_DestroyTexture(key_value.second);
    }
    loadedTextures.erase(loadedTextures.begin(), loadedTextures.end());
}