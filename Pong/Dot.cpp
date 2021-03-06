#include "pch.h"
#include "Dot.h"


Dot::Dot()
{
}

Dot::Dot(SDL_Renderer * gRenderer) :
	mVelX((float)c.getDotVel()),
	mVelY((float)c.getDotVel()),
	Loaded(false)
{
	scoreDot = Score();
	resetPosition();
	Loaded = loadMediaDot(gRenderer);
}

int Dot::getPlayer1Score()
{
	return scoreDot.getScore1();
}

int Dot::getPlayer2Score()
{
	return scoreDot.getScore2();
}

void Dot::initScore()
{
	scoreDot.init();
}

float Dot::getMPosX()
{
	return mPosX;
}

float Dot::getMPosY()
{
	return mPosY;
}

bool Dot::loadMediaDot(SDL_Renderer * gRenderer)
{
	//Loading success flag
	Loaded = true;

	//Load dot texture
	if (!gDotTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		Loaded = false;
	}

	return Loaded;
}

bool Dot::isLoaded()
{
	return Loaded;
}

void Dot::move(float timeStep)
{

	//Move the dot left or right
	mPosX += mVelX * timeStep;

	//If the dot went too far to the left or right
	if (mPosX <= 0)
	{
		mVelX = -mVelX;
		resetPosition();
		scoreDot.addScore1();

	}
	else if (mPosX + c.getDotWidth() >= c.getScreenWidth())
	{
		mVelX = -mVelX;
		resetPosition();
		scoreDot.addScore2();

	}

	//Move the dot up or down
	mPosY += mVelY * timeStep;

	//If the dot went too far up or down
	if (mPosY < 0)
	{
		mVelY = -mVelY;
	}
	else if (mPosY + c.getDotHeight() > c.getScreenHeight())
	{
		mVelY = -mVelY;
	}

}

void Dot::render(SDL_Renderer* gRenderer)
{
	//Load dot texture
	if (!gDotTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
	}

	//Show the dot
	gDotTexture.render((int)mPosX, (int)mPosY, gRenderer);
}

void Dot::renderScore(SDL_Renderer* gRenderer)
{
	SDL_Color textColor = { 255, 255, 255, 255 };

	/*
	NOTE
	Pas de chargement de donn�e � chaque frame. Le jeu plante au bout de 40 secondes.
	*/
	if (displayScore1 != scoreDot.getScore1() || displayScore2 != scoreDot.getScore2())
	{
		gInputTextTexture.loadFromRenderedText(std::to_string(scoreDot.getScore1()).c_str(), textColor, gRenderer);
		gPromptTextTexture.render((c.getScreenWidth() - gPromptTextTexture.getWidth()) / 4, 0, gRenderer);
		//gInputTextTexture.render((c.getScreenWidth() - gInputTextTexture.getWidth()) / 4, gPromptTextTexture.getHeight(), gRenderer);

		gInputTextTexture2.loadFromRenderedText(std::to_string(scoreDot.getScore2()).c_str(), textColor, gRenderer);
		gPromptTextTexture.render(((c.getScreenWidth() - gPromptTextTexture.getWidth())) * 3 / 4, 0, gRenderer);
		//gInputTextTexture.render((c.getScreenWidth() - gInputTextTexture.getWidth()) * 3 / 4, gPromptTextTexture.getHeight(), gRenderer);

		displayScore1 = scoreDot.getScore1();
		displayScore2 = scoreDot.getScore2();
	}

	//gInputTextTexture.loadFromRenderedText(std::to_string(player1).c_str(), textColor, gRenderer);
	//gPromptTextTexture.render((c.getScreenWidth() - gPromptTextTexture.getWidth()) / 4, 0, gRenderer);
	gInputTextTexture.render((c.getScreenWidth() - gInputTextTexture.getWidth()) / 4, gPromptTextTexture.getHeight(), gRenderer);

	//gInputTextTexture.loadFromRenderedText(std::to_string(player2).c_str(), textColor, gRenderer);
	//gPromptTextTexture.render(((c.getScreenWidth() - gPromptTextTexture.getWidth())) * 3 / 4, 0, gRenderer);
	gInputTextTexture2.render((c.getScreenWidth() - gInputTextTexture2.getWidth()) * 3 / 4, gPromptTextTexture.getHeight(), gRenderer);

}

void Dot::resetPosition() {
	//Initialize the position
	mPosX = (float)c.getScreenWidth() / 2 - (float)c.getDotWidth();
	mPosY = (float)c.getScreenHeight() / 2 - (float)c.getDotHeight();
}

bool Dot::checkCollision(int ax, int ay)
{
	//The sides of the rectangles
	int ah;
	int aw;

	//Calculate dimensions of rect A
	aw = ax + c.getRacketWidth();
	ah = ay + c.getRacketHeight();


	float dotYMiddle = mPosY + (c.getDotHeight() / 2);

	if (mPosX + c.getDotWidth() >= ax && mPosX <= aw && mPosY + c.getDotHeight() >= ay && mPosY <= ah)
	{		
		const float Pi = 3.141592654f;
		float MAXBOUNCEANGLE = 5 * Pi / 12;
		
		float relativeIntersectY = (ay + (c.getRacketHeight() / 2)) - dotYMiddle;
		float normalizedRelativeIntersectionY = (relativeIntersectY / (c.getRacketHeight() / 2));
		float bounceAngle = normalizedRelativeIntersectionY * MAXBOUNCEANGLE;

		mVelX = -mVelX;
		mVelY = -c.getDotVel() * sin(bounceAngle);

		return true;
	}

	//If no collision
	return false;
}

void Dot::free()
{
	gDotTexture.free();
}


//void Dot::handleEvent(SDL_Event& e)
//{
//	//If a key was pressed
//	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
//	{
//		//Adjust the velocity
//		switch (e.key.keysym.sym)
//		{
//		case SDLK_UP: mVelY -= c.getDotVel(); break;
//		case SDLK_DOWN: mVelY += c.getDotVel(); break;
//		case SDLK_LEFT: mVelX -= c.getDotVel(); break;
//		case SDLK_RIGHT: mVelX += c.getDotVel(); break;
//		}
//	}
//	//If a key was released
//	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
//	{
//		//Adjust the velocity
//		switch (e.key.keysym.sym)
//		{
//		case SDLK_UP: mVelY += c.getDotVel(); break;
//		case SDLK_DOWN: mVelY -= c.getDotVel(); break;
//		case SDLK_LEFT: mVelX += c.getDotVel(); break;
//		case SDLK_RIGHT: mVelX -= c.getDotVel(); break;
//		}
//	}
//}