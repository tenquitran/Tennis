#pragma once

#include "Game.h"


namespace TennisApp
{
	class MainWindow
	{
	public:
		MainWindow(HINSTANCE hInstance, int nCmdShow, int width, int height);

		bool initialize();

		int runLoop();

	private:
		void cleanup();

		ATOM registerClass(HINSTANCE hInstance);

		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static INT_PTR CALLBACK aboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

		// Paint with double-buffering.
		void paint(HWND hWnd, HDC hDc);

	private:
		HINSTANCE m_hInstance = nullptr;

		int m_cmdShow = {};

		int m_width = {};

		int m_height = {};

		HWND m_hWnd = nullptr;

		HBRUSH m_oldBrush = nullptr;

		HBRUSH m_backgroundBrush = nullptr;

		Game m_game;
	};
}
