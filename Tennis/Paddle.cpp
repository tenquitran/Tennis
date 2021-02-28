#include "framework.h"
#include "Paddle.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////

const int Height = 100;

const int Width = 25;

const float Velocity = 35.0f;

const int RightOffset = 10;

///////////////////////////////////////////////////////////////////////////////


Paddle::Paddle()
	: m_velocity(Velocity)
{
}

void Paddle::initialize(int x, int y)
{
	m_center.m_x = x - Width / 2 - RightOffset;
	m_center.m_y = y;

	recalculateRect();
}

void Paddle::updatePos(HWND hWnd, int direction, int wallThickness)
{
	RECT client = {};

	if (!GetClientRect(hWnd, &client))
	{
		ATLASSERT(FALSE); return;
	}

	// The paddle can move only vertically.

	int newY = m_center.m_y + static_cast<int>(direction * Velocity);

	// Prevent the paddle from moving too far up.
	if (   direction < 0
		&& newY - Height / 2 <= wallThickness)
	{
		newY = Height / 2 + wallThickness;
	}

	// Prevent the paddle from moving too far down.
	if (   direction > 0
		&& newY + Height / 2 >= client.bottom - wallThickness)
	{
		newY = client.bottom - Height / 2 - wallThickness;
	}

	m_center.m_y = newY;

	recalculateRect();
}

void Paddle::draw(HDC hDc)
{
	SelectObject(hDc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	Rectangle(hDc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}

void Paddle::recalculateRect()
{
	m_rect.left = m_center.m_x - Width / 2;
	m_rect.right = m_center.m_x + Width / 2;
	m_rect.top = m_center.m_y - Height / 2;
	m_rect.bottom = m_center.m_y + Height / 2;
}

RECT Paddle::getRect() const
{
	return m_rect;
}
