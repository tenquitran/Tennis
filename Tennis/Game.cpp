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

	int centerX = (wndRect.right - wndRect.left) / 2;
	int centerY = (wndRect.bottom - wndRect.top) / 2;

#if 1
	// Move the ball to the center of the screen.
	m_ball.initialize(centerX, centerY);
#else
	//m_ball.initialize(25, 25);    // top left corner
	m_ball.initialize(400, 300);    // bottom right area
#endif

	// Move the paddle to the center of the right screen's edge.
	m_paddle.initialize(wndRect.right, centerY);

	return true;
}

bool Game::shutdown()
{
	// TODO: stub
	return true;
}

bool Game::isEnded() const
{
	return m_gameEnded;
}

#if 0
bool Game::shouldRun() const
{
	return m_shouldRun;
}
#endif

#if 0
void Game::processInput()
{
}
#endif

void Game::updateState()
{
	// Time elapsed since last frame (in seconds)...
	float delta = (GetTickCount64() - m_ticks) / 1000.0f;

	// Clamp maximum delta value.
	if (delta > 0.05f)
	{
		delta = 0.05f;
	}

	m_ball.updatePos(delta, m_paddle.getRect(), m_field.right, m_paddle.getPaddlePosY());

	if (m_ball.isGone())
	{
		m_gameEnded = true;
	}
}

void Game::render(HDC hDc)
{
	for (auto& itr : m_walls)
	{
		itr.draw(hDc);
	}

	m_ball.draw(hDc);

	m_paddle.draw(hDc);
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

	m_field.left = thickness;
	m_field.top = thickness;
	m_field.right = client.right;
	m_field.bottom = client.bottom - thickness;

	m_ball.resizeGameField(m_field);
}

void Game::movePaddle(HWND hWnd, int offset)
{
	m_paddle.updatePos(hWnd, offset, getWallThickness());
}
