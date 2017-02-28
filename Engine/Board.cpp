#include "Board.h"
#include "Snake.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:gfx(gfx)
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);	
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x * dimension + off_x + cellPadding, loc.y * dimension + off_y + cellPadding, dimension - cellPadding * 2, dimension - cellPadding * 2, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return	(loc.x >= 0) && 
			(loc.x < width) && 
			( loc.y >= 0) && 
			(loc.y < height);
}

int Board::GetContents(const Location & loc) const
{
	return contents[width * loc.y + loc.x];
}

void Board::ConsumeContents(const Location& loc)
{
	// The only content to consume is food not any other content
	assert(GetContents(loc) == 2);
	contents[width * loc.y + loc.x] = 0;
}

void Board::SpawnObstacle(std::mt19937 & rng, const Snake & snake)
{
	// Random location
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);

		// Check another location if snake is this location or the board has already another obstacle or a goal
	} while (snake.IsInTile(newLoc) || (GetContents(newLoc) != 0));
	
	// Include new obstacle
	contents[newLoc.y * width + newLoc.x] = 1;
}

void Board::SpawnFood(std::mt19937& rng, const class Snake& snake)
{
	// Random location
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);

		// Check another location if snake is this location or the board has already another obstacle or a goal
	} while (snake.IsInTile(newLoc) || (GetContents(newLoc) != 0));

	// Include new obstacle
	contents[newLoc.y * width + newLoc.x] = 2;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	// Top border rect
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);
	// Left border rect
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, borderColor);
	// Right border rect
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, borderColor);
	// Bottom border rect
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, borderColor);

}

void Board::DrawCells()
{	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const int contents = GetContents({ x,y });
			if (contents == 1)
			{
				DrawCell({ x, y }, obstacleColor);
			}else if (contents == 2)
			{
				DrawCell({ x, y }, foodColor);
			}
		}
	}
}
