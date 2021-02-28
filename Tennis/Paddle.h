#pragma once

#include "Vector.h"


namespace TennisApp
{
	class Paddle
		//: public IMovable
	{
	public:
		Paddle();

		void initialize(int x, int y);

#if 0
		// Move the object to the specified distance (positive or negative).
		virtual void moveTo(int distX, int distY) override;
#endif

		void updatePos(HWND hWnd, int direction, int wallThickness);

		void draw(HDC hDc);

	private:
		Vector2Int m_center = {};

		float m_velocity = {};
	};
}
