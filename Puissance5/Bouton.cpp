// Bouton.cpp
#include "Bouton.h"
#include "TextureManager.h"
#include <iostream>

Button::Button(int x, int y, int width, int height, const std::string& imagePath, const std::string& pressedImagePath, SDL_Renderer* renderer) : selected(false) {
    // Charger la texture par défaut du bouton
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        // Gestion de l'erreur si le chargement de l'image échoue
        std::cout << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_Rect srcRect = { 0, 0, surface->w, surface->h };
    SDL_Rect dstRect = { 0, 0, width, height };
    SDL_BlitScaled(surface, &srcRect, scaledSurface, &dstRect);
    texture = SDL_CreateTextureFromSurface(renderer, scaledSurface);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(scaledSurface);

    // Charger la texture alternative pour l'état pressé du bouton
    SDL_Surface* pressedSurface = IMG_Load(pressedImagePath.c_str());
    if (!pressedSurface) {
        // Gestion de l'erreur si le chargement de l'image alternative échoue
        std::cout << "Erreur de chargement de l'image alternative : " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Surface* scaledPressedSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_Rect pressedSrcRect = { 0, 0, pressedSurface->w, pressedSurface->h };
    SDL_Rect pressedDstRect = { 0, 0, width, height };
    SDL_BlitScaled(pressedSurface, &pressedSrcRect, scaledPressedSurface, &pressedDstRect);
    pressedTexture = SDL_CreateTextureFromSurface(renderer, scaledPressedSurface);
    SDL_FreeSurface(pressedSurface);
    SDL_FreeSurface(scaledPressedSurface);

    sRect = { 0 , 0, width, height };
    dRect = { x, y, width, height };
    defaultSrcRect = { 0, 0, width, height }; // Initialiser la zone source par défaut
    destRect = { x, y, width, height }; // Initialiser le rectangle de destination
}


void Button::setXY(int x, int y) {
    dRect.x = x;
    dRect.y = y;
}
void Button::draw(SDL_Renderer* renderer) { 
    SDL_RenderCopy(renderer, texture, &sRect, &dRect);
}
Button::~Button() {
    SDL_DestroyTexture(texture);
}

void Button::setClicked(bool clicked) {
       isClicked = clicked;
    // Changer la texture affichée en fonction de l'état du bouton
    if (isClicked) {
        // Bouton cliqué : utiliser la texture alternative
        texture = pressedTexture;
    }
    else {
        // Bouton non cliqué : utiliser la texture par défaut
        texture = defaultTexture;
    }
}

void Button::render(SDL_Renderer* renderer) {
    // Utiliser la texture appropriée en fonction de l'état du bouton
    SDL_Texture* currentTexture = mouseOver ? pressedTexture : texture;
    SDL_RenderCopy(renderer, currentTexture, &sRect, &dRect);
}


bool Button::checkClicked(int mouseX, int mouseY) const {
    return (mouseX >= dRect.x && mouseX <= dRect.x + dRect.w &&
        mouseY >= dRect.y && mouseY <= dRect.y + dRect.h);
}

void Button::handleMouseEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= dRect.x && mouseX <= dRect.x + dRect.w &&
            mouseY >= dRect.y && mouseY <= dRect.y + dRect.h) {
            // La souris est sur le bouton
            mouseOver = true;
        }
        else {
            // La souris n'est pas sur le bouton
            mouseOver = false;
        }
    }
}


