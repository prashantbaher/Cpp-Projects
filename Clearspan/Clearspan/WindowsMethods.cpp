#include "ClearspanGUIConstants.h"
#include "ClearspanSolidworksMethods.h"

// Handlers to handle return value by Edit controls
HWND hSelectProfile, hBuildingLength, hRafterSpacing;

// Declaration for checkInputIsValid method
bool checkInputIsValid(char* inputTexts, HWND hWnd, bool status);

// Method for Adding Controls in Clearspan Application
void AddControl (HWND hWnd)
{
	// Label for selecting rafter profile
	CreateWindowW(L"Static", L"Select Profile", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 100, 75, 150, 25, hWnd, NULL, NULL, NULL);

	// Text Box for rafter spacing
	hSelectProfile = CreateWindowW(L"Edit", L"T065RD", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 275, 75, 150, 25, hWnd, NULL, NULL, NULL);

	// Label for entering building length
	CreateWindowW(L"Static", L"Enter Building Length\n(in Inches)", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT | SS_LEFTNOWORDWRAP, 100, 110, 150, 35, hWnd, NULL, NULL, NULL);

	// Text Box for entering building length
	hBuildingLength = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 275, 110, 150, 35, hWnd, NULL, NULL, NULL);

	// Label for entering rafter spacing
	CreateWindowW(L"Static", L"Enter Rafter spacing\n(in Inches)", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT | SS_LEFTNOWORDWRAP, 100, 155, 150, 35, hWnd, NULL, NULL, NULL);

	// Text Box for entering rafter spacing
	hRafterSpacing = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 275, 155, 150, 35, hWnd, NULL, NULL, NULL);

	// Button for Creating Tech Doc Sketch
	CreateWindowW(L"Button", L"Create Building Sketch", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 200, 175, 35, hWnd,(HMENU)CREATE_BUILDING_SKETCH, NULL, NULL);
}

// Method for creating building sketch
void createBuildingSketch(HWND hWnd)
{
	// Declaring variables to hold input texts
	char selectProfileText[25], buildingLengthText[25], rafterSpacingText[25];

	// Getting text of Select Profile Text box
	GetWindowText(hSelectProfile, selectProfileText, 25);

	// Getting text of Building Length Text box
	GetWindowText(hBuildingLength, buildingLengthText, 25);

	// Getting text of Rafter Spacing Text box
	GetWindowText(hRafterSpacing, rafterSpacingText, 25);

	// Checking if input fields are empty or not
	if (strcmp(selectProfileText, "") == 0 | strcmp(buildingLengthText, "") == 0 | strcmp(rafterSpacingText, "") == 0)
	{
		// If empty then show message box 
		MessageBoxW(hWnd, L"You did not enter either Building Length or Rafter spacing!", NULL, MB_OK | MB_ICONERROR);
		return;
	}
	
	// Boolean to check status for false input
	bool inputStatus = true;

	// If inputStatus is true
	if (checkInputIsValid(buildingLengthText, hWnd, inputStatus))
	{
		// Checking if rafter spacing is given in numbers or not
		if (checkInputIsValid(rafterSpacingText, hWnd, inputStatus))
		{
			// Call Solidworks Method
			RunSolidworks();
		}
	}
}

// Method to check if input text is a digit or not
// If not then show message and stop the application
bool checkInputIsValid(char* inputTexts, HWND hWnd, bool status)
{
	// variable for counting digits
	int digit = 0, i;

	// Looping through each char
	for (i = 0; inputTexts[i] != '\0'; i++)
	{
		// If input digit is not numeric then show error
		if (!isdigit(inputTexts[i]))
		{
			MessageBoxW(hWnd, L"Please Enter Only Numbers in Building Length and Rafter Spacing!", NULL, MB_OK | MB_ICONERROR);
			
			// Set status of input to false, so that application don't go further
			return status = false;
		}
			
	}
}