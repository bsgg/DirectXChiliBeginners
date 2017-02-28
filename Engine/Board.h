#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{

public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	int GetContents(const Location& loc) const;
	void ConsumeContents(const Location& loc);
	// Use of forward declaration to avoid any circular dependencies with snake and board
	// Snake.h already include Board, so that´s why we can´t include Snake in this header file
	void SpawnContents(std::mt19937& rng, const class Snake& snake, int contentsType);
	void DrawBorder();
	void DrawCells();

private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color foodColor = Colors::Red;

	static constexpr int dimension = 20;
	static constexpr int cellPadding = 1;
	static constexpr int width = 32;
	static constexpr int height = 24;
	
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;

	static constexpr int x = 70;
	static constexpr int y = 20;

	// Initialize all the elements with {}
	// 0: empty 1: obstacle  2:food  3:sppedup elemtn
	int contents[width * height] = { 0 };
	Graphics& gfx;
};
