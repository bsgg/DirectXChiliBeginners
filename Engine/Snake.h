#pragma once

#include "Board.h"
#include "Location.h"


class Snake
{
private:

	// Class segment which represents a piece of the whole snake
	// Internal and private class inside Snake (inner class)
	// The outside world doesn´t need anything about this element
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color color);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& board) const;
		const Location& GetLocation() const;
		
		
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNexHeadLocation(const Location& delta_loc) const;
	void Grow();	
	bool IsInTile(const Location& target) const;
	bool IsInTileExceptEnd(const Location& target) const;
	void Draw(Board& board) const;

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentMax = 100;
	Segment segments[nSegmentMax];
	int nSegments = 1;
};