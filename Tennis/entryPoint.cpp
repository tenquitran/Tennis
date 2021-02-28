#include "framework.h"
#include "MainWindow.h"

///////////////////////////////////////////////////////////////////////////////

using namespace TennisApp;

///////////////////////////////////////////////////////////////////////////////


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Redirect std::wcout and std::wcerr output to the log file.
    std::wofstream out("log.txt");
    std::wcout.rdbuf(out.rdbuf());
    std::wcerr.rdbuf(out.rdbuf());

    int wndWidth  = 800;
    int wndHeight = 600;

    MainWindow mainWnd(hInstance, nCmdShow, wndWidth, wndHeight);

    if (!mainWnd.initialize())
    {
        std::wcerr << "Failed to initialize the main window\n";
        return 1;
    }

    return mainWnd.runLoop();
}
