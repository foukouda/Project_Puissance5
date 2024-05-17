#include "Player.h"

// D�finition du constructeur de la classe Player
Player::Player(const std::string& name, bool isBot, PlayerColor color)
    : name(name), bot(isBot), color(color) {
    // Les membres sont initialis�s avec les valeurs pass�es en param�tre
    // Vous pouvez ajouter des op�rations additionnelles ici si n�cessaire
}

// D�finition des m�thodes d'acc�s
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

