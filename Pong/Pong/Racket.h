#pragma once

#include "LTimer.h"
#include "Config.h"
#include "LTexture.h"
#include <SDL.h>

class Racket
{
public:

	Config c;

	Racket();
	Racket(int x, int y);

	float getRPosX();
	float getRPosY();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(float timeStep);

	//Shows the dot on the screen
	void render(SDL_Renderer* gRenderer);

	void free();

private:
	float rPosX, rPosY; // remplacer par sdl_rect
	float rVelX, rVelY;

	//Texture
	LTexture gRacketTexture;
};