#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL.h>

SDL_Renderer* ResourceManager::defaultRenderer = nullptr;
std::map<std::string, SDL_Texture*> ResourceManager::textures;

void ResourceManager::init(SDL_Renderer* ren) {
    defaultRenderer = ren;
    if (defaultRenderer == nullptr) {
        std::cout << "Renderer is null after initialization." << std::endl;
    }
    else {
        SDL_SetRenderDrawColor(defaultRenderer, 255, 255, 255, 255);
        std::cout << "Renderer initialized successfully." << std::endl;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else {
        std::cout << "SDL_image initialized successfully." << std::endl;
    }
}


// Déclaration simplifiée de la fonction loadTexture
SDL_Texture* ResourceManager::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (newTexture == nullptr) {
        std::cerr << "Unable to create texture from surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return newTexture;
}



void ResourceManager::cleanUp() {
    for (auto& t : textures) {
        SDL_DestroyTexture(t.second);
    }
    textures.clear();
}



