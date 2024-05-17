#include "Game.h"
#include <iostream>
#include <random>
#include <limits>

const int INF = std::numeric_limits<int>::max();
const char player = 'X';
const char opponent = 'O';
const int MAX_DEPTH = 4;

Game::Game() : boardSize(BOARD_SIZE_MIN), running(false), window(nullptr), renderer(nullptr), currentState(MENU), player1("NomJoueur1", false, PlayerColor::RED), player2("NomJoueur2", true, PlayerColor::YELLOW) {
    SDL_Init(SDL_INIT_EVERYTHING);
    board.resize(boardSize, std::vector<char>(boardSize, '-'));
}

Game::~Game() {
    cleanup();
}

int calculateCellSize(int boardSize, int screenWidth, int screenHeight) {
    int maxBoardWidth = screenWidth - 200;
    int maxBoardHeight = screenHeight - 200;
    int maxSizeByWidth = maxBoardWidth / boardSize;
    int maxSizeByHeight = maxBoardHeight / boardSize;
    return std::min(maxSizeByWidth, maxSizeByHeight);
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

std::vector<std::vector<char>> Game::copyBoard(const std::vector<std::vector<char>>& board) {
    return board; // Copie simple de la grille
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    running = true;

    backgroundTexture = ResourceManager::loadTexture("assets/background.png", renderer);
    if (!backgroundTexture) {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    backgroundTexture2 = ResourceManager::loadTexture("assets/background2.jpg", renderer);
    if (!backgroundTexture2) {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    backgroundTexture3 = ResourceManager::loadTexture("assets/background3.jpg", renderer);
    if (!backgroundTexture3) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    ResourceManager::init(renderer);
    initUI();
}

void Game::initUI() {
    startButton = std::make_unique<Button>(120, 300, 360, 125, "assets/start/notpress.png", "assets/start/press.png", renderer);
    startButton->setAction([this]() {
        std::cout << "Start Button Pressed" << std::endl;
        changeState(PLAYER_CONFIG);
        });

    quitButton = std::make_unique<Button>(120, 440, 360, 125, "assets/quit/notpress.png", "assets/quit/press.png", renderer);
    quitButton->setAction([this]() {
        std::cout << "Quit Button Pressed" << std::endl;
        running = false;
        });

    quitButton2 = std::make_unique<Button>(900, 600, 320, 110, "assets/quit/notpress.png", "assets/quit/press.png", renderer);
    quitButton2->setAction([this]() {
        std::cout << "Quit Button Pressed" << std::endl;
        running = false;
        });

    musicButton = std::make_unique<Button>(1200, 600, 100, 160, "assets/song/notpress.png", "assets/song/press.png", renderer);
    musicButton->setToggleMode(true);
    musicButton->setAction([this]() {
        std::cout << "Music Button Pressed - Toggled state: " << musicButton->isPressed() << std::endl;
        });

    player1HumanButton = std::make_unique<Button>(50, 150, 230, 230, "assets/player/rouge.jpeg", "assets/player/black.jpeg", renderer);
    player1HumanButton->setToggleMode(true);
    player1HumanButton->setAction([this]() {
        std::cout << "Player 1 set as Human" << std::endl;
        });

    player1BotButton = std::make_unique<Button>(300, 150, 230, 230, "assets/bot/rouge.jpeg", "assets/bot/black.jpeg", renderer);
    player1BotButton->setToggleMode(true);
    player1BotButton->setAction([this]() {
        std::cout << "Player 2 set as Bot" << std::endl;
        });

    player2HumanButton = std::make_unique<Button>(1125, 150, 230, 230, "assets/player/jaune.jpeg", "assets/player/blackR.jpeg", renderer);
    player2HumanButton->setToggleMode(true);
    player2HumanButton->setAction([this]() {
        std::cout << "Player 2 set as Human" << std::endl;
        });

    player2BotButton = std::make_unique<Button>(875, 150, 230, 230, "assets/bot/jaune.jpeg", "assets/bot/blackR.jpeg", renderer);
    player2BotButton->setToggleMode(true);
    player2BotButton->setAction([this]() {
        std::cout << "Player 2 set as Bot" << std::endl;
        });

    doneButton = std::make_unique<Button>(550, 650, 300, 100, "assets/start/notpress.png", "assets/start/press.png", renderer);
    doneButton->setAction([this]() {
        std::cout << "Player configuration done" << std::endl;
        changeState(GAME_RUNNING);
        });

    size7Button = std::make_unique<Button>(530, 580, 50, 50, "assets/7.JPG", "assets/7.JPG", renderer);
    size7Button->setAction([this]() {
        setBoardSize(7);
        std::cout << "board size set 7" << std::endl;
        });

    size8Button = std::make_unique<Button>(630, 580, 50, 50, "assets/8.JPG", "assets/8.JPG", renderer);
    size8Button->setAction([this]() {
        setBoardSize(8);
        std::cout << "board size set 8" << std::endl;
        });

    size9Button = std::make_unique<Button>(730, 580, 50, 50, "assets/9.JPG", "assets/9.JPG", renderer);
    size9Button->setAction([this]() {
        setBoardSize(9);
        std::cout << "board size set 9" << std::endl;
        });

    size10Button = std::make_unique<Button>(830, 580, 50, 50, "assets/10.JPG", "assets/10.JPG", renderer);
    size10Button->setAction([this]() {
        setBoardSize(10);
        std::cout << "board size set 10" << std::endl;
        });

    restartGameButton = std::make_unique<Button>(900, 470, 320, 110, "assets/restart_game/notpress.png", "assets/restart_game/press.png", renderer);
    restartGameButton->setAction([this]() {
        std::cout << "Restart Game Button Pressed" << std::endl;
        setupGame();
        });

    player1YellowButton = std::make_unique<Button>(140, 440, 50, 50, "assets/jaune-j.JPEG", "assets/jaune-j.JPEG", renderer);
    player1YellowButton->setAction([this]() {
        if (player2.getColor() != PlayerColor::YELLOW) {
            player1.setColor(PlayerColor::YELLOW);
            std::cout << "Player 1 color set to Yellow" << std::endl;
        }
        });

    player1RedButton = std::make_unique<Button>(210, 440, 50, 50, "assets/rouge-j.JPEG", "assets/rouge-j.JPEG", renderer);
    player1RedButton->setAction([this]() {
        if (player2.getColor() != PlayerColor::RED) {
            player1.setColor(PlayerColor::RED);
            std::cout << "Player 1 color set to Red" << std::endl;
        }
        });

    player1GreenButton = std::make_unique<Button>(280, 440, 50, 50, "assets/vert-j.JPG", "assets/vert-j.JPG", renderer);
    player1GreenButton->setAction([this]() {
        if (player2.getColor() != PlayerColor::GREEN) {
            player1.setColor(PlayerColor::GREEN);
            std::cout << "Player 1 color set to Green" << std::endl;
        }
        });

    player1BlueButton = std::make_unique<Button>(350, 440, 50, 50, "assets/bleu-j.JPG", "assets/bleu-j.JPG", renderer);
    player1BlueButton->setAction([this]() {
        if (player2.getColor() != PlayerColor::BLUE) {
            player1.setColor(PlayerColor::BLUE);
            std::cout << "Player 1 color set to Blue" << std::endl;
        }
        });

    player2YellowButton = std::make_unique<Button>(970, 440, 50, 50, "assets/jaune-j.JPEG", "assets/jaune-j.JPEG", renderer);
    player2YellowButton->setAction([this]() {
        if (player1.getColor() != PlayerColor::YELLOW) {
            player2.setColor(PlayerColor::YELLOW);
            std::cout << "Player 2 color set to Yellow" << std::endl;
        }
        });

    player2RedButton = std::make_unique<Button>(1040, 440, 50, 50, "assets/rouge-j.JPEG", "assets/rouge-j.JPEG", renderer);
    player2RedButton->setAction([this]() {
        if (player1.getColor() != PlayerColor::RED) {
            player2.setColor(PlayerColor::RED);
            std::cout << "Player 2 color set to Red" << std::endl;
        }
        });

    player2GreenButton = std::make_unique<Button>(1110, 440, 50, 50, "assets/vert-j.JPG", "assets/vert-j.JPG", renderer);
    player2GreenButton->setAction([this]() {
        if (player1.getColor() != PlayerColor::GREEN) {
            player2.setColor(PlayerColor::GREEN);
            std::cout << "Player 2 color set to Green" << std::endl;
        }
        });

    player2BlueButton = std::make_unique<Button>(1180, 440, 50, 50, "assets/bleu-j.JPG", "assets/bleu-j.JPG", renderer);
    player2BlueButton->setAction([this]() {
        if (player1.getColor() != PlayerColor::BLUE) {
            player2.setColor(PlayerColor::BLUE);
            std::cout << "Player 2 color set to Blue" << std::endl;
        }
        });
}

void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            if (currentState == MENU) {
                startButton->update(event);
                quitButton->update(event);
                musicButton->update(event);
            }
            else if (currentState == PLAYER_CONFIG) {
                player1BotButton->update(event);
                player1HumanButton->update(event);
                player2HumanButton->update(event);
                player2BotButton->update(event);
                musicButton->update(event);
                doneButton->update(event);
                size7Button->update(event);
                size8Button->update(event);
                size9Button->update(event);
                size10Button->update(event);
                player1YellowButton->update(event);
                player1RedButton->update(event);
                player1GreenButton->update(event);
                player1BlueButton->update(event);
                player2YellowButton->update(event);
                player2RedButton->update(event);
                player2GreenButton->update(event);
                player2BlueButton->update(event);
                updatePlayerConfiguration();
            }
            else if (currentState == GAME_RUNNING && !gameWon) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (isBot(currentPlayer)) {
                        performBotMove();
                    }
                    else {
                        handleHumanPlayerMove(event);
                    }
                }
                quitButton2->update(event);
                restartGameButton->update(event);
            }
        }
    }
}

