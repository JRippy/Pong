#include "pch.h"
#include "LTexture.h"
#include "LTimer.h"
#include "Racket.h"
#include "Dot.h"
#include "Config.h"
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

Config config;

//The dot that will be moving around on the screen
Dot dot;

//Racket that will be moving on the left screen
Racket r1 = Racket();

//Racket that will be moving on the right screen
Racket r2 = Racket(config.getScreenWidth() - config.getRacketWidth(), 0);

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
//LTexture gDotTexture;
//LTexture gRacketTexture;
LTexture gPromptTextTexture;
LTexture gInputTextTexture;


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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	success = dot.loadMediaDot(gRenderer);

	return success;
}

void close()
{
	//Free loaded images
	dot.free();
	r1.free();
	r2.free();

	//Free loaded images
	gPromptTextTexture.free();
	gInputTextTexture.free();

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
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set text color as White
			SDL_Color textColor = { 255, 255, 255, 255 };
			//gInputTextTexture.loadFromRenderedText(std::to_string("MDR").c_str(), textColor, gRenderer);
			gInputTextTexture.loadFromRenderedText("MDR", textColor, gRenderer);
//------------------------------------------------------------------------------------------------------------------

			//Enable text input
			SDL_StartTextInput();

			//Keeps track of time between steps
			LTimer stepTimer;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent(e);
					r1.handleEvent(e);
					r2.handleEvent(e);
				}

				//Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				SDL_RenderClear(gRenderer);

				//Move for time step
				dot.move(timeStep);
				dot.checkCollision((int)r1.getRPosX(), (int)r1.getRPosY());
				dot.checkCollision((int)r2.getRPosX(), (int)r2.getRPosY());

				//Restart step timer
				stepTimer.start();

				//Render dot
				dot.render(gRenderer);

				r1.move(timeStep);
				r2.move(timeStep);

				//Render racket
				r1.render(gRenderer);
				r2.render(gRenderer);

				//Render text textures
				gInputTextTexture.loadFromRenderedText("MDR", textColor, gRenderer);
				gPromptTextTexture.render((config.getScreenWidth() - gPromptTextTexture.getWidth()) / 2, 0, gRenderer);
				gInputTextTexture.render((config.getScreenWidth() - gInputTextTexture.getWidth()) / 2, gPromptTextTexture.getHeight(), gRenderer);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}