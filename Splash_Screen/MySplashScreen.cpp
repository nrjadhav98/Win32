// Headers
#include<windows.h>
#include"MySplashScreen.h"
// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;  
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	HDC hdc, hdcMem;
	RECT rc;
	PAINTSTRUCT ps;
	BITMAP bitmap;
	HBITMAP hBitmap;

	switch (iMsg)
	{
		case WM_PAINT:
			GetClientRect(hwnd,&rc);
			
			hdc = BeginPaint(hwnd,&ps);
			
			hBitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(MYBITMAP));
			GetObject(hBitmap,sizeof(BITMAP),&bitmap);

			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem,hBitmap);
		
			StretchBlt(hdc,
			0,
			0,
			rc.right-rc.left,
			rc.bottom-rc.top,
			hdcMem,
			0,
			0,
			bitmap.bmWidth,
			bitmap.bmHeight,
			MERGECOPY);
			
			DeleteDC(hdcMem);
			EndPaint(hwnd,&ps);
			break; 
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}




