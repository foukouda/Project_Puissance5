#pragma once

#include <memory>  // Inclusion nécessaire pour std::unique_ptr
#include "SDL.h"
#include "ResourceManager.h"
#include "Button.h"

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void processEvents();
    void update();
    void render();
    void cleanup();
    void clearScreen();

    bool isRunning() const;

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unique_ptr<Button> startButton;  // Utilisation de std::unique_ptr pour la gestion automatique de la mémoire
    std::unique_ptr<Button> quitButton;
    std::unique_ptr<Button> musicButton;
    SDL_Texture* backgroundTexture;
};
