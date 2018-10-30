#include "pch.h"
#include "DashedLine.h"


DashedLine::DashedLine()
{
	dashRacket.x = 0;
	dashRacket.y = 0;
	dashRacket.w = c.getRacketWidth();
	dashRacket.h = c.getMiniRacketHeight();

}


DashedLine::~DashedLine()
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

		//Show the Racket
		gRacketTexture.render(n, m, gRenderer);
		m += 2 * dashRacket.h;
	}

}