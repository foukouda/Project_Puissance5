#include "SDL.h" // Inclut la bibliothèque SDL
#include "Game.h" // Inclut le fichier d'en-tête de la classe Game

    // Ce programme est une démonstration simple d'un jeu de Puissance 5 réalisé avec SDL.
    // Il crée une fenêtre de jeu, gère les événements, met à jour la logique du jeu et effectue le rendu graphique.
    // Le framerate est limité à 60 images par seconde pour assurer une expérience de jeu fluide.

Game* game = nullptr; // Pointeur vers l'objet Game

int main(int argc, char* argv[]) {

    // Constantes pour contrôler le framerate
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    // Création d'une instance de la classe Game
    game = new Game();

    // Initialisation de la fenêtre de jeu
    game->init("PUISSANCE5", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 1400, false);

    // Boucle principale du jeu
    while (game->running()) {
        frameStart = SDL_GetTicks(); // Récupère le temps au début de la boucle

        game->handleEvents(); // Gestion des événements
        game->update(); // Mise à jour de la logique du jeu
        game->render(); // Rendu graphique du jeu

        frameTime = SDL_GetTicks() - frameStart; // Calcule le temps écoulé dans la boucle

        // Si le temps écoulé est inférieur au délai entre les frames, on attend pour maintenir le framerate
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean(); // Nettoyage des ressources

    return 0;
}
