#include "AffineTransform.h"

Matrix<> Translation(double x, double y)
{
	double T[9] =
	{
		1, 0, x,
		0, 1, y,
		0, 0, 1
	};
	return Matrix<>(3, 3, T);
}

Matrix<> Identity()
{
	double I[9] =
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
	return Matrix<>(3, 3, I);
}

Matrix<> Scaling(double kx, double ky)
{
	double S[9] =
	{
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1
	};
	return Matrix<>(3, 3, S);
}

Matrix<> Rotation(double grad)
{
	double R[9] =
	{
		cos(grad), -sin(grad), 0,
		sin(grad), cos(grad), 0,
		0, 0, 1
	};
	return Matrix<>(3, 3, R);
}

Matrix<> ReflectAll()
{
	return Scaling(-1, -1);
}