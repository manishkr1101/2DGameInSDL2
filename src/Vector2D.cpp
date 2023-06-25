#include "Vector2D.h"

Vector2D& Vector2D::add(const Vector2D& vec)
{
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
}

Vector2D& operator+(const Vector2D& v1, const Vector2D& v2)
{
    Vector2D v(v1);
    return v.add(v2);
}
