#include <Windows.h>
#include <Wingdi.h>
#include <commctrl.h>
#include "Resource.h"
#include "log.h"
#include "font.h"

#include "motor.h"

#define DISABLED	0
#define ENABLED		1

//update screen with new values

void mainWindowPaint(HWND hwnd) {
	HDC         hdc;
	//int         i;
	PAINTSTRUCT ps;
	//TCHAR       szBuffer [10];
	TEXTMETRIC  tm;
	HFONT hFont_title;
	HFONT hFont_normal;

	hdc = BeginPaint(hwnd, &ps);
	hFont_title = CreateFont(24, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, 0, 0, 0, 2, 0, "Calibri");
	hFont_normal = CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, "Calibri");
	HFONT hf = CreateFont(30, 0, 0, 0, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, "Calibri");
	HFONT value = CreateFont(80, 0, 0, 0, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, "Calibri");
	SetTextColor(hdc, BLACK);
	SetBkColor(hdc, GREY);
	//SelectObject(hdc, hFont_normal);	
	//SelectObject(hdc, hFont_title);

	HFONT hfOld = SelectObject(hdc, hf);
	SelectObject(hdc, hf);
	


	char text[100];
	int charCount;
	/////////////////
	//MOTOR CONTROL//
	/////////////////
	SetTextColor(hdc, BLACK);
	SetBkColor(hdc, GREY);

	//Rectangle
	Rectangle(hdc, 260, 80, 460, 180); //RPM
	Rectangle(hdc, 520, 80, 720, 180); //Distance

	//debug SP redraw box
	//Rectangle(hdc, 260, 200, 460, 240);
	//Rectangle(hdc, 520, 200, 720, 240);
	

	//Rectangle Label
	charCount = sprintf(text, "Drum (RPM)");
	TextOut(hdc, 260, 35, text, charCount);

	charCount = sprintf(text, "Distance (mm)");
	TextOut(hdc, 520, 35, text, charCount);

	//Set Point Text
	charCount = sprintf(text, "SP: %d RPM", motor_getRPMSetPoint()); //add function to get rpm SP
	TextOut(hdc, 260, 200, text, charCount);

	charCount = sprintf(text, "SP: %d mm", motor_getManifoldDistanceSetPoint()); //add function to get distance SP
	TextOut(hdc, 520, 200, text, charCount);

	charCount = sprintf(text, "%s", motorStateStrings[motor_getState()]);
	SetTextColor(hdc, motorStateColour[motor_getState()]);
	TextOut(hdc, 750, 200, text, charCount);

	//values for white rectangle
	SetTextColor(hdc, BLACK);
	SetBkColor(hdc, WHITE);
	SetTextAlign(hdc, TA_RIGHT);
	SelectObject(hdc, value);

	charCount = sprintf(text, "%d", motor_getRPM());
	TextOut(hdc, 450, 90, text, charCount);

	charCount = sprintf(text, "%d", motor_getManifoldDistance()); 
	TextOut(hdc, 710, 90, text, charCount);


	SelectObject(hdc, GetStockObject(BLACK_PEN));

	DeleteObject(hFont_normal);
	DeleteObject(hFont_title);
	DeleteObject(hf);
	DeleteObject(value);

	EndPaint(hwnd, &ps);
}

void drawMainWindow(HWND hwnd, HINSTANCE hInstance) {
	
	//Group Border
	CreateWindow("BUTTON", "Motor Control", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 15, 15, 970, 230, hwnd, (HMENU)IDGB_MECHANICAL_CONTROL, hInstance, NULL);
	
	HFONT buttonFont = CreateFont(36, 0, 0, 0, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, "Calibri");		
	
	//Motor Control
	HWND mControl = CreateWindowEx(0, "BUTTON", "Motor Control", WS_VISIBLE | WS_CHILD | BS_MULTILINE, 30, 80, 170, 100, hwnd, (HMENU)MAIN_BUTTON_MOTOR_CONTROL, hInstance, NULL);
	SendMessage(mControl, WM_SETFONT, (WPARAM)buttonFont, 0);
	HWND mOn = CreateWindowEx(0, "BUTTON", "On", WS_VISIBLE | WS_CHILD | BS_MULTILINE, 750, 80, 100, 100, hwnd, (HMENU)MAIN_BUTTON_MOTOR_ON, hInstance, NULL);
	SendMessage(mOn, WM_SETFONT, (WPARAM)buttonFont, 0);
	HWND mOff = CreateWindowEx(0, "BUTTON", "Off", WS_VISIBLE | WS_CHILD | BS_MULTILINE, 860, 80, 100, 100, hwnd, (HMENU)MAIN_BUTTON_MOTOR_OFF, hInstance, NULL);
	SendMessage(mOff, WM_SETFONT, (WPARAM)buttonFont, 0);

}

void drawStatusBar(HWND hwnd) {

	//return handle to status bar so SendMessage can be sent from program

	InitCommonControls();	
	HWND hStatus;
	hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, 
		hwnd, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);
	int statwidths[] = {75, 150, 300, 450, -1 };

	SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths) / sizeof(int), (LPARAM)statwidths);
	
	SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"0°C");
	SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)"0%RH");
	SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)"HVPSU: Disconnected");
	SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)"SPUMP: Disconnected");		
	SendMessage(hStatus, SB_SETTEXT, 4, (LPARAM)"MCTRL: Disconnected");
	
}