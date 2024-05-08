#include "Game.h" // Inclut le fichier d'en-tête de la classe Game
#include "TextureManager.h" // Inclut le fichier d'en-tête de la classe TextureManager
#include <iostream> // Inclut la bibliothèque iostream
#include "Bouton.h" // Inclut le fichier d'en-tête de la classe Bouton


// Il initialise la fenêtre de jeu, charge les textures, gère les événements, 
// met à jour la logique du jeu et effectue le rendu graphique.

SDL_Texture* background; // Texture de fond
SDL_Texture* logo; // Texture du logo
SDL_Rect srcR, destR; // Rectangles source et destination pour le rendu

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), button(nullptr) {} // Constructeur de la classe Game

Game::~Game() {} // Destructeur de la classe Game

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    }
    else {
        isRunning = false;
    }

    // Chargement des textures depuis les fichiers
    SDL_Surface* tmpSurface = IMG_Load("assets/background.png");
    background = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    SDL_Surface* tmpSurface2 = IMG_Load("assets/LOGO.png");
    logo = SDL_CreateTextureFromSurface(renderer, tmpSurface2);
    SDL_FreeSurface(tmpSurface2);

    // Création des boutons
    startButton = new Button(120, 300, 360, 125, "assets/start/notpress.png", "assets/start/press.png", renderer);
    quitButton = new Button(120, 440, 360, 125, "assets/quit/notpress.png", "assets/quit/press.png", renderer);
    musiqueButton = new Button(1200, 600, 100, 160, "assets/song/notpress.png", "assets/song/press.png", renderer);
}

// Cette fonction gère les événements de l'application, 
// tels que la fermeture de la fenêtre ou les clics de souris sur des boutons du jeu.
void Game::handleEvents() {
    SDL_Event event; // Initialise une structure d'événement SDL

    // Récupère le dernier événement de la file d'attente d'événements SDL
    SDL_PollEvent(&event);

    // Traite différents types d'événements
    switch (event.type) {
        // Si l'utilisateur ferme la fenêtre, arrête l'exécution du jeu
    case SDL_QUIT:
        isRunning = false;
        break;

        // Si l'utilisateur clique avec la souris
    case SDL_MOUSEBUTTONDOWN:
        int mouseX, mouseY;
        // Récupère les coordonnées du curseur de la souris
        SDL_GetMouseState(&mouseX, &mouseY);
        // Vérifie si un bouton du jeu a été cliqué
        if (startButton->checkClicked(mouseX, mouseY)) {
            startButton->setClicked(true);
            // Affiche un message dans la console
            std::cout << "Bouton Start cliqué !" << std::endl;
        }
        else if (quitButton->checkClicked(mouseX, mouseY)) {
            // Si le bouton "Quitter" est cliqué, arrête l'exécution du jeu
            isRunning = false;
            // Affiche un message dans la console
            std::cout << "Bouton Quitter cliqué !" << std::endl;
        }
        else if (musiqueButton->checkClicked(mouseX, mouseY)) {
            musiqueButton->setClicked(true);
            // Affiche un message dans la console
            std::cout << "Bouton soud cliqué !" << std::endl;
        }
        break;

        // Aucune action spécifique pour les autres types d'événements
    default:
        break;
    }
}

// Met à jour les paramètres de rendu du jeu, 
// tels que les dimensions et la position des éléments affichés à l'écran.

void Game::update() {
    // Met à jour les paramètres de rendu
    destR.h = 180;
    destR.w = 650;
    destR.x = 60;
    destR.y = 10;
}

// Effectue le rendu graphique du jeu en utilisant le renderer SDL.

void Game::render() {
    // Efface le rendu précédent
    SDL_RenderClear(renderer);
    // Affiche les textures et les boutons
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, logo, NULL, &destR);
    startButton->draw(renderer);
    quitButton->draw(renderer);
    musiqueButton->draw(renderer);
    // Affiche le rendu
    SDL_RenderPresent(renderer);
}

// Nettoie les ressources utilisées par le jeu à sa fermeture.

void Game::clean() {
    // Nettoie les ressources
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "game cleaned" << std::endl;
}
