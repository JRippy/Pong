#include "Texture.h"
#include "Config.h"
#include "Dot.h"
#include "Racket.h"

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#pragma once
class Game
{
public:
	Game();
	~Game();

	bool load(SDL_Renderer* gRenderer);
	bool input(SDL_Renderer* gRenderer, bool quit);
	void update();
	void draw(SDL_Renderer* gRenderer);

	void initGame();
	
	bool endGame(int p1, int p2);

	void free();

	void displayWinner(int p1, int p2, SDL_Color textColor, SDL_Renderer* gRenderer);

private:

	Config c;
	Texture gPromptTextTexture;
	Texture gInputTextTexture;


	//Set text color as White
	SDL_Color textColor;
	int player1, player2 ;

	//Keeps track of time between steps
	Timer stepTimer;
	float timeStep;

	bool newGame;


	//The dot that will be moving around on the screen
	Dot dot;

	//Racket that will be moving on the left screen
	Racket r1;

	//Racket that will be moving on the right screen
	Racket r2;

	//Dashed line
	float xDL;
	float pDL;
	float yDL;

	SDL_Event e;
};

