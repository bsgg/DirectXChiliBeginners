/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game2.h"
#include "SpriteCodex.h"

Game2::Game2(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(gfx),
	rng(std::random_device()()),
	snake({ 2,2 })
{
	// Spawn food
	board.SpawnFood(rng, snake);
}

void Game2::Go()
{
	// Starts a frame
	gfx.BeginFrame();

	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateFrame(dt);
		elapsedTime -= dt;
	}

	DrawFrame();
	// End frame and here is when the graphics draw
	gfx.EndFrame();
}

// Game Logic
void Game2::UpdateFrame(float dt)
{
	if (gameIsStarted)
	{
		if (!gameIsOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0,-1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0,1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1,0 };
			}

			float snakeModifiedMovePeriod = snakeMovePeriod;
			if (wnd.kbd.KeyIsPressed(VK_CONTROL))
			{
				snakeModifiedMovePeriod = std::min(snakeMovePeriod, snakeMovePeriodSpeedup);
			}

			// Move the snake according to the rate
			snakeMoveCounter += dt;
			if (snakeMoveCounter >= snakeModifiedMovePeriod)
			{
				snakeMoveCounter -= snakeModifiedMovePeriod;
				const Location next = snake.GetNexHeadLocation(delta_loc);
				const int contents = board.GetContents(next);
				if (!board.IsInsideBoard(next) ||
					snake.IsInTileExceptEnd(next) || 
					contents == 1) // Obstacle
				{
					gameIsOver = true;
				}
				else if (contents == 2) // Food
				{
					// Make snake grow and consumn the food
					snake.Grow();
					snake.MoveBy(delta_loc);
					board.ConsumeContents(next);
					board.SpawnFood(rng, snake);
					board.SpawnObstacle(rng, snake);
				}
				else
				{
					// Empty place, move snake
					snake.MoveBy(delta_loc);
				}
			}
			snakeMovePeriod = std::max(snakeMovePeriod - dt * snakeMovePeriodSpeedup, snakeMovePeriodMin);
		}
	}
	else
	{
		gameIsStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}


// Game Draw
void Game2::DrawFrame()
{
	// Range for the random
	/*std::uniform_int_distribution<int> colorDist(0,255);
	for (int y = 0; y < board.GetGridHeight(); y++)
	{
		for (int x = 0; x < board.GetGridWidth();x++)
		{
			// It is possible to initialize classes or structs with {}
			// if they have no private data and specify no constructors
			Location loc = { x,y };
			//Color c (colorDist(rng), colorDist(rng), colorDist(rng));
			Color c(255, 255,255);
			board.DrawCell(loc, c);
		}
	}*/
	
	// Draw snake
	if (gameIsStarted)
	{
		snake.Draw(board);
		board.DrawCells();

		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(358, 268, gfx);
		}

		board.DrawBorder();
	}
	else
	{
		SpriteCodex::DrawSnakeTitle(290, 225, gfx);
	}
}
