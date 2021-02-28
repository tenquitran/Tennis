#include "framework.h"
#include "Wall.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////

const int Thickness = 25;

///////////////////////////////////////////////////////////////////////////////


Wall::Wall(EWallType type)
	: m_type(type)
{
}

void Wall::resize(RECT client)
{
	switch (m_type)
	{
	case EWallType::North:
		m_rect.left = {};
		m_rect.top = {};
		m_rect.right = client.right;
		m_rect.bottom = client.top + Thickness;
		break;
	case EWallType::West:
		m_rect.left = {};
		m_rect.top = {};
		m_rect.right = client.left + Thickness;
		m_rect.bottom = client.bottom;
		break;
	case EWallType::South:
		m_rect.left = {};
		m_rect.top = client.bottom - Thickness;
		m_rect.right = client.right;
		m_rect.bottom = client.bottom;
		break;
	default:
		ATLASSERT(FALSE); break;
	}
}

void Wall::draw(HDC hDc)
{
	SelectObject(hDc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	Rectangle(hDc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}

int Wall::getThickness() const
{
	return Thickness;
}
