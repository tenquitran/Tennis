#include "framework.h"
#include "resource.h"
#include "MainWindow.h"

///////////////////////////////////////////////////////////////////////////////

#define MAX_LOADSTRING 100

WCHAR szWindowClass[MAX_LOADSTRING];    // the main window class name
WCHAR szTitle[MAX_LOADSTRING];          // the title bar text

#define IDT_GAME_TIMER   2009

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow, int width, int height)
	: m_hInstance(hInstance), m_cmdShow(nCmdShow), 
	  m_width(width), m_height(height)
{
}

bool MainWindow::initialize()
{
	LoadStringW(m_hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(m_hInstance, IDC_TENNIS, szWindowClass, MAX_LOADSTRING);

	registerClass(m_hInstance);

	m_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, m_width, m_height, nullptr, nullptr, m_hInstance, this);

	if (!m_hWnd)
	{
		std::cerr << "CreateWindowW() failed: " << ::GetLastError() << std::endl;
		ATLASSERT(FALSE); return false;
	}

	if (!SetTimer(m_hWnd, IDT_GAME_TIMER, 25, (TIMERPROC)nullptr))
	{
		std::cerr << "SetTimer() failed: " << ::GetLastError() << std::endl;
		ATLASSERT(FALSE); return false;
	}

	if (!m_game.initialize(m_hWnd))
	{
		std::wcerr << "Failed to initialize the game object\n";
		ATLASSERT(FALSE); return false;
	}

	m_backgroundBrush = CreateSolidBrush(RGB(0, 128, 64));

	if (!m_backgroundBrush)
	{
		std::cerr << "CreateSolidBrush() failed\n";
		ATLASSERT(FALSE); return false;
	}

	HDC hDc = GetDC(m_hWnd);
	if (!hDc)
	{
		std::cerr << __FUNCTION__ << "GetDC() failed\n";
		ATLASSERT(FALSE); return false;
	}

	m_oldBrush = (HBRUSH)SelectObject(hDc, m_backgroundBrush);

	ShowWindow(m_hWnd, m_cmdShow);
	UpdateWindow(m_hWnd);

	return true;
}

void MainWindow::cleanup()
{
	if (!m_game.shutdown())
	{
		std::wcerr << "Failed to shut down the game object\n";
		ATLASSERT(FALSE);
	}

	if (!KillTimer(m_hWnd, IDT_GAME_TIMER))
	{
		std::cerr << "KillTimer() failed: " << ::GetLastError() << std::endl;
		ATLASSERT(FALSE);
	}

	HDC hDc = GetDC(m_hWnd);

	if (!hDc)
	{
		std::cerr << __FUNCTION__ << "GetDC() failed\n";
		ATLASSERT(FALSE); return;
	}
	else
	{
		SelectObject(hDc, m_oldBrush);

		DeleteObject(m_backgroundBrush);
	}
}

ATOM MainWindow::registerClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TENNIS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TENNIS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

#if 0
void MainWindow::clearBackground(HDC hDc)
{
	RECT rect = {};

	if (GetClientRect(m_hWnd, &rect))
	{
		FillRect(hDc, &rect, m_backgroundBrush);
	}
}
#endif

int MainWindow::runLoop()
{
	HDC hDc = GetDC(m_hWnd);

	if (!hDc)
	{
		std::cerr << __FUNCTION__ << "GetDC() failed\n";
		ATLASSERT(FALSE); return 1;
	}

	MSG msg = {};

	while (WM_QUIT != msg.message
		/*&& game.shouldRun() */
		)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_game.processInput();

		//game.updateState();

		//game.render(m_hWnd, hDc);
	}

	return 0;
}

void MainWindow::paint(HWND hWnd, HDC hDc)
{
	RECT client = {};

	if (!GetClientRect(hWnd, &client))
	{
		ATLASSERT(FALSE); return;
	}

	// Create a compatible DC.

	HDC hdcMem = CreateCompatibleDC(hDc);

	if (!hdcMem)
	{
		ATLASSERT(FALSE); return;
	}

	// Create a bitmap large enough for our client rectangle.

	HBITMAP hbmMem = CreateCompatibleBitmap(hDc,
		client.right - client.left,
		client.bottom - client.top);

	if (!hbmMem)
	{
		ATLASSERT(FALSE); return;
	}

	// Select the bitmap into the off-screen DC.
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

	// Erase the background.
	if (0 == FillRect(hdcMem, &client, m_backgroundBrush))
	{
		ATLASSERT(FALSE); return;
	}

	m_game.render(hdcMem);

	// Blt the changes to the screen DC.
	if (!BitBlt(hDc,
		client.left, client.top, client.right - client.left, client.bottom - client.top,
		hdcMem, 0, 0, SRCCOPY))
	{
		// DWORD err = GetLastError();    // don't clutter the log
		ATLASSERT(FALSE); return;
	}

	// Cleanup.
	
	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);

	if (!DeleteDC(hdcMem))
	{
		ATLASSERT(FALSE);
	}
}

LRESULT MainWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static MainWindow* pWnd = nullptr;

	switch (message)
	{
	case WM_CREATE:
		pWnd = (MainWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		ATLASSERT(pWnd);
		break;
	case WM_DESTROY:
		pWnd->cleanup();

		PostQuitMessage(0);
		break;
	case WM_SIZE:
		{
			//UINT width  = LOWORD(lParam);
			//UINT height = HIWORD(lParam);

			pWnd->m_game.resize(hWnd);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDc = BeginPaint(hWnd, &ps);
			
			//pWnd->clearBackground(hDc);

			pWnd->paint(hWnd, hDc);
			//pWnd->game.render(hWnd, hDc);

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_ERASEBKGND:
		return (LRESULT)1;    // for double buffering
	case WM_TIMER:
		{
			pWnd->m_game.updateState();

#if 1
			InvalidateRect(hWnd, nullptr, TRUE);
#else
			// Update the client area minus walls.

			RECT client = {};

			if (!GetClientRect(hWnd, &client))
			{
				ATLASSERT(FALSE);
			}
			else
			{
				const int wallThickness = pWnd->game.getWallThickness();

				// Client area minus the walls.
				// left, top, right, bottom
				RECT rect = { wallThickness, wallThickness, client.right, client.bottom - wallThickness };

				InvalidateRect(hWnd, &rect, TRUE);
			}
#endif
		}
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);

			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(pWnd->m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, aboutDlgProc);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

INT_PTR CALLBACK MainWindow::aboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
