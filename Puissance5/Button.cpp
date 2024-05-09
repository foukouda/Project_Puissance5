#include "Button.h"
#include "ResourceManager.h"

Button::Button(int x, int y, int w, int h, const std::string& notPressedImage, const std::string& pressedImage, SDL_Renderer* renderer)
    : srcRect{ 0, 0, w, h }, destRect{ x, y, w, h }, pressed(false) {
    notPressedTexture = ResourceManager::loadTexture(notPressedImage, renderer);  // Utilisation correcte
    pressedTexture = ResourceManager::loadTexture(pressedImage, renderer);

    // Génération de couleur aléatoire
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    fallbackColor = { Uint8(std::rand() % 256), Uint8(std::rand() % 256), Uint8(std::rand() % 256), 255 };

    if (!notPressedTexture || !pressedTexture) {
        std::cerr << "Error loading button textures. Using fallback color." << std::endl;
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

void Button::render(SDL_Renderer* renderer) {
    SDL_Texture* currentTexture = pressed ? pressedTexture : notPressedTexture;
    if (currentTexture) {
        SDL_RenderCopy(renderer, currentTexture, nullptr, &destRect);
    }
    else {
        // Utiliser la couleur de repli si la texture n'est pas disponible
        SDL_SetRenderDrawColor(renderer, fallbackColor.r, fallbackColor.g, fallbackColor.b, fallbackColor.a);
        SDL_RenderFillRect(renderer, &destRect);
    }
}

void Button::setAction(std::function<void()> action) {
    this->action = action;
}

void Button::update(const SDL_Event& e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (e.type == SDL_MOUSEBUTTONDOWN && mouseX >= destRect.x && mouseX <= (destRect.x + destRect.w) &&
        mouseY >= destRect.y && mouseY <= (destRect.y + destRect.h)) {
        pressed = true;  // Le bouton est pressé
        if (action) {  // Exécutez l'action si elle est définie
            std::cout << "Button action triggered" << std::endl;
            action();
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP) {
        pressed = false;
    }
}
