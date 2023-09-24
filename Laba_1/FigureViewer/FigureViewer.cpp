#include <windows.h>
#include <windowsx.h>

POINT startPoint = { 0, 0 };
POINT endPoint = { 0, 0 };
COLORREF currentColor = RGB(255, 0, 0);  // Начальный цвет - красный

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основная процедура
{

	// Первая составляющая часть основной процедуры - создание окна: сначала описывается оконный класс wc, затем создается окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// имя оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложения, содержащий адрес начала выделенной ему области памяти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// имя оконного класса, используемое при создании экземпляров окна
	RegisterClass(&wc);								// регистрация класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// имя оконного класса
		(LPCSTR)"Figure Viewer",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200, 200, 400, 400,							// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Вторая составляющая часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщения и рассылает их соответствующим окнам
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// функция GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функция DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
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
		HPEN hPen = CreatePen(PS_SOLID, 1, currentColor);  // Используем текущий цвет
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
			// Генерируем случайный цвет
			currentColor = RGB(rand() % 256, rand() % 256, rand() % 256);

			// Обновляем окно для отображения нового цвета
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
