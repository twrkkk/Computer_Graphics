#include <windows.h>
#include <windowsx.h>

POINT startPoint = { 0, 0 };
POINT endPoint = { 0, 0 };
COLORREF currentColor = RGB(255, 0, 0);  // ��������� ���� - �������

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{

	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� ��������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Figure Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200, 200, 400, 400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch (msg)
	{
	case WM_RBUTTONDOWN:
	{
		startPoint.x = GET_X_LPARAM(lParam);
		startPoint.y = GET_Y_LPARAM(lParam);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		endPoint.x = GET_X_LPARAM(lParam);
		endPoint.y = GET_Y_LPARAM(lParam);

		HDC dc = GetDC(hWnd);
		HPEN hPen = CreatePen(PS_SOLID, 1, currentColor);  // ���������� ������� ����
		HPEN hOldPen = (HPEN)SelectObject(dc, hPen);

		MoveToEx(dc, startPoint.x, startPoint.y, nullptr);
		LineTo(dc, endPoint.x, endPoint.y);

		SelectObject(dc, hOldPen);
		DeleteObject(hPen);

		ReleaseDC(hWnd, dc);
		return 0;
	}
	case WM_KEYDOWN:
	{
		if (wParam == 'C' || wParam == 'c')
		{
			// ���������� ��������� ����
			currentColor = RGB(rand() % 256, rand() % 256, rand() % 256);

			// ��������� ���� ��� ����������� ������ �����
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;
	}
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}
