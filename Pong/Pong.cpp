#include "pch.h"
#include "Texture.h"
#include "Timer.h"
#include "Racket.h"
#include "Dot.h"
#include "Game.h"
#include "Config.h"
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

Config config;

Game g = Game();

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.getScreenWidth(), config.getScreenHeight(), SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					return false;
				}

			}
		}
	}

	return success;
}

void close()
{
	g.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!g.load(gRenderer))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Enable text input
			SDL_StartTextInput();

			//While application is running
			while (!quit)
			{
				quit = g.input(gRenderer, quit);
				g.update();

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				SDL_RenderClear(gRenderer);

				g.draw(gRenderer);

				//Update screen
				SDL_RenderPresent(gRenderer);

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}



//bool loadMedia()
//{
//	//Loading success flag
//	bool success = true;
//
//	//Load dot texture
//	success = dot.loadMediaDot(gRenderer);
//
//	return success;
//}
////While application is running
//while (!quit)
//{
//	quit = g.input(gRenderer, quit);
//
//
//
//	//if (g.endGame(player1, player2))
//	//{
//		//g.displayWinner(player1, player2, textColor, gRenderer);
//
//		/*
//		NOTE
//		Pourquoi ce RenderPresent ?
//		*/
//
//		//Update screen
//		//SDL_RenderPresent(gRenderer);
//
//		//while (SDL_PollEvent(&e) != 0 && !newGame)
//		//{
//
//		//	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
//		//	{
//
//				//newGame = true;
//				//player1 = 0;
//				//player2 = 0;
//
//				//dot.setPlayer1Score(player1);
//				//dot.setPlayer2Score(player2);
//
//				//Clear screen
//				/*SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
//				SDL_RenderClear(gRenderer);*/
//
//				//Update screen
//				//SDL_RenderPresent(gRenderer);
//			//}
//		//}
//	//}
//	//else
//	//{
//		/*
//		NOTE
//
//		Séparer les instructions en Input, Update et Draw.
//		Idéalement mettre cela dans des méthodes de l'objet Game.
//
//		Surtout ne pas commencer le render, faire de l'update, puis finir le render.
//
//		*/
//
//
//		//newGame = false;
//
//
//		////Calculate time step
//		//float timeStep = stepTimer.getTicks() / 1000.f;
//
//		////Handle events on queue
//		//while (SDL_PollEvent(&e) != 0)
//		//{
//		//	//User requests quit
//		//	if (e.type == SDL_QUIT)
//		//	{
//		//		quit = true;
//		//	}
//
//		//	//Handle input for the racket
//		//	//dot.handleEvent(e);
//		//	r1.handleEvent(e, timeStep);
//		//	//r2.handleEvent(e);
//		//}
//
//
//		//Clear screen
//	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
//	SDL_RenderClear(gRenderer);
//
//	////Move for time step
//	//dot.move(timeStep);
//	//dot.checkCollision((int)r1.getRPosX(), (int)r1.getRPosY());
//	//dot.checkCollision((int)r2.getRPosX(), (int)r2.getRPosY());
//
//	////Restart step timer
//	//stepTimer.start();
//
//	g.upload();
//	g.draw(gRenderer);
//
//	////Render dot
//	//dot.render(gRenderer);
//
//	//r1.move(timeStep);
//	//r2.moveOpponent(timeStep, dot.getMPosX(), dot.getMPosY());
//
//	////Render racket
//	//r1.render(gRenderer);
//	//r2.render(gRenderer);
//
//	////Dashed line
//	//float xDL = config.getScreenWidth() / 2 - config.getRacketWidth() / 2;
//	//float pDL = config.getScreenHeight() / 20;
//	//float yDL = pDL;
//
//
//	//for (int i = 0.0; i < 20; i += 2)
//	//{
//	//						
//	//	Racket rDL = Racket(xDL, yDL);
//	//	rDL.miniRender(gRenderer);
//	//	yDL += 2 * pDL;	
//
//	//}
//
//	////Display score
//	//dot.renderScore( gRenderer);
//
////}
//
////Update screen
//	SDL_RenderPresent(gRenderer);
//}