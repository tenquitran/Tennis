#pragma once

#include "Vector.h"


namespace TennisApp
{
	class Paddle
	{
	public:
		Paddle();

		void initialize(int x, int y);

		void updatePos(HWND hWnd, int direction, int wallThickness);

		void draw(HDC hDc);

		RECT getRect() const;

		int getPaddlePosY() const;

	private:
		void recalculateRect();

	private:
		Vector2Int m_center = {};

		float m_velocity = {};

		// Paddle rectangle.
		RECT m_rect = {};
	};
}
