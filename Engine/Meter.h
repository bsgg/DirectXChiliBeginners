#pragma once
#include "Graphics.h"
#include "Dude.h"


class Meter
{
public:
	Meter(int x, int y)
		:
		x(x),
		y(y)
	{};

	void IncreaseLevel()
	{
		++level;
	}

	int GetLevel() const
	{
		return level;
	}

	void Draw(Graphics& gfx) const
	{
		
		gfx.DrawRectDim(x, y, scale * level , heigth, color);
	}
private:

	static constexpr Color color = Colors::Cyan;	
	static constexpr int heigth = 12;
	static constexpr int scale = 4;
	int level = 0;
	int x;
	int y;

};