void Game::update() {
    // Game logic update
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    switch (currentState) {
    case MENU:
        if (backgroundTexture) {
            SDL_Rect menuBackgroundRect = { 0, 0, 1400, 800 };
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &menuBackgroundRect);
        }
        startButton->render(renderer);
        quitButton->render(renderer);
        musicButton->render(renderer);
        break;

    case PLAYER_CONFIG:
        if (backgroundTexture2) {
            SDL_Rect configBackgroundRect = { 0, 0, 1400, 800 };
            SDL_RenderCopy(renderer, backgroundTexture2, NULL, &configBackgroundRect);
        }
        player1HumanButton->render(renderer);
        player1BotButton->render(renderer);
        player2HumanButton->render(renderer);
        player2BotButton->render(renderer);
        doneButton->render(renderer);
        musicButton->render(renderer);
        size7Button->render(renderer);
        size8Button->render(renderer);
        size9Button->render(renderer);
        size10Button->render(renderer);
        player1YellowButton->render(renderer);
        player1RedButton->render(renderer);
        player1GreenButton->render(renderer);
        player1BlueButton->render(renderer);
        player2YellowButton->render(renderer);
        player2RedButton->render(renderer);
        player2GreenButton->render(renderer);
        player2BlueButton->render(renderer);
        break;

    case GAME_RUNNING:
        if (backgroundTexture3) {
            SDL_Rect gameBackgroundRect = { 0, 0, 1400, 800 };
            SDL_RenderCopy(renderer, backgroundTexture3, NULL, &gameBackgroundRect);
        }
        quitButton2->render(renderer);
        restartGameButton->render(renderer);
        int cellSize = calculateCellSize(boardSize, 1400, 800);
        int cellRadius = cellSize / 2 - 5;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                int centerX = 100 + j * cellSize + cellRadius;
                int centerY = 100 + i * cellSize + cellRadius;
                switch (board[i][j]) {
                case 'X':
                    switch (player1.getColor()) {
                    case PlayerColor::RED:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        break;
                    case PlayerColor::YELLOW:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                        break;
                    case PlayerColor::GREEN:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        break;
                    case PlayerColor::BLUE:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        break;
                    }
                    break;
                case 'O':
                    switch (player2.getColor()) {
                    case PlayerColor::RED:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        break;
                    case PlayerColor::YELLOW:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                        break;
                    case PlayerColor::GREEN:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        break;
                    case PlayerColor::BLUE:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        break;
                    }
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    break;
                }
                drawCircle(renderer, centerX, centerY, cellRadius);
            }
        }
        break;
    }

    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void Game::changeState(GameState newState) {
    currentState = newState;
    clearScreen();
    if (newState == GAME_RUNNING) {
        setupBoard();
    }
    currentState = newState;
}

