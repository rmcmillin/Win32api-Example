
#include <windows.h>
#include "Resource.h"
//#include <Wingdi.h>
//#include <commctrl.h>
#include <math.h>
#include "controlDialogs.h"
#include "log.h"

LRESULT CALLBACK getNumberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {	
	static int numberOfDigits;	
	static int decimalPressed;
	static int returnValue;
	static struct DialogInfo *info;	

	char buffer[30];
	switch (Message) {
	case WM_INITDIALOG: {		
		if (lParam) {
			info = (struct DialogInfo *)lParam;
			SetDlgItemText(hwnd, IDC_SUB_TITLE, info->subTitle);	
			sprintf(buffer, "Min: %d", info->min);
			SetDlgItemText(hwnd, IDC_MIN_VALUE, buffer);
			sprintf(buffer, "Max: %d", info->max);
			SetDlgItemText(hwnd, IDC_MAX_VALUE, buffer);
			//add min max strings
		}
		else {
			EndDialog(hwnd, ID_LPARAM_EMPTY);			
		}

		returnValue = 0;
		numberOfDigits = 0;
		decimalPressed = FALSE;		

		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_NUM_1: {
			returnValue = returnValue * 10 + 1;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_2: {
			returnValue = returnValue * 10 + 2;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_3: {
			returnValue = returnValue * 10 + 3;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_4: {
			returnValue = returnValue * 10 + 4;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_5: {
			returnValue = returnValue * 10 + 5;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_6: {
			returnValue = returnValue * 10 + 6;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_7: {
			returnValue = returnValue * 10 + 7;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_8: {
			returnValue = returnValue * 10 + 8;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_9: {
			returnValue = returnValue * 10 + 9;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_0: {
			returnValue = returnValue * 10 + 0;
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_DECIMAL: {
			returnValue = returnValue * -1;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDC_NUM_CLR: {
			returnValue = 0;
			numberOfDigits = 0;
			decimalPressed = FALSE;
			SetDlgItemText(hwnd, ID_VALUE, itoa(returnValue, buffer, 10));
			break;
		}
		case IDOK:
			GetDlgItemText(hwnd, ID_VALUE, buffer, 10);
			info->returnValue = atoi(buffer);			
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK enable_or_disable_DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	char buffer[10];
	HFONT buttonFont;
	switch (Message) {
	case WM_INITDIALOG: {

		buttonFont = CreateFont(36, 0, 0, 0, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, "Calibri");		

		HWND cancel_button = GetDlgItem(hwnd, IDCANCEL);
		HWND enable_button = GetDlgItem(hwnd, IDB_ENABLE);
		HWND disable_button = GetDlgItem(hwnd, IDB_DISABLE);

		SendMessage(cancel_button, WM_SETFONT, (WPARAM)buttonFont, 0);
		SendMessage(enable_button, WM_SETFONT, (WPARAM)buttonFont, 0);
		SendMessage(disable_button, WM_SETFONT, (WPARAM)buttonFont, 0);
		
		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDB_ENABLE: {
			//DeleteObject(buttonFont);
			EndDialog(hwnd, IDB_ENABLE);
			break;
		}
		case IDB_DISABLE: {
			//DeleteObject(buttonFont);
			EndDialog(hwnd, IDB_DISABLE);
			break;
		}				
		case IDCANCEL:
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



BOOL CALLBACK getFloatDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static int numberOfDigits;
	static float value;
	static int decimalPressed;
	char buffer[10];
	switch (Message) {
	case WM_INITDIALOG: {
		value = 0;
		//dispenseRate = spump_getDispenseRate();
		numberOfDigits = 0;
		decimalPressed = FALSE;
		//how to right align?
		//GetDlgItem(hwnd, ID_SP_DISPENSE_RATE)
		//HDC htextbox = GetDC(ID_SP_DISPENSE_RATE);		
		//SetTextAlign(htextbox, TA_RIGHT);
		SetDlgItemText(hwnd, ID_FLOAT_VALUE, itoa(value, buffer, 10));

		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_NUM_1: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 1;
			}
			else {
				value = value + 1 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 1);
			break;
		}
		case IDC_NUM_2: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 2;
			}
			else {
				value = value + 2 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 2);
			break;
		}
		case IDC_NUM_3: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 3;
			}
			else {
				value = value + 3 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 3);
			break;
		}
		case IDC_NUM_4: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 4;
			}
			else {
				value = value + 4 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 4);
			break;
		}
		case IDC_NUM_5: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 5;
			}
			else {
				value = value + 5 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 5);
			break;
		}
		case IDC_NUM_6: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 6;
			}
			else {
				value = value + 6 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 6);
			break;
		}
		case IDC_NUM_7: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 7;
			}
			else {
				value = value + 7 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 7);
			break;
		}
		case IDC_NUM_8: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 8;
			}
			else {
				value = value + 8 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 8);
			break;
		}
		case IDC_NUM_9: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 9;
			}
			else {
				value = value + 9 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 9);
			break;
		}
		case IDC_NUM_0: {
			if (decimalPressed == FALSE) {
				value = value * 10 + 0;
			}
			else {
				value = value + 0 * pow(10, numberOfDigits * -1);
			}
			numberOfDigits += 1;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, gcvt(value, 5, buffer));
			//SetDlgItemText(hwnd, ID_SP_DISPENSE_RATE, itoa(dispenseRate, buffer, 10));
			//calculateDispenseRate(hwnd, &dispenseRate, &numberOfDigits, 0);
			break;
		}
		case IDC_NUM_DECIMAL: {
			decimalPressed = TRUE;
			numberOfDigits = 1;
			break;
		}
		case IDC_NUM_CLR: {
			value = 0;
			numberOfDigits = 0;
			decimalPressed = FALSE;
			SetDlgItemText(hwnd, ID_FLOAT_VALUE, itoa(value, buffer, 10));
			break;
		}
		case IDOK:
			char buffer[7];
			//get textbox values, check bounds and store
			GetDlgItemText(hwnd, ID_FLOAT_VALUE, buffer, 7);
			value = atof(buffer);
			//if (spump_setDispenseRate(value) < 0) {
				//MessageBox(hwnd, "Parameter out of bounds", "Error", MB_OK | MB_ICONINFORMATION);
			//}
			EndDialog(hwnd, value * 100);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

//Dialog from Menu->About.
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}