#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <functional>


class Button {
public:
    Button(int x, int y, int w, int h, const std::string& notPressedImage, const std::string& pressedImage, SDL_Renderer* renderer);
    ~Button();

    void render(SDL_Renderer* renderer);
    void update(const SDL_Event& e);
    bool isPressed() const { return pressed; }
    void setAction(std::function<void()> action);
    void setToggleMode(bool toggle); // Activation du mode bascule

private:
    SDL_Texture* notPressedTexture;
    SDL_Texture* pressedTexture;
    SDL_Rect srcRect, destRect;
    bool pressed;
    bool toggleMode; // Indique si le bouton est en mode bascule
    bool toggled;    // État actuel du bouton dans le mode bascule
    SDL_Color fallbackColor;
    std::function<void()> action;
    int MARGIN_X = 0;
    int MARGIN_Y = 0;
};
