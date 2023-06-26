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

Vector2D& Vector2D::zero()
{
    this->x = this->y = 0;
    return *this;
}

Vector2D& Vector2D::multiply(const int& i)
{
    this->x *= i;
    this->y *= i;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
    return this->add(vec);
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
{
    Vector2D v(v1);
    return v.add(v2);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")\n";
    return os;
}
