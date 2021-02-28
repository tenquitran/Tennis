#pragma once


namespace TennisApp
{
	struct Vector2
	{
	public:
		Vector2() = default;

		Vector2(int x, int y)
			: m_x(x), m_y(y)
		{
		}

	public:
		int m_x = {};
		int m_y = {};
	};
}
