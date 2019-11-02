// Headers
#include<windows.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

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
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;

	switch (iMsg)
	{

	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("MessageBox"), TEXT("LeftMouseClicked"), MB_OK | MB_ICONASTERISK);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}




	DWORD WINAPI ThreadProcOne(LPVOID Param) 
	{
	
		HDC hdc;
		long int i;
		TCHAR str[255];

		hdc = GetDC((HWND)Param);
		SetTextColor(hdc, RGB(0, 255, 0));

		for (i = 0; i < 4294967295; i++)
		{
			wsprintf(str, TEXT("ThreadOne -> Increasing Order: %ld"),i);
			TextOut(hdc,5,5,str,wcslen(str));
		}
		ReleaseDC((HWND)Param,hdc);
		return 0;
	}



	DWORD WINAPI ThreadProcTwo(LPVOID Param)
	{

		HDC hdc;
		long int i;
		TCHAR str[255];

		hdc = GetDC((HWND)Param);
		SetTextColor(hdc, RGB(0, 255, 0));
		
		for (i = 429496729; i>0 ; i--)
		{
			wsprintf(str,TEXT("ThreadTwo -> Decreasing Order: %ld"), i);
			TextOut(hdc, 5, 20, str, wcslen(str));
		}
		ReleaseDC((HWND)Param, hdc);
		return 0;
	}
  





