#pragma once
#include <Windows.h>
#include <windowsx.h>
#include "Render2D.h"
#include "Scene2D.h"


WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

Render2D render;
double X0 = 100, Y0 = 200, px = 0.1, py = 0.1;
Scene2D* scene;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	render.addObject(new Model2D("figure1.txt", 0, 0));
	render.addObject(new Model2D("figure2.txt", 0, 0));

	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClass(&mainWindow))
		return -1;

	HWND hWnd = CreateWindow(LPCSTR(L"MainWndClass"), LPCSTR(L"MainWindow"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 400, 400, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG message = { 0 };
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = LPCSTR(windowName);
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc = NULL;
	HBRUSH brush = NULL;
	const char KEY_W = 0x57;
	const char KEY_Q = 0x51;
	const char KEY_E = 0x45;
	const char KEY_S = 0x53;
	const char KEY_C = 0x43;

	switch (msg)
	{
	case WM_CREATE:
		scene = new Scene2D(hWnd, X0, Y0, px, py, render.get_models());
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		/*hdc = GetDC(hWnd);
		brush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, brush);
		render.draw(hdc);
		DeleteObject(brush);
		ReleaseDC(hWnd, hdc);*/
		//scene->Clear();				// Вызов реализованного в классе Camera2D метода, отвечающего за очистку рабочей области окна hWnd
		brush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(scene->GetDC(), brush);
		scene->Render();
		DeleteObject(brush);
		ReleaseDC(hWnd, scene->GetDC());
		return DefWindowProc(hWnd, msg, wp, lp);
		break;
	case WM_MOUSEWHEEL:
	{
		double wheelNow = GET_WHEEL_DELTA_WPARAM(wp);

		if (wheelNow > 0) {
			render.get_model()->ScalingFigure(1.1, 1.1);
		}
		else {
			render.get_model()->ScalingFigure(0.9, 0.9);
		}

		InvalidateRect(hWnd, nullptr, true);
	}
	case WM_KEYDOWN:
	{
		switch (wp)
		{
		case VK_UP:
		{
			render.get_model()->Translation_M(0, -10);
			break;
		}
		case VK_DOWN:
		{
			render.get_model()->Translation_M(0, 10);
			break;
		}
		case VK_LEFT:
		{
			render.get_model()->Translation_M(-10, 0);
			break;
		}
		case VK_RIGHT:
		{
			render.get_model()->Translation_M(10, 0);
			break;
		}
		case KEY_W:
		{
			render.get_model()->ReflectOY();
			break;
		}
		case KEY_S:
		{
			render.get_model()->ReflectOX();
			break;
		}
		case KEY_Q:
		{
			render.get_model()->Rotation_M(-45);
			break;
		}
		case KEY_E:
		{
			render.get_model()->Rotation_M(45);
			break;
		}
		case KEY_C:
		{
			render.nextObj();
			break;
		}
		}
		InvalidateRect(hWnd, NULL, true);
		return 0;
	}
	case WM_SIZE:
	{
		scene->SetResolution();
		ReleaseDC(hWnd, scene->GetDC());
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
