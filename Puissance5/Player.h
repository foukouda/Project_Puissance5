#pragma once

#include <string>

// Définition de l'énumération pour les couleurs des joueurs
enum class PlayerColor {
    RED,
    YELLOW,
    GREEN,
    BLUE
};

// Déclaration de la classe Player
class Player {
public:
    // Constructeur avec paramètres pour initialiser un joueur
    Player(const std::string& name, bool isBot, PlayerColor color);

    // Méthodes d'accès pour les propriétés du joueur
    const std::string& getName() const;
    bool isBot() const;
    PlayerColor getColor() const;
    void setColor(PlayerColor color);

    void setBot(bool isBot);

private:
    std::string name;  // Nom du joueur
    bool bot;          // Indicateur si le joueur est un bot
    PlayerColor color; // Couleur associée au joueur
};
