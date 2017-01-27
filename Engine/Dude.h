#pragma once
#include "Graphics.h"
#include "Keyboard.h"
class Dude
{
public:
		
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd);
	void ClampToScreen();

	// Getter for position
	float GetX() const
	{
		return x;
	}
	float GetY() const
	{
		return y;
	}

	// width and height are static constexpr so, to make a getter, the function has to be static as well.
	// In this case we can make the function const because the memeber is static so is not related to any object.
	static float GetWidth()
	{
		return width;
	}
	static float GetHeight()
	{
		return height;
	}

private:

	float x = 400.0f;
	float y = 300.0f;

	// width and height isn't gonna change
	// const and constexpr means that the member is gonna have the same value every time
	// and const could have diferent value.
	static constexpr float width = 20.0f;
	static constexpr float height = 20.0f;

	// Speed
	static constexpr float speed = 5.0f;
};
