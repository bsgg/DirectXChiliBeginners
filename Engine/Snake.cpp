#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{ 10,100,32 },
		{ 10,130,48 },
		{ 10,160,48 },
		{ 10,130,48 }
	};

	// Process  the segments from the tail but not process the head
	for (int i = 0; i< nSegmentMax; ++i)
	{
		// Init the color of the body in all the segments
		// Using the module, we can limit the index so 
		// i = 0 -> 0/4 = 0 ->%0
		// i = 1 -> 1/4 = 0 ->%1
		// i = 2 -> 2/4 = 0 ->%2
		// i = 3 -> 3/4 = 0 ->%3
		// i = 4 -> 4/4 = 1 ->%0
		// .. i = 15 -> 15/4 = 3 ->%3
		// .. i = 21 -> 21/4 = 5 ->% 1
		// The index will be always between 0 and 4
		int index = i % nBodyColors;
		segments[i].InitBody(bodyColors[index]);
	}

	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	// Process  the segments from the tail but not process the head
	for (int i = nSegments - 1; i > 0; --i)
	{
		// Move the segment which is befor this one
		segments[i].Follow(segments[i - 1]);
	}
	// Move the head
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNexHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	if (nSegments < nSegmentMax)
	{
		//segments[nSegments].InitBody();
		++nSegments;
	}
}


void Snake::Draw(Board & board) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(board);
	}	
}


bool Snake::IsInTile(const Location & target) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	// Exclude the end of the snake
	// If the head and the tail are align (in pararell)
	// If the head moves up the tail will go right, 
	// so this is not a fail condition.
	for (int i = 0; i < nSegments-1; ++i)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	// HeadColor is private but Segment is private inside Snake so it´s possible to access
	// private members inside private clases
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color color)
{
	c = color;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	// Assert to check that we only move the snake 1 cell (so or x or y can be 1 (possitve or negative))
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & board) const
{
	board.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}

