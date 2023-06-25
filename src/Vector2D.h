#pragma once

class Vector2D {
public:
	float x;
	float y;

	Vector2D(): x(0.0f), y(0.0f) {}
	Vector2D(float _x, float _y): x(_x), y(_y) {}

	Vector2D& add(const Vector2D& vec);
	Vector2D& subtract(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);

	friend Vector2D& operator+(const Vector2D& v1, const Vector2D& v2);
};

const Vector2D UNIT_VECTOR(1, 1);