#define DISABLED	0
#define ENABLED		1

#include <windows.h>
#include <Wingdi.h>
#include <commctrl.h>

#include "controlDialogs.h"
#include "Resource.h"
#include "log.h"
#include "mainwindow.h"
#include "motor.h"


//#pragma comment(lib,"user32.lib") // use /link user32.lib in compile

const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND hWndIPAddressFld;
	static HWND hwndEdit;
	HDC         hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC  tm;
	HFONT hFont_title;
	HFONT hFont_normal;


	switch (msg) {
	case WM_PAINT: {
		//redraw the screen with new values after invalidate is called
		mainWindowPaint(hwnd);
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		case ID_FILE_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case ID_ABOUT_HELP: {
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
			if (ret == IDOK) {
				//MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);               
			}
			else if (ret == IDCANCEL) {
				// MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
			}
			else if (ret == -1) {
				MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			}
			break;
		}
		case MAIN_BUTTON_MOTOR_CONTROL: {
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MOTOR_CONTROL), hwnd, mControlDlgProc);
			if (ret == IDOK) {
				//InvalidateRect(hwnd, NULL, TRUE); //invalidate entire screen
				//log_info("New Motor Settings");
			}
			else if (ret == IDCANCEL) {
				//log_info("Motor Settings Cancelled");
			}
			else if (ret == -1) {
				MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			}
			break;
		}
		case MAIN_BUTTON_MOTOR_ON: {
			motor_setState(hwnd, MOTOR_ON);
			break;
		}
		case MAIN_BUTTON_MOTOR_OFF: {
			motor_setState(hwnd, MOTOR_OFF);
			break;
		}
		}
		break; //end WM_COMMAND
	}
	case WM_CREATE: {
		//draw starting screen here, redraw in WM_PAINT
		HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		//start 100ms timer
		SetTimer(hwnd, IDT_TIMER1, 100, (TIMERPROC)NULL);
		//draw the main screen buttons
		drawMainWindow(hwnd, hInstance);
		//draw the status bar on bottom
		drawStatusBar(hwnd);
		break;
	}
	case WM_TIMER:
		switch (wParam) {
			case IDT_TIMER1: {
				//run fake motor control
				motor_run(hwnd);		
				RECT rect;
				rect.left = 260;
				rect.top = 200;
				rect.right = 460;
				rect.bottom = 240;
				InvalidateRect(hwnd, &rect, TRUE);
				
				rect.left = 520;
				rect.top = 200;
				rect.right = 720;
				rect.bottom = 240;
				InvalidateRect(hwnd, &rect, TRUE);
				break;
			}
		}
		break;
	case WM_CLOSE:
		log_trace("Program closed");
		//saveSettings();
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		log_trace("Program exit");
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(CTLCOLOR_DLG + 1); //originally COLOR_WINDOW - white
	//wc.lpszMenuName = NULL;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
	wc.lpszClassName = g_szClassName;
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Electrospinner",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 400,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//Init struct here or set state machine starting state here
	

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//log startup
	log_info("Program Started");

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0) { // GetMessage() blocks until there is a message
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}