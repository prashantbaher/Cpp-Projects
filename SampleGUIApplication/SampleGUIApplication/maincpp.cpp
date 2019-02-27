#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_MENU_NEW 1			// Constant for New in File menu
#define FILE_MENU_OPEN 2		// Constant for Open in File menu
#define FILE_MENU_EXIT 3		// Constant for Exit in File menu
#define GENERATE_BUTTON 4		// Constant for Generating output
#define OPEN_FILE_BUTTON 5		// Constant for Open File Dialog Box

// #define CHANGE_TITLE 4		// Constand for Exit in File menu

// Window Procedure declaration for main Window class
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Window Procedure declaration for Dialog window class
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Declaration for Registering Dialog Class
void registerDialogClass(HINSTANCE hInstance);

// Declaration for displayDialog method
void displayDialog(HWND hWnd);

// Declaration for open_FileDialog method
void open_FileDialog(HWND hWnd);

// Declaration for diplay_file method
// void diplay_file(char* path);

// Handler for menus in our window
HMENU hMenu;

// Handler for Images in our application
HBITMAP hLogoImage, hGenerateImage;

/*
// Handler to take care for Message return by Edit controls
// NOTE: It is of type "HWND" because controls are Windows but having their own classes.
HWND hEdit;
*/

// Handlers to handle return value by Edit controls
HWND hName, hAge, hOutput, hLogo, hMainWindow;

// Add LoadImages method declaration
void LoadImages();

// Add Menu method declaration
void AddMenu(HWND hwnd);

// Add Control method declaration
void AddControl(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow)
{
	// Variable for our window class
	WNDCLASSW WindowClass = {0};

	// Defining Background of window
	WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	// Defining cursor of window
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// Defining HINSTACE of our window
	WindowClass.hInstance = hInst;

	// Defining class name for identifying this class
	WindowClass.lpszClassName = L"myWindowClass";

	// Assigning window procedure for this window class
	WindowClass.lpfnWndProc = WindowProcedure;

	// Registering class by pointing to Window class
	// If failed then return -1 value
	if (!RegisterClassW(&WindowClass))
		return -1;

	// Calling registerDialogClass method
	registerDialogClass(hInst);

	// Creating window from our Window class and returing HWND to hMainWindow
	hMainWindow = CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	// Message structure
	MSG msg = { 0 };

	// Message loop for our window to show on screen
	// It run until we close the window or give exit command
	while (GetMessage(&msg, NULL, NULL, NULL) )
	{
		// Translating message structure
		TranslateMessage(&msg);

		// Dispatiching message structure to Window procedure
		DispatchMessage(&msg);
	}
}

// Window Procedure function definition
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Integer variable to hold return value after pressing the button
	int MessageReturnValue;

	// Handling different message send by the window
	switch (uMsg)
	{
	case WM_COMMAND:
		// When some button in Menu is clicked then wParam is passed
		switch (wParam)		
		{
		// When we hit "Exit" button
		case FILE_MENU_EXIT:
			// Message to confirm the exit action
			MessageReturnValue = MessageBoxW(hwnd, L"Are you sure?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);
			if (MessageReturnValue == IDYES)
				DestroyWindow(hwnd);		// Distroy the window when exit menu is selected
			// MessageBeep(MB_OK);		// When the File menu is clicked because File menu has the Id of 1
			break;
		/*
		// When we hit "Change Title Button"
		case CHANGE_TITLE:
			wchar_t text[100];			// Text variable of type wchar and had a length of 100 character
			
			// Calling in-build function of GetWindowTextW from Win32 API to get the text value from text box
			GetWindowTextW(hEdit, text, 100);

			// Calling in-build function of SetWindowTextW from Win32 API to set the title of our window to text value
			SetWindowTextW(hwnd, text);	

			break;
		*/

		// When we hit Generate Output button
		case GENERATE_BUTTON:

			// Declaring variable to hold text values from different textboxes
			char nameText[50], ageText[30], outputText[60];

			// Get text value from Name Text box
			GetWindowText(hName, nameText, 50);

			// Get text value from Age Text box
			GetWindowText(hAge, ageText, 30);

			// Checking if input name and age is empty or not
			if (strcmp(nameText,"") == 0 | strcmp(ageText,"") == 0)
			{
				// Inform user for empty text fields
				MessageReturnValue = MessageBoxW(hwnd, L"You did not enter anything!", NULL, MB_ABORTRETRYIGNORE | MB_ICONERROR);

				// Handling 3 different cases
				switch (MessageReturnValue)
				{
				// If user select Abort the action then distroy the window
				case IDABORT:
					DestroyWindow(hwnd);
					break;

				// If user select RETRY the action then do nothing and return 0
				case IDRETRY:
					return 0;

				// If user select Ignore the action then process the calculation
				case IDIGNORE:
					break;
				}
			}

			strcpy_s(outputText, nameText);			// Copying the Name into Output text 
			strcat_s(outputText, " is ");			// Appending "is" to Output text
			strcat_s(outputText, ageText);			// Appending age to Output text
			strcat_s(outputText, " years old.");	// Appending "years old." to Output text

			// Set the output text to Output Text Box
			SetWindowText(hOutput, outputText);
			
			break;

		// When we hit "File" button
		case FILE_MENU_NEW:
			MessageBeep(MB_OK);		// When the New menu is clicked and produced sound
			displayDialog(hwnd);	// Calling displayDialog method when the window is created
			break;

		// Handling case for open file dialog box
		case OPEN_FILE_BUTTON:
			// Call Open_FileDialog method
			open_FileDialog(hwnd);
			break;
		}

		break;

	// When Window has been created
	case WM_CREATE:
		LoadImages();			// Calling LoadImages method when the window is created
		AddMenu(hwnd);			// Calling AddMenu method when the window is created
		AddControl(hwnd);		// Calling AddControl method when the window is created
		break;

	// When Window is closed
	case WM_DESTROY:
		PostQuitMessage(0);		// Return 0 value, so that our message loop get stopped
		break;

	// Handling all other cases
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		break;
	}
}

