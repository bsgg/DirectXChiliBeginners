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
	bool CheckForObstacle(const Location& loc) const;
	// Use of forward declaration to avoid any circular dependencies with snake and board
	// Snake.h already include Board, so that´s why we can´t include Snake in this header file
	void SpawnObstacle(std::mt19937& rng, const class Snake& snake);
	void DrawBorder();
	

private:
	static constexpr Color borderColor = Colors::Blue;

	static constexpr int dimension = 20;
	static constexpr int cellPadding = 1;
	static constexpr int width = 32;
	static constexpr int height = 24;
	
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;

	static constexpr int x = 70;
	static constexpr int y = 20;

	// Initialize all the elements with {}
	bool hasObstacle[width * height] = { false };
	Graphics& gfx;
};
