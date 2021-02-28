#pragma once

#include "Movable.h"


namespace TennisApp
{
	class Paddle
		//: public IMovable
	{
	public:
		Paddle(int x, int y);

#if 0
		// Move the object to the specified distance (positive or negative).
		virtual void moveTo(int distX, int distY) override;
#endif

	private:
		POINT m_center = {};
	};
}
