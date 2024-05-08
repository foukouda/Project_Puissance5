// Bouton.cpp

#include "Bouton.h" // Inclut le fichier d'en-tête de la classe Button
#include "TextureManager.h" // Inclut le gestionnaire de textures
#include <iostream> // Inclut la bibliothèque d'entrées-sorties standard

// Constructeur de la classe Button
Button::Button(int x, int y, int width, int height, const std::string& imagePath, const std::string& pressedImagePath, SDL_Renderer* renderer) : selected(false) {
    // Charge la texture par défaut du bouton
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        // Affiche un message d'erreur si le chargement de l'image échoue
        std::cout << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }

    // Redimensionne la surface de l'image
    SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_Rect srcRect = { 0, 0, surface->w, surface->h };
    SDL_Rect dstRect = { 0, 0, width, height };
    SDL_BlitScaled(surface, &srcRect, scaledSurface, &dstRect);
    // Crée une texture à partir de la surface redimensionnée
    texture = SDL_CreateTextureFromSurface(renderer, scaledSurface);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(scaledSurface);

    // Charge la texture alternative pour l'état pressé du bouton
    SDL_Surface* pressedSurface = IMG_Load(pressedImagePath.c_str());
    if (!pressedSurface) {
        // Affiche un message d'erreur si le chargement de l'image alternative échoue
        std::cout << "Erreur de chargement de l'image alternative : " << IMG_GetError() << std::endl;
        return;
    }

    // Redimensionne la surface de l'image alternative
    SDL_Surface* scaledPressedSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_Rect pressedSrcRect = { 0, 0, pressedSurface->w, pressedSurface->h };
    SDL_Rect pressedDstRect = { 0, 0, width, height };
    SDL_BlitScaled(pressedSurface, &pressedSrcRect, scaledPressedSurface, &pressedDstRect);
    // Crée une texture à partir de la surface redimensionnée
    pressedTexture = SDL_CreateTextureFromSurface(renderer, scaledPressedSurface);
    SDL_FreeSurface(pressedSurface);
    SDL_FreeSurface(scaledPressedSurface);

    // Initialise les rectangles source et destination du bouton
    sRect = { 0 , 0, width, height };
    dRect = { x, y, width, height };
    defaultSrcRect = { 0, 0, width, height }; // Initialise la zone source par défaut
    destRect = { x, y, width, height }; // Initialise le rectangle de destination
}

// Définit la position du bouton
void Button::setXY(int x, int y) {
    dRect.x = x;
    dRect.y = y;
}

// Dessine le bouton sur le renderer
void Button::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, &sRect, &dRect);
}

// Destructeur de la classe Button
Button::~Button() {
    SDL_DestroyTexture(texture); // Détruit la texture du bouton
}

// Définit l'état du bouton (cliqué ou non)
void Button::setClicked(bool clicked) {
    isClicked = clicked;
    // Change la texture affichée en fonction de l'état du bouton
    if (isClicked) {
        // Bouton cliqué : utilise la texture alternative
        texture = pressedTexture;
    }
    else {
        // Bouton non cliqué : utilise la texture par défaut
        texture = defaultTexture;
    }
}

// Effectue le rendu du bouton sur le renderer en utilisant la texture appropriée
void Button::render(SDL_Renderer* renderer) {
    // Utilise la texture appropriée en fonction de l'état du bouton (survolé ou non)
    SDL_Texture* currentTexture = mouseOver ? pressedTexture : texture;
    SDL_RenderCopy(renderer, currentTexture, &sRect, &dRect);
}

// Vérifie si le bouton a été cliqué en fonction des coordonnées de la souris
bool Button::checkClicked(int mouseX, int mouseY) const {
    return (mouseX >= dRect.x && mouseX <= dRect.x + dRect.w &&
        mouseY >= dRect.y && mouseY <= dRect.y + dRect.h);
}

// Gère les événements liés à la souris pour le bouton
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


