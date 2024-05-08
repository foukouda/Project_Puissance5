// Ce programme est une d�monstration d'un jeu simple utilisant la biblioth�que SDL.
// Il cr�e une fen�tre de jeu, g�re les �v�nements, met � jour la logique du jeu et effectue le rendu graphique.

#pragma once // Directive de pr�processeur pour emp�cher l'inclusion multiple du fichier d'en-t�te

#include "SDL.h" // Inclut la biblioth�que SDL
#include "SDL_image.h" // Inclut la biblioth�que SDL_image
#include "Bouton.h" // Inclut le fichier d'en-t�te de la classe Bouton

class Game {
public:
    Game(); // Constructeur de la classe Game
    ~Game(); // Destructeur de la classe Game

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen); // Initialise le jeu
    void handleEvents(); // G�re les �v�nements du jeu
    void update(); // Met � jour la logique du jeu
    void render(); // Effectue le rendu graphique du jeu
    void clean(); // Nettoie les ressources utilis�es par le jeu

    bool running() { return isRunning; } // Retourne l'�tat d'ex�cution du jeu

private:
    Button* startButton; // Bouton de d�marrage du jeu
    Button* quitButton; // Bouton de sortie du jeu
    Button* musiqueButton; // Bouton pour activer/d�sactiver la musique
    bool isRunning; // Indique si le jeu est en cours d'ex�cution
    SDL_Window* window; // Fen�tre de jeu
    SDL_Renderer* renderer; // Renderer SDL pour le rendu graphique
    Button* button; // Bouton temporaire
};


