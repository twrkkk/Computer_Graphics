#include "Scene2D.h"

Scene2D::Scene2D(HWND window, double X0, double Y0, double px, double py, std::vector<Model2D*> models) : Camera2D(window, X0, Y0, px, py), models(models)
{
}

void Scene2D::Plot(Func func, bool axes)
{
	if (axes)
		Axes();

	MoveTo(ScreenToWorldX(0), func(ScreenToWorldX(0)));

	for (int xf = 0; xf < W; ++xf)
	{
		double yf = func(ScreenToWorldX(xf));
		LineTo(ScreenToWorldX(xf), yf);
	}
}

void Scene2D::Render()
{
	for (int k = 0; k < models.size(); ++k)
	{
		auto model = models[k];
		/*model.getPoints()
		auto fpoint = models[k].GetVertex(i);
		auto spoint = models[k].GetVertex(j);
		MoveTo(fpoint.first, fpoint.second);
		LineTo(spoint.first, spoint.second);*/

		Vector2D start = model->GetVertices()[model->GetIndices()[0]];
		MoveTo(start.x(), start.y());

		int size = model->GetIndices().size();
		for (int i = 1; i < size; ++i) {

			Vector2D dot = model->GetVertices()[model->GetIndices()[i]];
			LineTo(dot.x(), dot.y());
		}
	}




}