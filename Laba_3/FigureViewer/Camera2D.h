#pragma once
#include <windows.h>
#include <utility>
#include <cmath>

class Camera2D
{
public:
	Camera2D(HWND window, double X0, double Y0, double px, double py);

	// �������� ������� ������� ����
	HDC GetDC() const;

	// ������� ������� ������� ����
	void Clear();

	// ������ ��������� ���������� ��� ��������� �������� ����. � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� X0, Y0, px, py ����� �������, ����� ���������� ���������� �������� �� ������������ ����
	void SetResolution();

	// ����������� ������������ ������� (posX, posY). �������� ��������, ��� �� ��������� � ������� �����������
	void MoveTo(double X, double Y);

	// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����. �������� ��������, ��� �� ��������� � ������� �����������
	void LineTo(double X, double Y);

	// ��������� ������������ ����
	void Axes();

protected:
	// �������� ���������� ������ ������� ������� ���������
	double X0, Y0;

	// ������� �������� ������� ������� ���������, ���������� � ��������
	double px, py;

	// ���������� ������� ������� ����
	int W, H;

	// ������� �� ������� ��������� � �������� (��� ��������)
	int WorldToScreenX(double X) const;

	// ������� �� ������� ��������� � �������� (��� ��������)
	int WorldToScreenY(double Y) const;
	
	// ������� �� �������� ��������� � ������� (��� ��������)
	double ScreenToWorldX(int X) const;
	
	// ������� �� �������� ��������� � ������� (��� ��������)
	double ScreenToWorldY(int Y) const;
	
	// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	double LeftBorder() const;
	
	// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	double RightBorder() const;
	
	// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	double BottomBorder() const;
	
	// �������� ������� ������� ������� ������� ���� (� ������� �����������)
	double TopBorder() const;

	// �������� ������������� ������� �������
	RECT GetDCRect() const;

	// �������� ������ ���� � ������� �����������
	int GetScreenWindowWidth() const;

	// �������� ����� ���� � ������� �����������
	int GetScreenWindowHeight() const;

private:
	// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
	double posX, posY;

	// ������� ����
	HWND hWindow;
};