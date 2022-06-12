#include <Windows.h>
#include "Resource.h"

#include "motor.h"
#include "controlDialogs.h"
#include "log.h"

static struct MotorSettings {
	motorState_t motorState;
	unsigned int motorRPM;
	volatile unsigned int motorRPMSetPoint;
	unsigned int manifoldDistance;
	volatile unsigned int manifoldDistanceSetPoint;
}motorSettings;

void motor_run(HWND hwnd) {
	if (motorSettings.motorState == MOTOR_ON) {		
		if (motorSettings.motorRPM < motorSettings.motorRPMSetPoint) {				
			motorSettings.motorRPM++;
			motor_setRPM(hwnd, motorSettings.motorRPM);
		}
		else if (motorSettings.motorRPM > motorSettings.motorRPMSetPoint) {						
			motorSettings.motorRPM--;
			motor_setRPM(hwnd, motorSettings.motorRPM);
		}		
		if (motorSettings.manifoldDistance < motorSettings.manifoldDistanceSetPoint) {						
			motorSettings.manifoldDistance++;
			motor_setManifoldDistance(hwnd, motorSettings.manifoldDistance);
		}
		else if (motorSettings.manifoldDistance > motorSettings.manifoldDistanceSetPoint) {			
			motorSettings.manifoldDistance--;
			motor_setManifoldDistance(hwnd, motorSettings.manifoldDistance);
		}
	}
	else {
		//not on, do nothing		
	}
}

motorState_t motor_getState() {
	return motorSettings.motorState;
}

unsigned int motor_getRPM() {
	return motorSettings.motorRPM;
}

unsigned int motor_getRPMSetPoint() {
	return motorSettings.motorRPMSetPoint;
}

unsigned int motor_getManifoldDistance() {
	return motorSettings.manifoldDistance;
}

unsigned int motor_getManifoldDistanceSetPoint() {
	return motorSettings.manifoldDistanceSetPoint;
}

int motor_setState(HWND hwnd, motorState_t state) {
	if (state == MOTOR_ON || state == MOTOR_OFF) {
		motorSettings.motorState = state;
		//invalidate area so it can be redrawn on next WM_PAINT
		RECT rect;
		rect.left = 750;
		rect.top = 200;
		rect.right = 890;
		rect.bottom = 230;
		InvalidateRect(hwnd, &rect, TRUE);
		return 0;
	}
	return -1;
}

int motor_setRPM(HWND hwnd, unsigned int rpm) {
	if (rpm >= RPM_MIN && rpm <= RPM_MAX) {
		motorSettings.motorRPM = rpm;
		RECT rect;
		rect.left = 260;
		rect.top = 80;
		rect.right = 460;
		rect.bottom = 180;
		InvalidateRect(hwnd, &rect, TRUE);
		return 0;
	}
	return -1;
}

int motor_setRPMSetPoint(HWND hwnd, unsigned int setPoint) {
	if (setPoint >= RPM_MIN && setPoint <= RPM_MAX) {
		motorSettings.motorRPMSetPoint = setPoint;
		RECT rect;		
		rect.left = 260;
		rect.top = 200;
		rect.right = 460;
		rect.bottom = 240;
		InvalidateRect(hwnd, &rect, TRUE);
		return 0;
	}
	return -1;
}

int motor_setManifoldDistance(HWND hwnd, unsigned int distance) {
	if (distance >= DISTANCE_MIN && distance <= DISTANCE_MAX) {
		motorSettings.manifoldDistance = distance;
		RECT rect;
		rect.left = 520;
		rect.top = 80;
		rect.right = 720;
		rect.bottom = 180;
		InvalidateRect(hwnd, &rect, TRUE);
		return 0;
	}
	return -1;
}

int motor_setManifoldDistanceSetPoint(HWND hwnd, unsigned int setPoint) {
	if (setPoint >= DISTANCE_MIN && setPoint <= DISTANCE_MAX) {
		motorSettings.manifoldDistanceSetPoint = setPoint;
		RECT rect;		
		rect.left = 520;
		rect.top = 200;
		rect.right = 720;
		rect.bottom = 240;
		InvalidateRect(hwnd, &rect, TRUE);
		return 0;
	}
	return -1;
}



