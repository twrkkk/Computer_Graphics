#include "Vector2D.h"

Vector2D::Vector2D(const double& x, const double& y) :
    m_x(x),
    m_y(y)
{
}

Vector2D::Vector2D(const double& u1, const double& u2, const double& u3)
{
    m_x = u1 / u3;
    m_y = u2 / u3;
}

void Vector2D::setX(const double& x)
{
    m_x = x;
}

void Vector2D::setY(const double& y)
{
    m_y = y;
}

double Vector2D::x() const
{
    return m_x;
}

double Vector2D::y() const
{
    return m_y;
}

void Vector2D::ApplyTransformation(const Matrix<double>& M)
{
    float _x = m_x;
    float _y = m_y;

    m_x = M(1, 1) * _x + M(1, 2) * _y + M(1, 3);
    m_y = M(2, 1) * _x + M(2, 2) * _y + M(2, 3);
}
