#pragma once

#include "Timer.h"
#include "Config.h"
#include "Texture.h"
#include <SDL.h>
#include <math.h>


//The dot that will move around on the screen
class Dot
{
public:
	////The dimensions of the dot
	//static const int config.getDotWidth() = 20;
	//static const int config.getDotHeight() = 20;

	////Maximum axis velocity of the dot
	//static const int DOT_VEL = 640;


	Config c;

	//Initializes the variables
	Dot(SDL_Renderer & gRenderer);

	int getPlayer1Score();
	int getPlayer2Score();

	void setPlayer1Score(int p1);
	void setPlayer2Score(int p2);

	float getMPosX();
	float getMPosY();

	//load Media Dot
	bool loadMediaDot(SDL_Renderer& gRenderer);

	//Takes key presses and adjusts the dot's velocity
	//void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(float timeStep);

	//Shows the dot on the screen
	void render(SDL_Renderer* gRenderer);

	//Shows the dot on the screen
	void renderScore(SDL_Renderer* gRenderer);

	//Reset position initial
	void resetPosition();

	//Box collision detector
	bool checkCollision(int ax, int ay);

	void free();


private:
	bool isLoaded;
	float mPosX, mPosY;
	float mVelX, mVelY;

	//Scene textures
	Texture gDotTexture;
	Texture gPromptTextTexture;
	Texture gInputTextTexture;
	Texture gInputTextTexture2;

	//Players
	int player1 = 0, player2 = 0;
	int displayScore1 = -1, displayScore2 = -1;
};