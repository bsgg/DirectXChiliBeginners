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
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	x_MobileBox(400),
	y_MobileBox(300),
	isBoxMode(false)
{
}

void Game::Go()
{
	// Starts a frame
	gfx.BeginFrame();	
	UpdateFrame();
	DrawFrame();
	// End frame and here is when the graphics draw
	gfx.EndFrame();
}

// Game Logic
void Game::UpdateFrame()
{	

	// Check keys
	// Check if we have to draw an arrow or a box
	isBoxMode = !wnd.kbd.KeyIsPressed(VK_CONTROL);

	// Update movement
	const int units = 5;
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		y_MobileBox -= units;
		y0 -= units;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		y_MobileBox += units;
		y0 += units;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		x_MobileBox += units;
		x0 += units;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		x_MobileBox -= units;
		x0 -= units;
		
	}
	x_MobileBox = ClampScreenX(x_MobileBox);
	y_MobileBox = ClampScreenY(y_MobileBox);
	
	// Check collision with each fixed box
	colliding = OverLapTest(x_MobileBox, y_MobileBox, x_FixedBox0, y_FixedBox0) ||
		OverLapTest(x_MobileBox, y_MobileBox, x_FixedBox1, y_FixedBox1) ||
		OverLapTest(x_MobileBox, y_MobileBox, x_FixedBox2, y_FixedBox2);
	if (colliding)
	{
		r_MobileBox = 232;
		g_MobileBox = 79;
		b_MobileBox = 246;
	}
	else
	{
		r_MobileBox = 255;
		g_MobileBox = 255;
		b_MobileBox = 255;
	}


	// Mouse control
	if (wnd.mouse.LeftIsPressed())
	{
		x1 = wnd.mouse.GetPosX();
		y1 = wnd.mouse.GetPosY();
	}
	
}

int Game::ClampScreenX(int x)
{
	const int farPixel = 5;
	const int left  = x - farPixel;
	const int right = x + farPixel;
	if (left < 0)
	{
		return farPixel;
	}
	else if (right >= gfx.ScreenWidth)
	{
		return (gfx.ScreenWidth - (farPixel + 1));
	}
	else
	{
		return x;
	}

}
int Game::ClampScreenY(int y)
{
	const int farPixel = 5;
	const int top = y - 5;
	const int bottom = y + 5;

	if (top < 0)
	{
		return farPixel;

	}else if (bottom >= gfx.ScreenHeight)
	{
		return gfx.ScreenHeight - (farPixel + 1);

	}else
	{
		return y;
	}	
}

bool Game::OverLapTest(int box0x, int box0y, int box1x, int box1y)
{
	// Check collision
	const int left_box0 = box0x - 5;
	const int right_box0 = box0x + 5;
	const int top_box0 = box0y - 5;
	const int bottom_box0 = box0y + 5;

	const int left_box1 = box1x - 5;
	const int right_box1 = box1x + 5;
	const int top_box1 = box1y - 5;
	const int bottom_box1 = box1y + 5;

	if ((left_box0 <= right_box1) &&
		(right_box0 >= left_box1) &&
		(top_box0 <= bottom_box1) &&
		(bottom_box0 >= top_box1))
	{
		return true;
	}
	return false;
}

// Game Draw
void Game::DrawFrame()
{
	// Check type of draw to paint
	if (isBoxMode)
	{
		// Draw mobile box
		DrawBox(x_MobileBox, y_MobileBox, r_MobileBox, g_MobileBox, b_MobileBox);
	}
	else
	{
		DrawCross(x_MobileBox, y_MobileBox, r_MobileBox, g_MobileBox, b_MobileBox);
	}

	// Paint the fixed box	
	DrawBox(x_FixedBox0, y_FixedBox0, 150,30,60);	
	DrawBox(x_FixedBox1, y_FixedBox1, 150, 30, 60);
	DrawBox(x_FixedBox2, y_FixedBox2, 150, 30, 60);

	// Draw rect
	
	gfx.DrawRect(x0, y0, x1, y1, Colors::Cyan );

	Color c(150,100,60);
	gfx.DrawRectDim(100, 100, 80, 80, c);
}

void Game::DrawBox(int x, int y, int r, int g, int b)
{
	// top left
	gfx.PutPixel(-5 + x, -5 + y, r, g, b);
	gfx.PutPixel(-4 + x, -5 + y, r, g, b);
	gfx.PutPixel(-3 + x, -5 + y, r, g, b);
	gfx.PutPixel(-5 + x, -5 + y, r, g, b);
	gfx.PutPixel(-5 + x, -4 + y, r, g, b);
	gfx.PutPixel(-5 + x, -3 + y, r, g, b);

	// top right
	gfx.PutPixel(5 + x, -5 + y, r, g, b);
	gfx.PutPixel(4 + x, -5 + y, r, g, b);
	gfx.PutPixel(3 + x, -5 + y, r, g, b);
	gfx.PutPixel(5 + x, -5 + y, r, g, b);
	gfx.PutPixel(5 + x, -4 + y, r, g, b);
	gfx.PutPixel(5 + x, -3 + y, r, g, b);

	// bottom left
	gfx.PutPixel(-5 + x, 5 + y, r, g, b);
	gfx.PutPixel(-4 + x, 5 + y, r, g, b);
	gfx.PutPixel(-3 + x, 5 + y, r, g, b);
	gfx.PutPixel(-5 + x, 5 + y, r, g, b);
	gfx.PutPixel(-5 + x, 4 + y, r, g, b);
	gfx.PutPixel(-5 + x, 3 + y, r, g, b);

	// bottom right
	gfx.PutPixel(5 + x, 5 + y, r, g, b);
	gfx.PutPixel(4 + x, 5 + y, r, g, b);
	gfx.PutPixel(3 + x, 5 + y, r, g, b);
	gfx.PutPixel(5 + x, 5 + y, r, g, b);
	gfx.PutPixel(5 + x, 4 + y, r, g, b);
	gfx.PutPixel(5 + x, 3 + y, r, g, b);
}

void Game::DrawCross(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(-5 + x, y, r,g,b);
	gfx.PutPixel(-4 + x, y, r,g,b);
	gfx.PutPixel(-3 + x, y, r,g,b);
	gfx.PutPixel( 3 + x, y, r,g,b);
	gfx.PutPixel( 4 + x, y, r,g,b);
	gfx.PutPixel( 5 + x, y, r,g,b);
	gfx.PutPixel(x, -5 + y, r,g,b);
	gfx.PutPixel(x, -4 + y, r,g,b);
	gfx.PutPixel(x, -3 + y, r,g,b);
	gfx.PutPixel(x, 3 + y, r,g,b);
	gfx.PutPixel(x, 4 + y, r,g,b);
	gfx.PutPixel(x, 5 + y, r,g,b);
}
