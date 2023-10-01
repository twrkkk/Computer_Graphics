#pragma once
#include <Windows.h>
#include <math.h>
#include <stdlib.h>

class Figure
{
protected:
	int _size;
	int _posX, _posY;
private:
	int _mouseOffsetX, _mouseOffsetY;
	bool _isDragging;
public:
	Figure(int size, int posX, int posY) : _size(size), _posX(posX), _posY(posY), _isDragging(false)
	{
	}

	virtual void Draw(HDC& dc) = 0;
	virtual bool InnerPoint(int X, int Y) = 0;

	void Move(int X, int Y) {
		_posX = X + _mouseOffsetX;
		_posY = Y + _mouseOffsetY;
	}

	void StartDragging(int mousePosX, int mousePosY)
	{
		_isDragging = true;
		_mouseOffsetX = _posX - mousePosX;
		_mouseOffsetY = _posY - mousePosY;
	}
	void StopDragging()
	{
		_mouseOffsetX = 0;
		_mouseOffsetY = 0;
		_isDragging = false;
	}
	bool IsDragging()
	{
		return _isDragging;
	}
};
