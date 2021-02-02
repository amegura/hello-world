#include <windows.h>

HWND check;

#define BUTTON_ID1 0
#define HOTWEDNESDAY_1 1


LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_COMMAND:
	    switch(LOWORD(wp)) {
			case BUTTON_ID1:
			        MessageBox(hwnd , TEXT("BUTTON_ID1") , TEXT("kitty") , MB_OK);
					break;
			case HOTWEDNESDAY_1:
			        if(BST_CHECKED == SendMessage(check , BM_GETCHECK , 0 , 0))
		                   SendMessage(check , BM_SETCHECK , BST_UNCHECKED , 0);
		            else
		                   SendMessage(check , BM_SETCHECK , BST_CHECKED , 0);
		            return 0;
			        break;
		}
    }
	return DefWindowProc(hwnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
			PSTR lpCmdLine , int nCmdShow ) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("KITTY");

	if (!RegisterClass(&winc)) return -1;

	hwnd = CreateWindow(
			TEXT("KITTY") , TEXT("Kitty on your lap") ,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			NULL , NULL , hInstance , NULL
	);

	CreateWindow(
			TEXT("BUTTON") , TEXT("Check") ,
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_LEFTTEXT ,
			0 , 0 , 100 , 30 ,
			hwnd , (HMENU)HOTWEDNESDAY_1 , hInstance , NULL
	);

	CreateWindow(
			TEXT("BUTTON") , TEXT("Auto Check") ,
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX ,
			0 , 30 , 100 , 30 ,
			hwnd , NULL , hInstance , NULL
	);
	CreateWindow(
		    TEXT("BUTTON") , TEXT("kitty") ,
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
			0 , 50 , 100 , 30 ,
			hwnd , (HMENU)BUTTON_ID1 ,hInstance , NULL
	);

	if (hwnd == NULL) return -1;

	while(GetMessage(&msg , NULL , 0 , 0)) DispatchMessage(&msg);
	return msg.wParam;
}