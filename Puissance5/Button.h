#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <functional>  // Nécessaire pour std::function

class Button {
public:
    Button(int x, int y, int w, int h, const std::string& notPressedImage, const std::string& pressedImage, SDL_Renderer* renderer);
    ~Button();

    void render(SDL_Renderer* renderer);
    void update(const SDL_Event& e);
    bool isPressed() const { return pressed; }
    void setAction(std::function<void()> action); // Ajoutez cette ligne

private:
    SDL_Texture* notPressedTexture;
    SDL_Texture* pressedTexture;
    SDL_Rect srcRect, destRect;
    bool pressed;
    SDL_Color fallbackColor; // Couleur de repli si le chargement de la texture échoue
    std::function<void()> action;  // Ajoutez cette ligne
};

