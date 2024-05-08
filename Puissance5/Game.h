// Ce programme est une démonstration d'un jeu simple utilisant la bibliothèque SDL.
// Il crée une fenêtre de jeu, gère les événements, met à jour la logique du jeu et effectue le rendu graphique.

#pragma once // Directive de préprocesseur pour empêcher l'inclusion multiple du fichier d'en-tête

#include "SDL.h" // Inclut la bibliothèque SDL
#include "SDL_image.h" // Inclut la bibliothèque SDL_image
#include "Bouton.h" // Inclut le fichier d'en-tête de la classe Bouton

class Game {
public:
    Game(); // Constructeur de la classe Game
    ~Game(); // Destructeur de la classe Game

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen); // Initialise le jeu
    void handleEvents(); // Gère les événements du jeu
    void update(); // Met à jour la logique du jeu
    void render(); // Effectue le rendu graphique du jeu
    void clean(); // Nettoie les ressources utilisées par le jeu

    bool running() { return isRunning; } // Retourne l'état d'exécution du jeu

private:
    Button* startButton; // Bouton de démarrage du jeu
    Button* quitButton; // Bouton de sortie du jeu
    Button* musiqueButton; // Bouton pour activer/désactiver la musique
    bool isRunning; // Indique si le jeu est en cours d'exécution
    SDL_Window* window; // Fenêtre de jeu
    SDL_Renderer* renderer; // Renderer SDL pour le rendu graphique
    Button* button; // Bouton temporaire
};


