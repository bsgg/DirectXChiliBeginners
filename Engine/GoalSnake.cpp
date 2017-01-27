#include "GoalSnake.h"

GoalSnake::GoalSnake(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	Respawn(rng, brd, snake);
}

void GoalSnake::Respawn(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);

	} while (snake.IsInTile(newLoc));
	loc = newLoc;
}

void GoalSnake::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & GoalSnake::GetLocation() const
{
	return loc;
}
