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

		void updatePos(float delta, const RECT& paddle, int rightEdge, int paddlePosY);

		void draw(HDC hDc);

		void resizeGameField(const RECT& rect);

		bool isGone() const;

	private:
		Vector2Int m_center = {};

		Vector2Float m_velocity = {};

		// Game field rectangle.
		RECT m_field = {};

		// true if the ball has gone off the screen.
		bool m_isGone = { false };
	};
}
