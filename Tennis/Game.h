#pragma once

#include "Wall.h"
#include "Ball.h"
#include "Paddle.h"


namespace TennisApp
{
	class Game
	{
	public:
		Game();

		virtual ~Game();

		bool initialize(HWND hWnd);

		bool shutdown();

		bool isEnded() const;

		void updateState();

		void render(HDC hDc);

		int getWallThickness() const;

		void resize(HWND hWnd);

		void movePaddle(HWND hWnd, int offset);

		int getBallsMissed() const;

	private:
		std::vector<Wall> m_walls;

		// Game field rectangle.
		RECT m_field = {};

		Ball m_ball;

		Paddle m_paddle;

		// Number of ticks since the game start.
		ULONGLONG m_ticks = {};

		// true if the game is ended.
		bool m_gameEnded = { false };

		int m_ballsMissed = {};
	};
}
