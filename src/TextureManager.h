#pragma once

#include "SDL.h"
#include <map>

class TextureManager {
private:
	static std::map<const char*, SDL_Texture*> loadedTextures;
	TextureManager() = default;
public:
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, const SDL_RendererFlip flip = SDL_FLIP_NONE);
	static void clean();
};
