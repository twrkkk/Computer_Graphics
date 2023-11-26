#pragma once
#include <vector>
#include <Windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wingdi.h>
#include "Vector2D.h"
#include "Matrix.h"
#include "Loader.h"
#include "AffineTransform.h"
#include "Camera.h"

class Model2D
{
public:
	Model2D() = default;
	Model2D(const std::vector<Vector2D>& vertices, const std::vector<int>& indices);
	Model2D(const std::string path, double dX, double dY);

	void draw(const HDC& hdc, const Camera& cam);
	void apply(Matrix<> transformMat);
	void affin(Matrix<> transformMat);
	void Rotation_M(double O);
	void Translation_M(double x, double y);

	void ScalingFigure(double kx, double ky);
	void ReflectOY();
	void ReflectOX();
	pair<double, double> getFirstCoord();

private:
	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	Matrix<> m_modelMatrix;
	void fillMatrix(double dX, double dY);
	POINT* getPoints();
};
