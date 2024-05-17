
README pour le Projet de Jeu

Vue d'ensemble
Ce projet est un jeu développé en utilisant SDL2, qui propose un jeu de plateau avec diverses fonctionnalités, incluant la configuration des joueurs, la mise en place de l'interface utilisateur, la logique du jeu, et un adversaire IA. Le jeu permet aux joueurs d'interagir via une interface graphique, de configurer leurs paramètres et de jouer les uns contre les autres ou contre une IA.

Structure des Fichiers
- Game.h / Game.cpp : Logique principale du jeu, fonctions d'initialisation et de rendu.
- Player.h / Player.cpp : Attributs et méthodes des joueurs.
- Button.h / Button.cpp : Classe Button pour l'interaction de l'interface utilisateur.
- ResourceManager.h / ResourceManager.cpp : Gestion des ressources pour les textures et autres actifs.

Installation et Configuration
Prérequis
- Bibliothèque SDL2
- Compilateur C++

Étapes
1. Installer SDL2 :
   sudo apt-get install libsdl2-dev
2. Cloner le dépôt :
   git clone <url_du_dépôt>
3. Compiler le projet :
   cd <répertoire_du_projet>
   make

Utilisation
Lancer le Jeu
Exécutez le binaire :
./game

Contrôles du Jeu
- Bouton Démarrer : Lance le jeu.
- Bouton Quitter : Quitte le jeu.
- Bouton Musique : Active ou désactive la musique de fond.
- Boutons de Configuration des Joueurs : Configure les joueurs comme humain ou bot, et choisit les couleurs.
- Boutons de Taille du Plateau : Sélectionne la taille du plateau de 7x7 à 10x10.
- Bouton Redémarrer : Redémarre le jeu.

Explication du Code
Initialisation
- Constructeur de Game : Initialise SDL, configure le plateau de jeu, et configure l'état initial du jeu.
- Destructeur de Game : Nettoie les ressources.

Configuration de l'Interface Utilisateur (Game::initUI)
- Initialise divers boutons pour différentes fonctionnalités (démarrer, quitter, configuration des joueurs, etc.).
- Assigne des actions aux boutons pour gérer les changements d'état et les configurations.

Boucle de Jeu
- processEvents() : Gère les événements SDL tels que les clics de souris et les événements de fermeture.
- update() : Contient la logique du jeu pour mettre à jour l'état du jeu.
- render() : Rend le plateau de jeu et les éléments de l'interface utilisateur en fonction de l'état actuel.

Logique du Jeu
- setupGame() : Initialise ou réinitialise le plateau de jeu.
- makeMove() : Exécute un coup pour le joueur actuel.
- hasWon() : Vérifie si un joueur a gagné le jeu.
- isBoardFull() : Vérifie si le plateau est plein.
- findBestMove() : Fonction IA pour déterminer le meilleur coup en utilisant l'algorithme minimax.

Rendu
- calculateCellSize() : Calcule la taille de chaque cellule en fonction de la taille du plateau et des dimensions de l'écran.
- drawCircle() : Dessine un cercle aux coordonnées spécifiées.

Dépendances
- SDL2
- Bibliothèques standard C++

Contact
Pour toute question ou problème, veuillez contacter [votre_email@example.com].
