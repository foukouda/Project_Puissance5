#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Button.h"
#include "ResourceManager.h"
#include "Player.h"

enum GameState {
    MENU,
    PLAYER_CONFIG,
    GAME_RUNNING
};

struct Move {
    int row, col;
};

class Game {
public:
    Game();
    ~Game();

    void setBoardSize(int size);
    static const int BOARD_SIZE_MIN = 7;
    static const int BOARD_SIZE_MAX = 10;
    static const int WIN_LENGTH = 5;
    char currentPlayer;
    bool gameWon;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void processEvents();
    void update();
    void render();
    void cleanup();
    void clearScreen();
    void initUI();
    void changeState(GameState newState);
    bool isRunning() const;
    void setupGame();
    void setupBoard();
    bool isValidMove(const std::vector<std::vector<char>>& board, int col) const;
    void makeMove(std::vector<std::vector<char>>& board, int col, char player);
    bool hasWon(const std::vector<std::vector<char>>& board, char player) const;
    void performBotMove();
    void handleHumanPlayerMove(const SDL_Event& event);
    void checkGameStateAfterMove();
    bool isBot(char currentPlayer) const;
    void updatePlayerConfiguration();
    void updateRenderForCell(int row, int col);
    bool isBoardFull(const std::vector<std::vector<char>>& board) const;
    Move findBestMove(std::vector<std::vector<char>>& board);
    int minimax(std::vector<std::vector<char>>& board, int depth, int alpha, int beta, bool isMaximizingPlayer);
    int scorePosition(const std::vector<std::vector<char>>& board, char piece);
    int evaluateWindow(const std::vector<char>& window, char piece);
    int getNextOpenRow(const std::vector<std::vector<char>>& board, int col) const;
    bool isMovesLeft(const std::vector < std::vector<char>>& board) const;

    std::unique_ptr<Button> size7Button;
    std::unique_ptr<Button> size8Button;
    std::unique_ptr<Button> size9Button;
    std::unique_ptr<Button> size10Button;

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> quitButton;
    std::unique_ptr<Button> quitButton2;
    std::unique_ptr<Button> musicButton;
    std::unique_ptr<Button> player1HumanButton;
    std::unique_ptr<Button> player1BotButton;
    std::unique_ptr<Button> player2HumanButton;
    std::unique_ptr<Button> player2BotButton;
    std::unique_ptr<Button> doneButton;
    std::unique_ptr<Button> restartGameButton;

    SDL_Texture* backgroundTexture;
    SDL_Texture* backgroundTexture2;
    SDL_Texture* backgroundTexture3;
    GameState currentState;
    std::string playerName;
    int boardSize;
    std::vector<std::vector<char>> board;

    Player player1;
    Player player2;
    std::unique_ptr<Button> player1YellowButton;
    std::unique_ptr<Button> player1RedButton;
    std::unique_ptr<Button> player1GreenButton;
    std::unique_ptr<Button> player1BlueButton;

    std::unique_ptr<Button> player2YellowButton;
    std::unique_ptr<Button> player2RedButton;
    std::unique_ptr<Button> player2GreenButton;
    std::unique_ptr<Button> player2BlueButton;
};
