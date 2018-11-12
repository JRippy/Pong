#include "pch.h"
#include "DashedLine.h"


DashedLine::DashedLine()
{
	dashRacket.x = 200;
	dashRacket.y = 200;
	dashRacket.w = c.getRacketWidth();
	dashRacket.h = c.getMiniRacketHeight();

}


DashedLine::~DashedLine()
{
}

void DashedLine::load(SDL_Renderer * gRenderer)
{

}

void DashedLine::render(SDL_Renderer * gRenderer)
{
	//Render racket
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &dashRacket);
	SDL_RenderFillRect(gRenderer, &dashRacket);

	int n = c.getScreenWidth() / 2 - c.getRacketWidth() / 2;
	int m = 0;

	for (int i = 0; i < 10; i ++)
	{
		printf("Numero Racket : %d; Position Racket : %d \n", i, m);
		//Show the Racket
		dashRacket.x = n;
		dashRacket.y = m;
		SDL_RenderDrawRect(gRenderer, &dashRacket);
		SDL_RenderFillRect(gRenderer, &dashRacket);
		gRacketTexture.render(n, m, gRenderer);
		m += 2 * dashRacket.h;

	}

}