// Method for add menus in our GUI
void AddMenu(HWND hwnd)
{
	// Create a Menu and assigned it to our HMENU variable
	hMenu = CreateMenu();

	// Create a Sub Menu
	HMENU hFileMenu = CreateMenu();

	// Create another Sub Menu
	HMENU hSubMenu = CreateMenu();

	// Adding "Sub Menu" to "Open SubMenu"
	AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Items");

	// Adding "New" to "File"
	AppendMenu(hFileMenu, MF_STRING,FILE_MENU_NEW, "New");
	// Adding "Open SubMenu" to "File"
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
	// Adding "Separator" to "File"
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	// Adding "Exit" to "File"
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	// Adding the items into Menu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");	// Adding "File" to menu
	AppendMenu(hMenu, MF_STRING, 0, "Help");	// Adding "Help" to menu

	// Setting the menu by adding this menu to our window
	SetMenu(hwnd, hMenu);
}


// Method to add control in our GUI
void AddControl(HWND hwnd)
{
	/*
	// Creating Window for Static controls like "Labels"
	CreateWindowW(L"Static", L"Enter Text Here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 100, 75, 150, 25, hwnd, NULL, NULL, NULL);

	// Creating window for Edit controls like "TextBox" and return the value inside the edit control
	hEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 100, 110, 150, 25, hwnd, NULL, NULL, NULL);

	// Creating Window for Button (Change Title Button)
	CreateWindowW(L"Button", L"Change Title", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 150, 150, 25, hwnd, (HMENU)CHANGE_TITLE, NULL, NULL);
	*/

	// Label for Name
	CreateWindowW(L"Static", L"Name :", WS_VISIBLE | WS_CHILD, 100, 50, 95, 35, hwnd, NULL, NULL, NULL);

	// Text box to hold input Name
	hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 50, 95, 35, hwnd, NULL, NULL, NULL);

	// Label for Age
	CreateWindowW(L"Static", L"Age :", WS_VISIBLE | WS_CHILD, 100, 90, 95, 35, hwnd, NULL, NULL, NULL);

	// Text box to hold input Age
	hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 95, 35, hwnd, NULL, NULL, NULL);

	// Button to Generate Output
	HWND hButton = CreateWindowW(L"Button", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 150, 130, 95, 35, hwnd, (HMENU)GENERATE_BUTTON, NULL, NULL);

	// Sending message to Button to load generate image
	SendMessageW(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hGenerateImage);

	// Text box to hold Generated Output
	hOutput = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hwnd, NULL, NULL, NULL);

	// Static window for creating Logo
	hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hwnd, NULL, NULL, NULL);

	// Sending the message to Logo window handler
	SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);

	// Button for open file dialog box
	CreateWindowW(L"Button", L"Open File", WS_VISIBLE | WS_CHILD, 150, 160, 95, 35, hwnd, (HMENU)OPEN_FILE_BUTTON, NULL, NULL);
}

