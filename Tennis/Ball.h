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

		void moveTo(int x, int y);

		void updatePos(float delta);

		void draw(HDC hDc);

		void resizeGameField(const RECT& rect);

	private:
		Vector2 m_center = {};

		const Vector2 m_velocity = {};

		const int Width = 25;

		// Game field rectangle.
		RECT m_field = {};
	};
}
