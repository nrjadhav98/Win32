// Headers
#include<windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	
	static int iPaintFlag = NULL;	//Using Accross The Message  
	PAINTSTRUCT ps;
	RECT rc;
	GetClientRect(hwnd, &rc);
	switch (iMsg)
	{

	case WM_CHAR:
		switch (LOWORD(wParam))
		{
			case 'R':
			case 'r':
				iPaintFlag = 1;
				InvalidateRect(hwnd, &rc, 0);
				break;

			case 'G':
			case 'g':
				iPaintFlag = 2;
				InvalidateRect(hwnd, &rc, 0);
				break;

			case 'B':
			case 'b':
				iPaintFlag = 3;
				InvalidateRect(hwnd, &rc, 0);
				break;

			case 'C':
			case 'c':
				iPaintFlag = 4;
				InvalidateRect(hwnd, &rc, 0);
				break;

			case 'M':
			case 'm':
				iPaintFlag = 5;
				InvalidateRect(hwnd, &rc, 0);
				break;

			case 'Y':
			case 'y':
				iPaintFlag = 6;
				InvalidateRect(hwnd, &rc, 0);
				break;

			case 'W':
			case 'w':
				iPaintFlag = 7;
				InvalidateRect(hwnd, &rc, 0);
				break;

			case 'K':
			case 'k':
			default:
				iPaintFlag = 0;
				InvalidateRect(hwnd, &rc, 0);
				break;
		}
		break;
		
			case WM_PAINT:
			{
				HDC hdc;
				HBRUSH hBrush;
				//GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				switch (iPaintFlag)
				{
					//RECT rc;
				case 0:
					hBrush = CreateSolidBrush(RGB(0,0,0));	//BLACK
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(0, 0, 0)));
					break;
	
				case 1:
					hBrush = CreateSolidBrush(RGB(255, 0, 0));	//RED
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(255, 0, 0)));
					break;

				case 2:
					hBrush = CreateSolidBrush(RGB(0, 255, 0));	//GREEN
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(0, 255, 0)));
					break;

				case 3:
					hBrush = CreateSolidBrush(RGB(0, 0, 255));	//BLUE
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(0, 0, 255)));
					break;

				case 4:
					hBrush = CreateSolidBrush(RGB(0, 255, 255));	//CYAN
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(0, 255, 255)));
					break;

				case 5:
					hBrush = CreateSolidBrush(RGB(255, 0, 255));	//MAGINTA
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(255, 0, 255)));
					break;

				case 6:
					hBrush = CreateSolidBrush(RGB(255, 255, 0));	//YELLOW
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(255, 255, 0)));
					break;

				case 7:
					hBrush = CreateSolidBrush(RGB(255, 255, 255));	//WHITE
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(255, 255, 255)));
					break;
				
				default:
					hBrush = CreateSolidBrush(RGB(0, 0, 0));	//BLACK
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, CreateSolidBrush(RGB(0,0,0)));
					break;
				}

				// All painting occurs here, between BeginPaint and EndPaint.

				EndPaint(hwnd, &ps);
				break;
			}
		//	return 0;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}


