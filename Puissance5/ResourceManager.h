#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class ResourceManager {
public:
    static void init(SDL_Renderer* defaultRenderer);
    static SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    static void cleanUp();

private:
    static SDL_Renderer* defaultRenderer;
    static std::map<std::string, SDL_Texture*> textures;
};