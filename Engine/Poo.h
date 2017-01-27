#pragma once
#include "Graphics.h"
#include "Dude.h"
#include <assert.h>

class Poo
{
public:
	void Init(float in_x, float in_y, float in_vx, float in_vy)
	{	
		// With this assertion we make sure that Init is called just once, if this method is called a second time
		// it will throw an exception and stop running
		assert(initialized == false);
		x = in_x;
		y = in_y;
		vx = in_vx;
		vy = in_vy;
		initialized = true;		
	};
	void Update();
	bool TestCollision(const Dude& dude) const;
	void Draw(Graphics& gfx) const;
private:
	
	// width and height isn't gonna change
	// const and constexpr means that the member is gonna have the same value every time
	// and const could have diferent value.
	static constexpr float width = 24;
	static constexpr float height = 24;
	float x;
	float y;
	float vx;
	float vy;	
	bool isEaten = false;

	bool initialized = false;
};