bool Game::isRunning() const {
    return running;
}

void Game::setupGame() {
    board = std::vector<std::vector<char>>(boardSize, std::vector<char>(boardSize, '-'));
    currentPlayer = 'X';
    gameWon = false;
    changeState(GAME_RUNNING);
}

bool Game::isValidMove(const std::vector<std::vector<char>>& board, int col) const {
    return col >= 0 && col < boardSize && board[0][col] == '-';
}

void Game::makeMove(std::vector<std::vector<char>>& board, int col, char player) {
    for (int i = boardSize - 1; i >= 0; i--) {
        if (board[i][col] == '-') {
            board[i][col] = player;
            if (&board == &(this->board)) {
                updateRenderForCell(i, col); // Mettre à jour le rendu uniquement si la grille principale est modifiée
            }
            return;
        }
    }
}

bool Game::hasWon(const std::vector<std::vector<char>>& board, char player) const {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col <= boardSize - WIN_LENGTH; ++col) {
            bool horizontalWin = true;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[row][col + k] != player) {
                    horizontalWin = false;
                    break;
                }
            }
            if (horizontalWin) return true;
        }
    }

    for (int col = 0; col < boardSize; ++col) {
        for (int row = 0; row <= boardSize - WIN_LENGTH; ++row) {
            bool verticalWin = true;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[row + k][col] != player) {
                    verticalWin = false;
                    break;
                }
            }
            if (verticalWin) return true;
        }
    }

    for (int row = 0; row <= boardSize - WIN_LENGTH; ++row) {
        for (int col = 0; col <= boardSize - WIN_LENGTH; ++col) {
            bool diagonalWin1 = true;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[row + k][col + k] != player) {
                    diagonalWin1 = false;
                    break;
                }
            }
            if (diagonalWin1) return true;
        }
    }

    for (int row = WIN_LENGTH - 1; row < boardSize; ++row) {
        for (int col = 0; col <= boardSize - WIN_LENGTH; ++col) {
            bool diagonalWin2 = true;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[row - k][col + k] != player) {
                    diagonalWin2 = false;
                    break;
                }
            }
            if (diagonalWin2) return true;
        }
    }

    return false;
}

