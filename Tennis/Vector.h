#pragma once


namespace TennisApp
{
	struct Vector2Int
	{
	public:
		Vector2Int() = default;

		Vector2Int(int x, int y)
			: m_x(x), m_y(y)
		{
		}

	public:
		int m_x = {};
		int m_y = {};
	};


	struct Vector2Float
	{
	public:
		Vector2Float() = default;

		Vector2Float(float x, float y)
			: m_x(x), m_y(y)
		{
		}

	public:
		float m_x = {};
		float m_y = {};
	};
}
