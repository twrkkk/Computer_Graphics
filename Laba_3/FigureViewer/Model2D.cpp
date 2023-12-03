#include "Model2D.h"


Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int>& indices) :
	m_vertices(vertices),
	m_indices(indices)
{
}

Model2D::Model2D(const std::string path, double dX, double dY)
{
	Loader loader(path);
	loader.load();
	m_vertices = loader.vertices();
	m_indices = loader.indices();
	fillMatrix(dX, dY);
}

void Model2D::draw(const HDC& hdc, RECT& rcClient)
{

	auto Camera = [&rcClient](int x0_world, int y0_world, POINT source_point, int scale) -> POINT
	{
		int WIDTH = rcClient.right - rcClient.left, HEIGHT = rcClient.bottom - rcClient.top;
		int x_0 = WIDTH / 2 - x0_world;
		int y_0 = HEIGHT / 2 - y0_world;
		double x = x_0 + scale * source_point.x;
		double y = y_0 + scale * source_point.y;
		POINT pnt;
		pnt.x = int(x);
		pnt.y = int(y);

		return pnt;
	};

	POINT* pnts = new POINT[m_vertices.size()];
	POINT* modelPoints = getPoints();
	for (int i = 0; i < m_vertices.size(); ++i)
	{
		POINT tmp = Camera(350, 200, modelPoints[i], 1);
		pnts[i] = tmp;
	}
	Polygon(hdc, pnts, m_vertices.size());

	delete[] pnts;
}

void Model2D::apply(Matrix<> transformMat)
{
	m_modelMatrix = transformMat * m_modelMatrix;
}

pair<double, double> Model2D::getFirstCoord()
{
	return pair<double, double>(m_modelMatrix(0, 0), m_modelMatrix(1, 0));
}

void Model2D::fillMatrix(double dX, double dY)
{
	Matrix<> matrix(3, m_vertices.size());
	for (int i = 0; i < m_indices.size() - 1; i++)
	{
		matrix.setVaue(0, i, m_vertices[m_indices[i]].x() + dX);
		matrix.setVaue(1, i, m_vertices[m_indices[i]].y() + dY);
		matrix.setVaue(2, i, 1);
	}
	m_modelMatrix = matrix;
}

POINT* Model2D::getPoints()
{
	POINT* result = new POINT[m_vertices.size()];
	for (int i = 0; i < m_vertices.size(); i++)
	{
		result[i].x = round(m_modelMatrix(0, i) / m_modelMatrix(2, i));
		result[i].y = round(m_modelMatrix(1, i) / m_modelMatrix(2, i));
	}
	return result;
}
void Model2D::affin(Matrix<> transformMat)
{
	int tempX = getFirstCoord().first;
	int tempY = getFirstCoord().second;
	apply(Translation(-tempX, -tempY));
	apply(transformMat);
	apply(Translation(tempX, tempY));
}

void Model2D::Rotation_M(double O)
{
	O = (O * M_PI) / 180;
	affin(Rotation(O));

}
void Model2D::Translation_M(double x, double y)
{
	affin(Translation(x, y));
}

void Model2D::ScalingFigure(double kx, double ky)
{
	affin(Scaling(kx, ky));
}

void Model2D::ReflectOY()
{
	affin(Scaling(1, -1));
}

void Model2D::ReflectOX()
{
	affin(Scaling(-1, 1));
}