void Game::setupBoard() {
    board.resize(boardSize);
    currentPlayer = 'X';
    for (auto& row : board) {
        row.resize(boardSize, '-');
    }
}

void Game::performBotMove() {
    if (!isBot(currentPlayer)) return;

    std::cout << "Bot is thinking..." << std::endl; // Journalisation pour le débogage
    std::vector<std::vector<char>> boardCopy = copyBoard(board); // Créer une copie de la grille
    Move bestMove = findBestMove(boardCopy); // Utiliser la copie pour trouver le meilleur coup
    std::cout << "Best move found: (" << bestMove.row << ", " << bestMove.col << ")" << std::endl; // Journalisation pour le débogage

    if (bestMove.row != -1 && bestMove.col != -1) {
        makeMove(board, bestMove.col, currentPlayer); // Appliquer le meilleur coup sur la grille principale
        if (hasWon(board, currentPlayer)) {
            gameWon = true;
            std::cout << "Bot Player " << currentPlayer << " wins!" << std::endl;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void Game::handleHumanPlayerMove(const SDL_Event& event) {
    int col = (event.button.x - 100) / calculateCellSize(boardSize, 1400, 800);
    if (col >= 0 && col < boardSize && isValidMove(board, col)) {
        makeMove(board, col, currentPlayer);
        checkGameStateAfterMove();
    }
}

void Game::checkGameStateAfterMove() {
    if (hasWon(board, currentPlayer)) {
        gameWon = true;
        std::cout << "Player " << currentPlayer << " wins!" << std::endl;
    }
    else if (isBoardFull(board)) {
        gameWon = true;
        std::cout << "The game is a draw!" << std::endl;
    }
    else {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

bool Game::isBot(char currentPlayer) const {
    if (currentPlayer == 'X') {
        return player1.isBot();
    }
    else {
        return player2.isBot();
    }
}

void Game::updatePlayerConfiguration() {
    if (player1HumanButton->isPressed()) {
        player1.setBot(false);
        player1BotButton->setToggleMode(false);
        player1HumanButton->setToggleMode(true);
    }
    else if (player1BotButton->isPressed()) {
        player1.setBot(true);
        player1HumanButton->setToggleMode(false);
        player1BotButton->setToggleMode(true);
    }
    else {
        player1HumanButton->setToggleMode(true);
        player1BotButton->setToggleMode(true);
    }

    if (player2HumanButton->isPressed()) {
        player2.setBot(false);
        player2BotButton->setToggleMode(false);
        player2HumanButton->setToggleMode(true);
    }
    else if (player2BotButton->isPressed()) {
        player2.setBot(true);
        player2HumanButton->setToggleMode(false);
        player2BotButton->setToggleMode(true);
    }
    else {
        player2HumanButton->setToggleMode(true);
        player2BotButton->setToggleMode(true);
    }
}

void Game::setBoardSize(int size) {
    if (size >= BOARD_SIZE_MIN && size <= BOARD_SIZE_MAX) {
        boardSize = size;
        board.resize(boardSize, std::vector<char>(boardSize, '-'));
    }
}

void Game::updateRenderForCell(int row, int col) {
    int cellSize = calculateCellSize(boardSize, 1400, 800);
    int cellRadius = cellSize / 2 - 5;
    int centerX = 100 + col * cellSize + cellRadius;
    int centerY = 100 + row * cellSize + cellRadius;

    switch (board[row][col]) {
    case 'X':
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break;
    case 'O':
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        break;
    default:
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        break;
    }

    drawCircle(renderer, centerX, centerY, cellRadius);
    SDL_Rect updateRect = { centerX - cellRadius, centerY - cellRadius, cellSize, cellSize };
    SDL_RenderFillRect(renderer, &updateRect);
    SDL_RenderPresent(renderer);
}

bool Game::isBoardFull(const std::vector<std::vector<char>>& board) const {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == '-') {
                return false;
            }
        }
    }
    return true;
}

int Game::scorePosition(const std::vector<std::vector<char>>& board, char piece) {
    int score = 0;
    int n = board.size();
    char opponentPiece = (piece == 'X') ? 'O' : 'X';

    std::vector<char> centerArray(n);
    for (int i = 0; i < n; i++) {
        centerArray[i] = board[i][n / 2];
    }
    int centerCount = std::count(centerArray.begin(), centerArray.end(), piece);
    score += centerCount * 6;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n - WIN_LENGTH + 1; c++) {
            std::vector<char> window(WIN_LENGTH);
            for (int i = 0; i < WIN_LENGTH; i++) {
                window[i] = board[r][c + i];
            }
            score += evaluateWindow(window, piece);
        }
    }

    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n - WIN_LENGTH + 1; r++) {
            std::vector<char> window(WIN_LENGTH);
            for (int i = 0; i < WIN_LENGTH; i++) {
                window[i] = board[r + i][c];
            }
            score += evaluateWindow(window, piece);
        }
    }

    for (int r = 0; r < n - WIN_LENGTH + 1; r++) {
        for (int c = 0; c < n - WIN_LENGTH + 1; c++) {
            std::vector<char> window(WIN_LENGTH);
            for (int i = 0; i < WIN_LENGTH; i++) {
                window[i] = board[r + i][c + i];
            }
            score += evaluateWindow(window, piece);
        }
    }

    for (int r = WIN_LENGTH - 1; r < n; r++) {
        for (int c = 0; c < n - WIN_LENGTH + 1; c++) {
            std::vector<char> window(WIN_LENGTH);
            for (int i = 0; i < WIN_LENGTH; i++) {
                window[i] = board[r - i][c + i];
            }
            score += evaluateWindow(window, piece);
        }
    }

    return score;
}

