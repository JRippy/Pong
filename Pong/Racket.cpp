#pragma once
#include "pch.h"
#include "Racket.h"

Racket::Racket()
{
	//Initialize the position
	rPosX = 0;
	rPosY = 0;

	//Initialize the velocity
	rVelX = 0;
	rVelY = 0;
}

Racket::Racket(float x, float y)
{
	//Initialize the position
	rPosX = x;
	rPosY = y;

	//Initialize the velocity
	rVelX = 0;
	rVelY = 0;
}

float Racket::getRPosX()
{
	return rPosX;
}

float Racket::getRPosY()
{
	return rPosY;
}

void Racket::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_MOUSEMOTION && e.key.repeat == 0)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Adjust position
		rPosY = y;

	}

}

void Racket::move(float timeStep)
{

	//Move the racket up or down
	rPosY += rVelY * timeStep;

	//If the racket went too far up or down
	if (rPosY < 0)
	{
		rPosY = 0;
	}
	else if (rPosY > c.getScreenHeight() - c.getRacketHeight())
	{
		rPosY = c.getScreenHeight() - c.getRacketHeight();
	}

}

void Racket::moveOpponent(float timeStep, float dPosX, float dPosY)
{
	if (dPosX > c.getScreenWidth() / 2)
	{
		rPosY = dPosY + (c.getDotHeight() / 2) - (c.getRacketHeight() / 2);
		move(timeStep);
	}

}

void Racket::render(SDL_Renderer* gRenderer)
{

	SDL_Rect racket;
	racket.x = (int)rPosX;
	racket.y = (int)rPosY;
	racket.w = c.getRacketWidth();
	racket.h = c.getRacketHeight();

	//Render racket
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &racket);
	SDL_RenderFillRect(gRenderer, &racket);


	//Show the Racket
	gRacketTexture.render((int)rPosX, (int)rPosY, gRenderer);
}

void Racket::free()
{
	gRacketTexture.free();
}
