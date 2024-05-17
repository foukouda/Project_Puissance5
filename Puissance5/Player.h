#pragma once

#include <string>

// D�finition de l'�num�ration pour les couleurs des joueurs
enum class PlayerColor {
    RED,
    YELLOW,
    GREEN,
    BLUE
};

// D�claration de la classe Player
class Player {
public:
    // Constructeur avec param�tres pour initialiser un joueur
    Player(const std::string& name, bool isBot, PlayerColor color);

    // M�thodes d'acc�s pour les propri�t�s du joueur
    const std::string& getName() const;
    bool isBot() const;
    PlayerColor getColor() const;
    void setColor(PlayerColor color);

    void setBot(bool isBot);

private:
    std::string name;  // Nom du joueur
    bool bot;          // Indicateur si le joueur est un bot
    PlayerColor color; // Couleur associ�e au joueur
};
