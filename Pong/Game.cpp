#include "pch.h"
#include "Game.h"
#include "config.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::load(SDL_Renderer* gRenderer)
{
	textColor = { 255, 255, 255, 255 };
	player1 = 0;
	player2 = 0;

	newGame = true;

	r1 = Racket();

	r2 = Racket((float)c.getScreenWidth() - c.getRacketWidth(), (float)c.getScreenWidth() / 2 - c.getRacketHeight() / 2);

	//Calculate time step
	timeStep = stepTimer.getTicks() / 1000.f;

	//Dashed line
	xDL = c.getScreenWidth() / 2 - c.getRacketWidth() / 2;
	pDL = c.getScreenHeight() / 20;
	yDL = pDL;

	return dot.loadMediaDot(gRenderer);
}

bool Game::input(SDL_Renderer* gRenderer, bool quit)
{
	if (!newGame)
	{
		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				initGame();
			}
		}
	}
	else
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle input for the racket
			r1.handleEvent(e, timeStep);
		}
	}

	return quit;
}

void Game::upload()
{
	if (!endGame(player1, player2))
	{	
		//Calculate time step
		timeStep = stepTimer.getTicks() / 1000.f;

		//Move for time step
		dot.move(timeStep);
		dot.checkCollision((int)r1.getRPosX(), (int)r1.getRPosY());
		dot.checkCollision((int)r2.getRPosX(), (int)r2.getRPosY());

		r2.moveOpponent(timeStep, dot.getMPosX(), dot.getMPosY());

		//Restart step timer
		stepTimer.start();
	}

}

void Game::draw(SDL_Renderer* gRenderer)
{
	if (endGame(player1, player2))
	{
		displayWinner(player1, player2, textColor, gRenderer);
	}
	else
	{
		//Render racket
		r1.render(gRenderer);
		r2.render(gRenderer);
		
		//Render dot
		dot.render(gRenderer);

		for (int i = 0; i < 10; i += 1)
		{

			Racket rDL = Racket(xDL, yDL);
			rDL.miniRender(gRenderer);
			yDL += 2 * pDL;

		}

		//Display score
		dot.renderScore(gRenderer);
	}
}

void Game::initGame()
{
	newGame = true;
	player1 = 0;
	player2 = 0;

	dot.setPlayer1Score(player1);
	dot.setPlayer2Score(player2);
}

bool Game::endGame(int p1, int p2)
{
	bool end = false;

	if (p1 == c.getEndPartyGameScore() || p2 == c.getEndPartyGameScore())
	{
		end = true;
		newGame = false;
	}

	return end;
}

void Game::free()
{
	//Free loaded images
	dot.free();
	r1.free();
	r2.free();
}

void Game::displayWinner(int p1, int p2, SDL_Color textColor, SDL_Renderer* gRenderer)
{
	std::string winnerText = "";

	if (p1 == c.getEndPartyGameScore())
	{
		winnerText = "Player 1 Win!";
	}
	else
	{
		winnerText = "Player 2 Win!";
	}

	gInputTextTexture.loadFromRenderedText(winnerText.c_str(), textColor, gRenderer);
	gPromptTextTexture.render((c.getScreenWidth() - gPromptTextTexture.getWidth()) / 2, 0, gRenderer);
	gInputTextTexture.render((c.getScreenWidth() - gInputTextTexture.getWidth()) / 2, c.getScreenHeight() / 2, gRenderer);

	gInputTextTexture.loadFromRenderedText("Press a key", textColor, gRenderer);
	gPromptTextTexture.render((c.getScreenWidth() - gPromptTextTexture.getWidth()) / 2, 0, gRenderer);
	gInputTextTexture.render((c.getScreenWidth() - gInputTextTexture.getWidth()) / 2, c.getScreenHeight() / 3 * 2, gRenderer);
	
}
