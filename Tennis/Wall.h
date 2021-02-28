#pragma once

#include "WallType.h"


namespace TennisApp
{
	class Wall
	{
	public:
		explicit Wall(EWallType type);

		void draw(HDC hDc);

		int getThickness() const;

		// Resize the wall according to the window's client size.
		void resize(RECT client);

	private:
		EWallType m_type = { EWallType::Unknown };

		RECT m_rect = {};

		const int Thickness = 25;
	};
}
