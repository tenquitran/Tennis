#pragma once

#include "Wall.h"
#include "Ball.h"


namespace TennisApp
{
	class Game
	{
	public:
		Game();

		virtual ~Game();

		bool initialize(HWND hWnd);

		bool shutdown();

#if 0
		bool shouldRun() const;
#endif

		void processInput();

		void updateState();

		void render(HDC hDc);

		int getWallThickness() const;

		void resize(HWND hWnd);

	private:
#if 0
		bool m_shouldRun = { true };
#endif

		std::vector<Wall> m_walls;

		Ball m_ball;

		// Number of ticks since the game start.
		ULONGLONG m_ticks = {};
	};
}
