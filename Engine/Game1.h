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
#include "Poo.h"
#include "Dude.h"
#include "Goal.h"
#include "Meter.h"
#include "Sound.h"
#include "SoundEffect.h"
#include <random>

class Game1
{
public:
	Game1(class MainWindow& wnd);
	Game1(const Game1&) = delete;
	Game1& operator=(const Game1&) = delete;
	void Go();
private:
	void DrawFrame();
	void UpdateFrame();
	/********************************/
	/*  User Functions              */
	/********************************/
	//void DrawPoo(int x, int y);
	void DrawGameOver(int x, int y);
	void DrawTittleScreen(int x, int y);

private:
	MainWindow& wnd;
	Graphics gfx;

	/********************************/
	/*  User Variables              */
	/********************************/
	bool IsStarted = false;
	bool GameOver = false;

	// Dude, and poos to collect

	// Important to set the variables in this order and not the random variables after Dude and Poos,
	// because this is the order of initialize that matters not in the constructor with :
	// Randomize poo positions
	// Random generator
	std::random_device rd;
	std::mt19937 rng;
	// Range for the random
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;

	// Main Character
	Dude dude;	
	Meter meter;

	// Goal for dude
	Goal goal;

	// List of poo
	static constexpr int nPoo = 10;
	Poo poos[nPoo];

	// Sounds
	SoundEffect sFart;
	Sound sGameOver;
};