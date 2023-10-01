#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include "Circle.h"

Circle circle(100, 100, 100);

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), LPCSTR(L"MainWndClass"), windowProcedure);

	if (!RegisterClass(&mainWindow))
		return -1;

	HWND hwnd = CreateWindow(LPCSTR(L"MainWndClass"), LPCSTR(L"Circle"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 640, NULL, NULL, NULL, NULL);
	SetTimer(hwnd, 0, 50, NULL);

	MSG message = { 0 };
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}



WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;


	return wc;
}



void Draw(HWND& hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	circle.Draw(hdc);

	EndPaint(hWnd, &ps);

}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

	POINT point;
	LPPOINT position = &point;
	GetCursorPos(position);
	ScreenToClient(hWnd, position);

	switch (msg)
	{
	case WM_PAINT:
		Draw(hWnd);
		break;
	case WM_TIMER:
		if (circle.IsDragging()) {
			circle.Move(position->x, position->y);
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		if (circle.InnerPoint(position->x, position->y))
		{
			circle.StartDragging(position->x, position->y);
		}
		break;
	case WM_LBUTTONUP:
		circle.StopDragging();
		break;
	case WM_RBUTTONDOWN:
		circle.Move(position->x, position->y);
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}