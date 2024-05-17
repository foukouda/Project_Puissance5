#include "Button.h"
#include "ResourceManager.h"

Button::Button(int x, int y, int w, int h, const std::string& notPressedImage, const std::string& pressedImage, SDL_Renderer* renderer)
    : srcRect{ 0, 0, w, h }, pressed(false), toggleMode(false), toggled(false) {
    // Ajuster les coordonnées pour les marges visuelles
    int adjustedX = x + MARGIN_X; // MARGIN_X à définir selon le besoin
    int adjustedY = y + MARGIN_Y; // MARGIN_Y à définir selon le besoin

    destRect = { adjustedX, adjustedY, w, h };
    notPressedTexture = ResourceManager::loadTexture(notPressedImage, renderer);
    pressedTexture = ResourceManager::loadTexture(pressedImage, renderer);
}

void Button::setToggleMode(bool toggle) {
    toggleMode = toggle;
    toggled = false; // Réinitialiser lors du changement de mode
}

void Button::update(const SDL_Event& e) {
    // Obtenir l'état actuel de la souris
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Vérifier si le clic de souris est à l'intérieur des limites du bouton
    bool isInside = mouseX >= destRect.x && mouseX <= (destRect.x + destRect.w) &&
        mouseY >= destRect.y && mouseY <= (destRect.y + destRect.h);

    if (e.type == SDL_MOUSEBUTTONDOWN && isInside) {
        if (toggleMode) {
            // Mode bascule : toggler l'état lors du clic
            toggled = !toggled; // Inverser l'état de toggled
            pressed = toggled;  // Synchroniser l'état pressed avec toggled
        }
        else {
            // Mode normal : simplement marquer comme pressé
            pressed = true;
        }

        // Exécuter l'action associée au bouton, si elle existe
        if (action) action();
    }
    else if (e.type == SDL_MOUSEBUTTONUP) {
        if (!toggleMode) {
            // En mode non-bascule, relâcher le bouton lors du relâchement de la souris
            pressed = false;
        }
        // En mode bascule, l'état reste inchangé jusqu'au prochain clic
    }
}


void Button::render(SDL_Renderer* renderer) {
    SDL_Texture* currentTexture = pressed ? pressedTexture : notPressedTexture;

    if (currentTexture) {
        // Si la texture est disponible, l'utiliser pour le rendu
        SDL_RenderCopy(renderer, currentTexture, nullptr, &destRect);
    }
    else {
        // S'il n'y a pas de texture disponible, utiliser une couleur de repli
        // La couleur de repli est définie lors de l'initialisation du bouton en cas d'erreur de chargement de texture
        SDL_SetRenderDrawColor(renderer, fallbackColor.r, fallbackColor.g, fallbackColor.b, fallbackColor.a);
        SDL_RenderFillRect(renderer, &destRect);

        // Optionnel: dessiner un contour pour mieux visualiser le bouton sans texture
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir pour le contour
        SDL_RenderDrawRect(renderer, &destRect);
    }
}


Button::~Button() {
    if (notPressedTexture) {
        SDL_DestroyTexture(notPressedTexture);
    }
    if (pressedTexture) {
        SDL_DestroyTexture(pressedTexture);
    }
}

void Button::setAction(std::function<void()> newAction) {
    action = newAction;
}