BOOL CALLBACK mControlDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HFONT buttonFont;

	switch (Message) {
	case WM_INITDIALOG: {

		buttonFont = CreateFont(36, 0, 0, 0, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, "Calibri");

		//Set Font for Buttons
		HWND ok_button = GetDlgItem(hwnd, IDOK);
		SendMessage(ok_button, WM_SETFONT, (WPARAM)buttonFont, 0);

		HWND cancel_button = GetDlgItem(hwnd, IDCANCEL);
		SendMessage(cancel_button, WM_SETFONT, (WPARAM)buttonFont, 0);

		HWND mControl_rpm = GetDlgItem(hwnd, IDB_MCONTROL_RPM);
		SendMessage(mControl_rpm, WM_SETFONT, (WPARAM)buttonFont, 0);

		HWND mControl_distance = GetDlgItem(hwnd, IDB_MCONTROL_DISTANCE);
		SendMessage(mControl_distance, WM_SETFONT, (WPARAM)buttonFont, 0);

		//Set Font for Edit Text			
		HWND mControl_rpmText = GetDlgItem(hwnd, ID_MCONTROL_RPM);
		SendMessage(mControl_rpmText, WM_SETFONT, (WPARAM)buttonFont, 0);

		HWND mControl_distanceText = GetDlgItem(hwnd, ID_MCONTROL_DISTANCE);
		SendMessage(mControl_distanceText, WM_SETFONT, (WPARAM)buttonFont, 0);

		//Units
		HWND mControl_rpmUnits = GetDlgItem(hwnd, IDT_RPM);
		SendMessage(mControl_rpmUnits, WM_SETFONT, (WPARAM)buttonFont, 0);

		HWND mControl_distanceUnits = GetDlgItem(hwnd, IDT_DISTANCE);
		SendMessage(mControl_distanceUnits, WM_SETFONT, (WPARAM)buttonFont, 0);

		//Fill Edit Text Boxes with Current Values
		unsigned char buffer[100];

		SetDlgItemText(hwnd, ID_MCONTROL_RPM, itoa(motor_getRPMSetPoint(), buffer, 10));
		SetDlgItemText(hwnd, ID_MCONTROL_DISTANCE, itoa(motor_getManifoldDistanceSetPoint(), buffer, 10));

		/*
		//DISABLE or ENABLE BUTTONS
		if (motor_getState() == MOTOR_OFF) {
			EnableWindow(GetDlgItem(hwnd, IDB_MCONTROL_RPM), TRUE);
			EnableWindow(GetDlgItem(hwnd, IDB_MCONTROL_DISTANCE), TRUE);
		}
		else {
			EnableWindow(GetDlgItem(hwnd, IDB_MCONTROL_RPM), FALSE);
			EnableWindow(GetDlgItem(hwnd, IDB_MCONTROL_DISTANCE), FALSE);
		}
		*/

		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDB_MCONTROL_RPM: {
			struct DialogInfo info;			
			strcpy(info.subTitle, "RPM Set Point");		
			info.max = RPM_MAX;
			info.min = RPM_MIN;
			char buffer[10];
			int ret = DialogBoxParamA(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_GET_NUMBER), hwnd, getNumberDlgProc, (LPARAM)&info);			
			if (ret == IDOK) {				
				SetDlgItemText(hwnd, ID_MCONTROL_RPM, itoa(info.returnValue, buffer, 10));
			}
			else if (ret == IDCANCEL) {

			}
			else if (ret == ID_LPARAM_EMPTY) {
				MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			}
			else if (ret == -1) {
				MessageBox(hwnd, "Dialog failed!", "Error",MB_OK | MB_ICONINFORMATION);
			}
			break;			
		}
		case IDB_MCONTROL_DISTANCE: {
			struct DialogInfo info;
			strcpy(info.subTitle, "Distance Set Point");
			info.max = DISTANCE_MAX;
			info.min = DISTANCE_MIN;
			char buffer[10];
			int ret = DialogBoxParamA(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_GET_NUMBER), hwnd, getNumberDlgProc, (LPARAM)&info);
			if (ret == IDOK) {				
				SetDlgItemText(hwnd, ID_MCONTROL_DISTANCE, itoa(info.returnValue, buffer, 10));
			}
			else if (ret == IDCANCEL) {

			}
			else if (ret == ID_LPARAM_EMPTY) {
				MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			}
			else if (ret == -1) {
				MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			}
			break;
		}

		case IDOK: {
			char buffer[10];			
			GetDlgItemText(hwnd, ID_MCONTROL_RPM, buffer, 10);
			motor_setRPMSetPoint(hwnd, atoi(buffer));
			GetDlgItemText(hwnd, ID_MCONTROL_DISTANCE, buffer, 10);
			motor_setManifoldDistanceSetPoint(hwnd, atoi(buffer));

			InvalidateRect(hwnd, NULL, TRUE); //redraw
			//DeleteObject(buttonFont);
			EndDialog(hwnd, IDOK);
			break;
		}
		case IDCANCEL:
			InvalidateRect(hwnd, NULL, TRUE); //redraw
			//DeleteObject(buttonFont);
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}