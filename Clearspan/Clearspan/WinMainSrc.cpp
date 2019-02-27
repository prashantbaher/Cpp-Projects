#include <Windows.h>

// Declaration for mainWindowProcedure
LRESULT CALLBACK mainWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Entry point for Clearspan Application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR args, int cmdShow)
{
	// Creating Main Window class for Clearspan Application
	WNDCLASSW mainWindowClass = { 0 };

	// Setting Background of Clearspan Application
	mainWindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	// Setting Cursor of Clearspan Application
	mainWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// Setting HINSTANCE of Clearspan Application
	mainWindowClass.hInstance = hInstance;

	// Setting class name for identifying Main window class
	mainWindowClass.lpszClassName = L"ClearspanWindowClass";

	// Setting Windows Procedure for main window class
	mainWindowClass.lpfnWndProc = mainWindowProcedure;



	// Creating Message Structure
	MSG windowMsg = { 0 };

	// Message loop for Clearspan Application to show on screen
	// It runs until we close the window or give exit command
	while (GetMessage(&windowMsg, NULL, NULL, NULL))
	{
		// Translating the message
		TranslateMessage(&windowMsg);

		// Dispatching the message to main window procedure
		DispatchMessage(&windowMsg);
	}
}

// Creating Window Procedure for Main window class
LRESULT CALLBACK mainWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Handling different message send by the Clearspan Application
	switch (uMsg)
	{
	// Handling Window closing case
	case WM_DESTROY:
		// Return value 0, so that our message get stopped
		PostQuitMessage(0);
		break;
	// Handling all other un-handle cases
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		break;
	}
}