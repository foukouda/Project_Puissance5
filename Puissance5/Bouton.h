#pragma once
#include "SDL.h"
#include <functional>
#include <SDL_image.h>
#include <string>

class Button {
public:
	SDL_Texture* texture; // Texture par défaut
	SDL_Texture* defaultTexture;
	SDL_Texture* pressedTexture; 
	SDL_Rect sRect, dRect;
	bool selected;

	// mes la texture en haut a gauche de l'emplacement x y
	Button(int x, int y, int width, int height , const std::string& imagePath, const std::string& pressedImagePath, SDL_Renderer* renderer);

	// créer la destination
	void setXY(int x, int y);

	void draw(SDL_Renderer* renderer);

	bool checkClicked(int mouseX, int mouseY) const;

	void setClicked(bool clicked); // Méthode pour définir l'état cliqué
	void render(SDL_Renderer* renderer); // Méthode pour rendre le bouton

	~Button();
	void handleMouseEvent(SDL_Event& event);


private:
	
	bool isClicked; // Indique si le bouton est cliqué
	SDL_Rect clickedSrcRect; // Zone source de la texture alternative lorsque le bouton est cliqué
	SDL_Rect defaultSrcRect; // Zone source de la texture par défaut
	SDL_Rect destRect; // Rectangle de destination pour le rendu
	bool mouseOver;

};