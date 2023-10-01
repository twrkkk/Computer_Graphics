#pragma once
#include <Windows.h>
#include <math.h>
#include <stdlib.h>
#include "Figure.h"

class Circle : public Figure {
public:
	class Circle(int size, int posX, int posY) : Figure(size, posX, posY) {
	}

	void Draw(HDC& hdc) {
		Ellipse(hdc, _posX - _size, _posY - _size, _posX + _size, _posY + _size);
	}

	bool InnerPoint(int X, int Y) {
		float lengthX = X - _posX,
			lengthY = Y - _posY;

		if (lengthX * lengthX + lengthY * lengthY < _size * _size) {
			return true;
		}
		else {
			return false;
		}

	}
};