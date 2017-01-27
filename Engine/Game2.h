#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "GoalSnake.h"
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
	void UpdateFrame();
private:
	MainWindow& wnd;
	Graphics gfx;

	std::mt19937 rng;
	Board board;
	Snake snake;
	GoalSnake goal;
	// Snake starts moving to the right
	Location delta_loc = { 1,0 };
	
	// How many frames the snake takes to move (60 / 20 = 3 frames per second)
	static constexpr int snakeMovePeriodMin = 4;
	int snakeMoveRate = 20;
	int snakeMoveCounter = 0;
	static constexpr int snakeSpeedupPeriod = 180;
	int snakeSpeedupPeriodCounter = 0;
	bool gameIsOver = false;
	bool gameIsStarted = false;
};
