#pragma once

//#include "Movable.h"
#include "Vector.h"


namespace TennisApp
{
	class Ball
		//: public IMovable
	{
	public:
		Ball();

		void initialize(int x, int y);

		void updatePos(float delta, const RECT& paddle);

		void draw(HDC hDc);

		void resizeGameField(const RECT& rect);

	private:
		Vector2Int m_center = {};

		Vector2Float m_velocity = {};

		// Game field rectangle.
		RECT m_field = {};
	};
}
