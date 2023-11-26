#pragma once
#include <windows.h>
#include <utility>
#include <cmath>

class Camera2D
{
public:
	Camera2D(HWND window, double X0, double Y0, double px, double py);

	// Полчение рабочей области окна
	HDC GetDC() const;

	// Очистка рабочей области окна
	void Clear();

	// Данная процедура вызывается при изменении размеров окна. В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	void SetResolution();

	// Перемещение графического курсора (posX, posY). Обратите внимание, что мы действуем в мировых координатах
	void MoveTo(double X, double Y);

	// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку. Обратите внимание, что мы действуем в мировых координатах
	void LineTo(double X, double Y);

	// Отрисовка координатных осей
	void Axes();

protected:
	// Экранные координаты начала мировой системы координат
	double X0, Y0;

	// Единицы масштаба мировой системы координат, выраженные в пикселях
	double px, py;

	// Разрешение рабочей области окна
	int W, H;

	// Переход от мировых координат к экранным (для абсциссы)
	int WorldToScreenX(double X) const;

	// Переход от мировых координат к экранным (для ординаты)
	int WorldToScreenY(double Y) const;
	
	// Переход от экранных координат к мировым (для абсциссы)
	double ScreenToWorldX(int X) const;
	
	// Переход от экранных координат к мировым (для ординаты)
	double ScreenToWorldY(int Y) const;
	
	// Абсцисса левой границы рабочей области окна (в мировых координатах)
	double LeftBorder() const;
	
	// Абсцисса правой границы рабочей области окна (в мировых координатах)
	double RightBorder() const;
	
	// Ордината нижней границы рабочей области окна (в мировых координатах)
	double BottomBorder() const;
	
	// Ордината верхней границы рабочей области окна (в мировых координатах)
	double TopBorder() const;

	// Получает прямоугольник рабочей области
	RECT GetDCRect() const;

	// Получает ширину окна в оконных координатах
	int GetScreenWindowWidth() const;

	// Получает длину окна в оконных координатах
	int GetScreenWindowHeight() const;

private:
	// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
	double posX, posY;

	// Текущее окно
	HWND hWindow;
};