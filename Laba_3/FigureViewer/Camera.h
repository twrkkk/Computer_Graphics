#pragma once
#include "Vector2D.h"
#include "AffineTransform.h"

class Camera
{
private:
	Vector2D pos, scale;
public:
	Camera() : pos(0, 0), scale(1, 1) {}
	Camera(Vector2D pos, Vector2D scale = Vector2D(1, 1)) : pos(pos), scale(scale) {}

	Vector2D GetDot(const Vector2D& vector) const {
		Vector2D dot = vector;
		dot.ApplyTransformation(Translation(-pos.x(), -pos.y()));
		if (scale.x() != 1 || scale.y() != 1) {
			dot.ApplyTransformation(Scaling(scale.x(), scale.y()));
		}
		return dot;
	}

	void SetPosition(Vector2D newPos)
	{
		pos = newPos;
	}

	void SetScale(Vector2D newScale)
	{
		scale = newScale;
	}

	Vector2D Position()
	{
		return pos;
	}

	Vector2D Scale()
	{
		return scale;
	}
};