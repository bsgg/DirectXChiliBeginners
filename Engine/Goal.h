#pragma once
#include "Graphics.h"
#include "Dude.h"


class Goal
{
public:
	Goal(float in_x, float in_y)
	{
		// With this assertion we make sure that Init is called just once, if this method is called a second time
		// it will throw an exception and stop running

		x = in_x;
		y = in_y;
		
	};
	void Draw(Graphics& gfx) const
	{
		gfx.DrawRectDim((int)x, (int)y, (int)size, (int)size, color);
	}
	
	bool TestCollision(const Dude& dude) const
	{
		const float dudeRigth = dude.GetX() + Dude::GetWidth();
		const float dudeBottom = dude.GetY() + Dude::GetHeight();
		const float rightPoo = x + size;
		const float bottomPoo = y + size;

		return  (dudeRigth >= x &&
			dude.GetX() <= rightPoo &&
			dudeBottom >= y &&
			dude.GetY() <= bottomPoo);
	}

	void Respawn(float in_x, float in_y)
	{
		x = in_x;
		y = in_y;
	}

	void UpdateColor()
	{
		int constexpr rateColor = 5;
		if (colorIncreasing)
		{
			
			if (color.GetR() + 4 < 253)
			{
				color = Color(color.GetR() + 2, color.GetG() + 4, color.GetB() + 4);
			}
			else
			{
				colorIncreasing = false;
			}
		}
		else
		{
			
			if ((color.GetR() - 2) > 127)
			{
				color = Color(color.GetR() - 2, color.GetG() -4, color.GetB() - 4);
				
			}
			else
			{
				colorIncreasing = true;
			}
		}

	}
private:

	Color color = { 127,0,0 };
	bool colorIncreasing = true;
	// width and height isn't gonna change
	// const and constexpr means that the member is gonna have the same value every time
	// and const could have diferent value.
	static constexpr float size = 20;
	float x;
	float y;
	
};
