#pragma once
#include "Racket.h"
class DashedLine :
	public Racket
{
public:
	DashedLine();
	~DashedLine();

	void render(SDL_Renderer* gRenderer);

	//Texture
	Texture gRacketTexture;

	SDL_Rect dashRacket;

	SDL_Rect dashRacketL[10];
};
