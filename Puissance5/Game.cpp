#include "Game.h"
#include <iostream>

Game::Game() : running(false), window(nullptr), renderer(nullptr) {}

Game::~Game() {
    cleanup();
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    SDL_Init(SDL_INIT_EVERYTHING);  
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    running = true;

    ResourceManager::init(renderer);

    backgroundTexture = ResourceManager::loadTexture("assets/background.png", renderer);
    if (!backgroundTexture) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }

    startButton = std::make_unique<Button>(120, 300, 360, 125, "assets/start/notpress.png", "assets/start/press.png", renderer);
    quitButton = std::make_unique<Button>(120, 440, 360, 125, "assets/quit/notpress.png",  "assets/quit/press.png", renderer);
    musicButton = std::make_unique<Button>(1200, 600, 100, 160, "assets/song/notpress.png",  "assets/song/press.png", renderer);
   
    startButton->setAction([this]() {
        std::cout << "Start Button Pressed" << std::endl;
        this->clearScreen();
        });
    quitButton->setAction([this]() {
        std::cout << "Quit Button Pressed" << std::endl;
        running = false;  // Met fin à la boucle principale du jeu
        });
    musicButton->setAction([this]() {
        std::cout << "Music Button Pressed" << std::endl;
        // Code pour 'couper le son' ici
        });

}

void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        // Appelez update pour chaque bouton ici
        startButton->update(event);
        quitButton->update(event);
        musicButton->update(event);
    }
}


void Game::update() {
    // Update game logic here
}

void Game::render() {
    SDL_RenderClear(renderer);  // Nettoie l'écran

    SDL_Rect screenRect = { 0, 0, 1400, 800 };
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &screenRect);

    startButton->render(renderer);
    quitButton->render(renderer);
    musicButton->render(renderer);

    SDL_RenderPresent(renderer);  // Met à jour l'écran
}



void Game::cleanup() {

    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = NULL;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::isRunning() const {
    return running;
}

void Game::clearScreen() {
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
    SDL_RenderClear(renderer);  
    SDL_RenderPresent(renderer);  
    std::cout << "Screen cleared to white" << std::endl;
}