#include "SDL.h" // Inclut la biblioth�que SDL
#include "Game.h" // Inclut le fichier d'en-t�te de la classe Game

    // Ce programme est une d�monstration simple d'un jeu de Puissance 5 r�alis� avec SDL.
    // Il cr�e une fen�tre de jeu, g�re les �v�nements, met � jour la logique du jeu et effectue le rendu graphique.
    // Le framerate est limit� � 60 images par seconde pour assurer une exp�rience de jeu fluide.

Game* game = nullptr; // Pointeur vers l'objet Game

int main(int argc, char* argv[]) {

    // Constantes pour contr�ler le framerate
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    // Cr�ation d'une instance de la classe Game
    game = new Game();

    // Initialisation de la fen�tre de jeu
    game->init("PUISSANCE5", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 1400, false);

    // Boucle principale du jeu
    while (game->running()) {
        frameStart = SDL_GetTicks(); // R�cup�re le temps au d�but de la boucle

        game->handleEvents(); // Gestion des �v�nements
        game->update(); // Mise � jour de la logique du jeu
        game->render(); // Rendu graphique du jeu

        frameTime = SDL_GetTicks() - frameStart; // Calcule le temps �coul� dans la boucle

        // Si le temps �coul� est inf�rieur au d�lai entre les frames, on attend pour maintenir le framerate
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean(); // Nettoyage des ressources

    return 0;
}
