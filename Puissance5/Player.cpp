#include "Player.h"

// Définition du constructeur de la classe Player
Player::Player(const std::string& name, bool isBot, PlayerColor color)
    : name(name), bot(isBot), color(color) {
    // Les membres sont initialisés avec les valeurs passées en paramètre
    // Vous pouvez ajouter des opérations additionnelles ici si nécessaire
}

// Définition des méthodes d'accès
const std::string& Player::getName() const {
    return name;
}

bool Player::isBot() const {
    return bot;
}

PlayerColor Player::getColor() const {
    return color;
}

void Player::setBot(bool isBot) {
    this->bot = isBot;
}

void Player::setColor(PlayerColor color) {
    this->color = color;
}

