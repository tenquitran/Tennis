#include "framework.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////


Game::Game()
{
	m_ticks = GetTickCount64();
}

Game::~Game()
{
}

bool Game::initialize(HWND hWnd)
{
	// Create walls.
	m_walls.emplace_back(Wall(EWallType::West));
	m_walls.emplace_back(Wall(EWallType::North));
	m_walls.emplace_back(Wall(EWallType::South));

	// Place the ball to the center of the screen.

	RECT wndRect = {};

	if (!GetClientRect(hWnd, &wndRect))
	{
		ATLASSERT(FALSE); return false;
	}

#if 0
	// Move the ball to the center of the screen.

	int centerX = (wndRect.right - wndRect.left) / 2;
	int centerY = (wndRect.bottom - wndRect.top) / 2;

	m_ball.moveTo(centerX, centerY);
#else
	m_ball.moveTo(25, 25);
#endif

	return true;
}

bool Game::shutdown()
{
	// TODO: stub
	return true;
}

#if 0
bool Game::shouldRun() const
{
	return m_shouldRun;
}
#endif

void Game::processInput()
{
}

void Game::updateState()
{
	// Time elapsed since last frame (in seconds)...
	float delta = (GetTickCount64() - m_ticks) / 1000.0f;

	// Clamp maximum delta value.
	if (delta > 0.05f)
	{
		delta = 0.05f;
	}

	m_ball.updatePos(delta);
}

void Game::render(HDC hDc)
{
	for (auto& itr : m_walls)
	{
		itr.draw(hDc);
	}

	m_ball.draw(hDc);
}

int Game::getWallThickness() const
{
	if (m_walls.empty())
	{
		ATLASSERT(FALSE); return 0;
	}

	// All walls are of the same thickness.
	return m_walls.cbegin()->getThickness();
}

void Game::resize(HWND hWnd)
{
	RECT client = {};

	if (!GetClientRect(hWnd, &client))
	{
		ATLASSERT(FALSE); return;
	}

	for (auto& itr : m_walls)
	{
		itr.resize(client);
	}

	int thickness = getWallThickness();

	RECT field = {};
	field.left = thickness;
	field.top = thickness;
	field.right = client.right;
	field.bottom = client.bottom - thickness;

	m_ball.resizeGameField(field);
}
