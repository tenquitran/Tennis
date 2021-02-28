#include "framework.h"
#include "Ball.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////

//const float Velocity = 150.0f;
const float Velocity = -75.0f;
//const int Velocity = 5;

///////////////////////////////////////////////////////////////////////////////


Ball::Ball()
	: m_velocity(Velocity, Velocity)
{
}

void Ball::resizeGameField(const RECT& rect)
{
	m_field = rect;
}

void Ball::moveTo(int x, int y)
{
	m_center.m_x = x;
	m_center.m_y = y;
}

void Ball::updatePos(float delta)
{
#if 0
	m_center.m_x += m_velocity.m_x;
	m_center.m_y += m_velocity.m_y;
#else

#ifdef _DEBUG
	CAtlString str;
	str.Format(L"delta: %f\n", delta);
	OutputDebugStringW(str);
#endif

	if (   m_center.m_y + Width / 2 >= m_field.bottom
		&& m_velocity.m_y > 0.0f)
	{
		// Bounce off the south wall.
		m_velocity.m_y *= -1;
	}
	else if (   m_center.m_y - Width / 2 <= m_field.top 
		     && m_velocity.m_y < 0.0f)
	{
		// Bounce off the north wall.
		m_velocity.m_y *= -1;
	}

	if (   m_center.m_x - Width / 2 <= m_field.left
		//&& m_velocity.m_x > 0.0f
		)
	{
		// Bounce off the west wall.
		m_velocity.m_x *= -1;
	}

	m_center.m_x += static_cast<int>(m_velocity.m_x * delta);
	m_center.m_y += static_cast<int>(m_velocity.m_y * delta);
}

void Ball::draw(HDC hDc)
{
	SelectObject(hDc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	RECT rect = {};

	rect.left   = m_center.m_x - Width / 2;
	rect.right  = m_center.m_x + Width / 2;
	rect.top    = m_center.m_y - Width / 2;
	rect.bottom = m_center.m_y + Width / 2;

#ifdef _DEBUG
	CAtlString str;
	str.Format(L"center: %d, %d\n", m_center.m_x, m_center.m_y);
	OutputDebugStringW(str);
#endif

	Rectangle(hDc, rect.left, rect.top, rect.right, rect.bottom);
}
