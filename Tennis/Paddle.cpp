#include "framework.h"
#include "Paddle.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////

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
}

void Paddle::updatePos(int direction)
{
	// The paddle can move only vertically.
	m_center.m_y += static_cast<int>(direction * Velocity);
}

void Paddle::draw(HDC hDc)
{
	SelectObject(hDc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	RECT rect = {};

	rect.left = m_center.m_x - Width / 2;
	rect.right = m_center.m_x + Width / 2;
	rect.top = m_center.m_y - Height / 2;
	rect.bottom = m_center.m_y + Height / 2;

	Rectangle(hDc, rect.left, rect.top, rect.right, rect.bottom);
}
