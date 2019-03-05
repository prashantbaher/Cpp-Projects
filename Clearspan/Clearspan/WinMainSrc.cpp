#include "ClearspanGUIConstants.h"
#include "ClearspanSolidworksMethods.h"

// Declaration for mainWindowProcedure
LRESULT CALLBACK mainWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Declaration for AddControl Method
void AddControl(HWND hWnd);

// Declaration for createBuildingSketch Method
void createBuildingSketch(HWND hWnd);

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

	// Registering the class by reference
	// If failed then return -1
	if (!RegisterClassW(&mainWindowClass))
		return -1;

	// Creating main window for Clearspan Application
	CreateWindowW(L"ClearspanWindowClass", L"Clearspan Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

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
	
	// Handling Window closing case
	case WM_CREATE:
		// Calling AddControl method
		AddControl(hwnd);
		break;

	// Handling Window different commands
	case WM_COMMAND:

		// Handling different parameters send by the Clearspan Application
		switch (wParam)
		{

		// Handling case when create building sketch button is clicked
		case CREATE_BUILDING_SKETCH:
			// Calling createBuildingSketch method
			createBuildingSketch(hwnd);
			break;
		}

		break;

	// Handling all other un-handle cases
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		break;
	}
}