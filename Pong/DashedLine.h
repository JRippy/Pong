#pragma once
#include "Racket.h"
class DashedLine :
	public Racket
{
public:
	DashedLine();
	~DashedLine();

	void load(SDL_Renderer* gRenderer);

	void render(SDL_Renderer* gRenderer);

	//Texture
	Texture gRacketTexture;

	SDL_Rect dashRacket;

	SDL_Rect dashRacketL[10];
};