// Method for Loading images in our application
void LoadImages()
{
	// Load logo image
	hLogoImage = (HBITMAP)LoadImageW(NULL, L"logo.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

	// Load Generate image
	hGenerateImage = (HBITMAP)LoadImageW(NULL, L"generate.bmp", IMAGE_BITMAP, 150, 130, LR_LOADFROMFILE);
}

// Method to register Dialog window
void registerDialogClass(HINSTANCE hInstance)
{
	// Creating Window class for Dialog boxes
	WNDCLASSW dialog = { 0 };

	// Defining background for dialog window
	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;

	// Defining curson for dialog window
	dialog.hCursor = LoadCursor(NULL, IDC_CROSS);

	// Defining the HINSTANCE of our dialog window
	dialog.hInstance = hInstance;

	// Defining the dialog class name for identifying this class
	dialog.lpszClassName = L"myDialogClass";

	// Defining the window procedure for our dialog class
	dialog.lpfnWndProc = DialogProcedure;

	// Registering the Dialog Window class
	RegisterClassW(&dialog);
}

// Window procedure for Dialog class
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Handling the cases for different input messages
	switch (uMsg)
	{
	// Handling the Case for Command
	case WM_COMMAND:
		// Handling the Cases for Different Commands
		switch (wParam)
		{
		case 1:
			// Enabling the mainwindow before destroying the Dialog Window
			EnableWindow(hMainWindow, true);

			// Destroying the Dialog Window
			DestroyWindow(hWnd);
			break;
		}
		break;

	// Destroying the window when close is selected
	case WM_CLOSE:

		// Enabling the mainwindow before destroying the Dialog Window
		EnableWindow(hMainWindow, true);

		// Destroying the Dialog Window
		DestroyWindow(hWnd);

		break;

	// Handling all other case than defined
	default:
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		break;
	}
}

// Method for displaying Dialog Window
void displayDialog(HWND hWnd)
{
	// Creating Dialog Window
	HWND hDialog = CreateWindowW(L"myDialogClass", L"Dialog", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 200, 200, hWnd, NULL, NULL, NULL);

	// Creating Button in Dialog Window
	CreateWindowW(L"Button", L"Close", WS_VISIBLE | WS_CHILD, 20, 20, 50, 25, hDialog, (HMENU)1, NULL, NULL);

	// Disabling the main window when working with Dialog Window
	EnableWindow(hWnd, false);
}

// Method for opening "Open File Dialog Box"
void open_FileDialog(HWND hWnd)
{
	// Create a structure as needed for Creating open file dialog box
	OPENFILENAME openFileName;

	// Initial setting elements of above structure is set to zero 
	ZeroMemory(&openFileName, sizeof(OPENFILENAME));

	// String for holding selected file path
	char file_Name[100];

	// Define size of openFileName structure
	openFileName.lStructSize = sizeof(OPENFILENAME);

	// Define Handle owner of this structure
	openFileName.hwndOwner = hWnd;

	// Getting and storing the path of selected file
	openFileName.lpstrFile = file_Name;

	// Setting initial file name to null other wise program show unexpected behaviour
	openFileName.lpstrFile[0] = '\0';

	// Setting maximum file of path
	openFileName.nMaxFile = 100;

	// Setting filter for our window
	openFileName.lpstrFilter = "All Files\0*.*\0 Source File\0*.cpp\0";

	// Setting default index for filter to All Files
	openFileName.nFilterIndex = 1;

	// Calling Method to Open File Dialog Box
	GetOpenFileName(&openFileName);

	// MessageBoxW(NULL, openFileName.lpstrFile, L"", MB_OK | MB_ICONINFORMATION);

	// Calling Display File Method
	// diplay_file(openFileName.lpstrFile);

}

/*
// Method to display files
void diplay_file(char* path)
{
	// Creating a File type pointer
	FILE *file;

	// Opening the selected file
	// file = fopen(path, "rb");

	// Look for how many characters to read till the end
	// fseek(file, 0, SEEK_END);

	// Getting Size of the file
	int _sizeOfFile = ftell(file);

	// Go to start of the file
	rewind(file);

	// Creating memory for storage of all characters
	char *data = new char[_sizeOfFile + 1];

	// Reading the file
	fread(data, _sizeOfFile, 1, file);

	// Defining the ending character
	data[_sizeOfFile] = '\0';

}
*/