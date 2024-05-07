#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include "Bouton.h"

/// <summary>
/// bonjour test
/// </summary>
/// 
SDL_Texture* background;
SDL_Texture* logo;
SDL_Rect srcR, destR;

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), button(nullptr){}
Game::~Game(){
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	SDL_Surface* tmpSurface = IMG_Load("assets/background.png");
	background = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	SDL_Surface* tmpSurface2 = IMG_Load("assets/LOGO.png");
	logo = SDL_CreateTextureFromSurface(renderer, tmpSurface2);
	SDL_FreeSurface(tmpSurface2);
	
	 startButton = new Button(120, 300, 360, 125,"assets/start/notpress.png","assets/start/press.png", renderer);
	 quitButton = new Button(120, 440, 360, 125, "assets/quit/notpress.png","assets/quit/press.png", renderer);
	 musiqueButton = new Button(1200, 600, 100, 160, "assets/song/notpress.png", "assets/song/press.png", renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		if (startButton->checkClicked(mouseX, mouseY)) {
			startButton->setClicked(true);
			std::cout << "Bouton Start cliqué !" << std::endl;
		}
		else if (quitButton->checkClicked(mouseX, mouseY)) {
			std::cout << "Bouton Quitter cliqué !" << std::endl;
			isRunning = false;
		}
		else if (musiqueButton->checkClicked(mouseX, mouseY)) {
			musiqueButton->setClicked(true);
			std::cout << "Bouton soud cliqué !" << std::endl;
		}
		break;
	
	default:
		break;
	}
}

void Game::update() {
	destR.h = 180;
	destR.w = 650;
	destR.x = 60;
	destR.y = 10;
}

void Game::render() {
	SDL_RenderClear(renderer);
	//afficher ici
	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderCopy(renderer, logo, NULL, &destR);
	startButton->draw(renderer);
	quitButton->draw(renderer);
	musiqueButton->draw(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}

