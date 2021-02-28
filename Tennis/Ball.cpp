#include "framework.h"
#include "Ball.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////

const int Width = 25;

//const float Velocity = 150.0f;
const float Velocity = 75.0f;
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

bool Ball::isGone() const
{
	return m_isGone;
}

void Ball::initialize(int x, int y)
{
	m_center.m_x = x;
	m_center.m_y = y;
}

void Ball::updatePos(float delta, const RECT& paddle, int rightEdge, int paddlePosY)
{
#if 0
	m_center.m_x += m_velocity.m_x;
	m_center.m_y += m_velocity.m_y;
#endif

#if 0//def _DEBUG
	CAtlString str;
	str.Format(L"delta: %f\n", delta);
	OutputDebugStringW(str);
#endif

	if (   m_center.m_y + Width / 2 >= m_field.bottom
		&& m_velocity.m_y > 0.0f)
	{
		// Bounce off the south wall.
		m_velocity.m_y *= -1.0f;
	}
	else if (   m_center.m_y - Width / 2 <= m_field.top 
		     && m_velocity.m_y < 0.0f)
	{
		// Bounce off the north wall.
		m_velocity.m_y *= -1.0f;
	}

	if (   m_center.m_x - Width / 2 <= m_field.left
		//&& m_velocity.m_x > 0.0f
		)
	{
		// Bounce off the west wall.
		m_velocity.m_x *= -1.0f;
	}

	// Detect collision with the paddle and whether the ball has gone.

	int paddleHeight = paddle.bottom - paddle.top;

	float diff = abs(static_cast<float>(paddlePosY - m_center.m_y));

	if (// difference of the ball and paddle Y coordinates is small enough
		   diff <= paddleHeight / 2.0f 
		// the ball X coordinate is within the paddle rectangle
		&& m_center.m_x + Width / 2 >= paddle.left
		&& m_center.m_x + Width / 2 <= paddle.right 
		// the ball is moving to the right
		&& m_velocity.m_x > 0.0f)
	{
		m_velocity.m_x *= -1.0f;
	}
	else if (m_center.m_x - Width / 2 >= rightEdge)
	{
		m_isGone = true;
		return;
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

#if 0//def _DEBUG
	CAtlString str;
	str.Format(L"center: %d, %d\n", m_center.m_x, m_center.m_y);
	OutputDebugStringW(str);
#endif

	Rectangle(hDc, rect.left, rect.top, rect.right, rect.bottom);
}
