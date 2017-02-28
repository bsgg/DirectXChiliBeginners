#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "FrameTimer.h"
#include <random>

class Game2
{
public:
	Game2(class MainWindow& wnd);
	Game2(const Game2&) = delete;
	Game2& operator=(const Game2&) = delete;
	void Go();
private:
	void DrawFrame();
	void UpdateFrame(float dt);
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;

	std::mt19937 rng;
	Board board;
	Snake snake;
	// Snake starts moving to the right
	Location delta_loc = { 1,0 };
	
	// How many frames the snake takes to move (60 / 20 = 3 frames per second)
	static constexpr float snakeMovePeriodMin = 0.06f;
	static constexpr float snakeMovePeriodSpeedup = 0.15f;
	float snakeMovePeriod = 0.4f;
	float snakeMoveCounter = 0.0f;
	static constexpr float snakeSpeedupPeriod = 0.05f;
	int snakeSpeedupPeriodCounter = 0;
	bool gameIsOver = false;
	bool gameIsStarted = false;
};