int Game::evaluateWindow(const std::vector<char>& window, char piece) {
    int score = 0;
    char opponentPiece = (piece == 'X') ? 'O' : 'X';
    int countPiece = std::count(window.begin(), window.end(), piece);
    int countOpponent = std::count(window.begin(), window.end(), opponentPiece);
    int countEmpty = std::count(window.begin(), window.end(), '-');

    if (countPiece == 5) {
        score += 1000;
    }
    else if (countPiece == 4 && countEmpty == 1) {
        score += 10;
    }
    else if (countPiece == 3 && countEmpty == 2) {
        score += 5;
    }

    if (countOpponent == 4 && countEmpty == 1) {
        score -= 80;
    }

    return score;
}

int Game::minimax(std::vector<std::vector<char>>& board, int depth, int alpha, int beta, bool isMaximizingPlayer) {
    //std::cout << "Minimax call at depth " << depth << " for player " << (isMaximizingPlayer ? 'X' : 'O') << std::endl; // Journalisation pour le débogage

    bool isTerminal = hasWon(board, 'X') || hasWon(board, 'O') || !isMovesLeft(board);
    if (depth == 0 || isTerminal) {
        if (isTerminal) {
            if (hasWon(board, 'X')) {
                return 1000;
            }
            else if (hasWon(board, 'O')) {
                return -1000;
            }
            else {
                return 0;
            }
        }
        else {
            return scorePosition(board, isMaximizingPlayer ? 'X' : 'O');
        }
    }

    if (isMaximizingPlayer) {
        int maxEval = -INF;
        for (int col = 0; col < boardSize; col++) {
            if (isValidMove(board, col)) {
                std::vector<std::vector<char>> newBoard = board;
                makeMove(newBoard, col, 'X');
                int eval = minimax(newBoard, depth - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = INF;
        for (int col = 0; col < boardSize; col++) {
            if (isValidMove(board, col)) {
                std::vector<std::vector<char>> newBoard = board;
                makeMove(newBoard, col, 'O');
                int eval = minimax(newBoard, depth - 1, alpha, beta, true);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
    }
}

Move Game::findBestMove(std::vector<std::vector<char>>& board) {
    int bestValue = -INF;
    Move bestMove = { -1, -1 };
    for (int col = 0; col < boardSize; col++) {
        if (isValidMove(board, col)) {
            std::vector<std::vector<char>> newBoard = board;
            int row = getNextOpenRow(newBoard, col);
            makeMove(newBoard, col, 'X');
            int moveValue = minimax(newBoard, MAX_DEPTH - 1, -INF, INF, false);
            //std::cout << "Evaluating move (" << row << ", " << col << ") with value " << moveValue << std::endl;
            if (moveValue > bestValue) {
                bestMove = { row, col };
                bestValue = moveValue;
            }
        }
        else {
            //std::cout << "Column " << col << " is not a valid move." << std::endl;
        }
    }
    //std::cout << "Best move selected: (" << bestMove.row << ", " << bestMove.col << ")" << std::endl;
    return bestMove;
}


int Game::getNextOpenRow(const std::vector<std::vector<char>>& board, int col) const {
    for (int row = board.size() - 1; row >= 0; row--) {
        if (board[row][col] == '-') {
            return row;
        }
    }
    return -1; // Retourne -1 si la colonne est pleine
}


bool Game::isMovesLeft(const std::vector<std::vector<char>>& board) const {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == '-') {
                return true;
            }
        }
    }
    return false;
}
