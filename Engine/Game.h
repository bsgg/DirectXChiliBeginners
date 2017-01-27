/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void DrawFrame();
	void UpdateFrame();
	/********************************/
	/*  User Functions              */
	/********************************/

	void DrawBox(int x, int y, int r, int g, int b);
	void DrawCross(int x, int y, int r, int g, int b);

	bool OverLapTest(int box0x, int box0y, int box1x, int box1y);
	int ClampScreenX(int x);
	int ClampScreenY(int y);

private:
	MainWindow& wnd;
	Graphics gfx;
	
	/********************************/
	/*  User Variables              */
	/********************************/
	int x_MobileBox, y_MobileBox;
	int r_MobileBox = 255, g_MobileBox = 255, b_MobileBox = 255;
	bool isBoxMode = false;
	bool inhibitLeft = false;
	bool inhibitRight = false;
	bool inhibitUp = false;
	bool inhibitDown = false;
	int vx_MobileBox = 0;
	int vy_MobileBox = 0;

	// Position for the fixed box
	int x_FixedBox0 = 100;
	int y_FixedBox0 = 100;
	int x_FixedBox1 = 200;
	int y_FixedBox1 = 100;
	int x_FixedBox2 = 300;
	int y_FixedBox2 = 100;
	bool colliding = false;

	// Square members
	int x0 = 200;
	int y0 = 200;
	int x1 = 300;
	int y1 = 300;
};