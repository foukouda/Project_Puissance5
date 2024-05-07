#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Bouton.h"

class Game {

public: 
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width,int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	Button* startButton;
	Button* quitButton;
	Button* musiqueButton;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Button* button;
};

