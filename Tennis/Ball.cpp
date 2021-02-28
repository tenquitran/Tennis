#include "framework.h"
#include "Ball.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////

const int Velocity = 150;
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

	m_center.m_x += static_cast<int>(m_velocity.m_x * delta);
	m_center.m_y += static_cast<int>(m_velocity.m_y * delta);
#endif
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
