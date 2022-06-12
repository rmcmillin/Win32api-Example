
//struct that can be used to pass to lParam in dialogs
/*
struct DialogInfo *info;
cast as (LPARAM) in function parameter when calling
cast back to DialogInfo inside dialog
*/

struct DialogInfo {
	char title[100];
	char subTitle[100];	
	int min;
	int max;
	int returnValue;
};

//reusable dialogs
LRESULT CALLBACK getNumberDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK enable_or_disable_DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK getFloatDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

//Help Menu Dialog
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);