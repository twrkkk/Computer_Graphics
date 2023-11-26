#include "Camera2D.h"
#include <cmath>

Camera2D::Camera2D(HWND hWindow, double X0, double Y0, double px, double py) : hWindow(hWindow), X0(X0), Y0(Y0), px(px), py(py)
{
	MoveTo(X0, Y0);
	W = GetScreenWindowWidth();
	H = GetScreenWindowHeight();
}

HDC Camera2D::GetDC() const
{
	return ::GetDC(hWindow);
}

void Camera2D::Clear()
{
	RECT rect = GetDCRect();
	Rectangle(GetDC(), rect.left, rect.top, rect.right, rect.bottom);
}

void Camera2D::SetResolution()
{
	int Wnew = GetScreenWindowWidth();
	int Hnew = GetScreenWindowHeight();

	const double pxdivpy = px / py;

	Y0 = Wnew / (double)W * pxdivpy * Y0 + (double)H / 2 * ((double)Hnew / H - (double)Wnew / W * pxdivpy);
	X0 = Wnew / (double)W * X0;

	px = Wnew * px / (double)W;
	py = Hnew * py / (double)H;

	W = Wnew;
	H = Hnew;
}

void Camera2D::MoveTo(double X, double Y)
{
	posX = X;
	posY = Y;
}

void Camera2D::LineTo(double X, double Y)
{
	HDC dc = GetDC();

	::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
	::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));

	posX = X;
	posY = Y;
}

void Camera2D::Axes()
{
	MoveTo(LeftBorder(), 0);
	LineTo(RightBorder(), 0);
	MoveTo(0, TopBorder());
	LineTo(0, BottomBorder());
}

int Camera2D::WorldToScreenX(double X) const
{
	return (int)round(X0 + px * X);
}

int Camera2D::WorldToScreenY(double Y) const
{
	return (int)round(Y0 - py * Y);
}

double Camera2D::ScreenToWorldX(int X) const
{
	const double DOT_CENTER = 0.5;
	return (X - X0 + DOT_CENTER) / px;
}

double Camera2D::ScreenToWorldY(int Y) const
{
	const double DOT_CENTER = 0.5;
	return (Y - Y0 + DOT_CENTER) / py;
}

double Camera2D::LeftBorder() const
{
	return -X0 / px;
}

double Camera2D::RightBorder() const
{
	return (W - X0) / px;
}

double Camera2D::BottomBorder() const
{
	return (Y0 - H) / py;
}

double Camera2D::TopBorder() const
{
	return Y0 / py;
}

RECT Camera2D::GetDCRect() const
{
	RECT rect;
	GetClientRect(hWindow, &rect);
	return rect;
}

int Camera2D::GetScreenWindowWidth() const
{
	RECT rect = GetDCRect();
	return rect.right - rect.left;
}

int Camera2D::GetScreenWindowHeight() const
{
	RECT rect = GetDCRect();
	return rect.bottom - rect.top;
}