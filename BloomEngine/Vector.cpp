#include "Vector.h"


Vector::Vector()
{

}

Vector::Vector(real32 x = 0, real32 y = 0, real32 z = 0)
		: x(x), y(y), z(z)
{
}

Vector& Vector::operator=(const Vector& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

Vector Vector::operator+(const Vector& a) const
{
	return Vector(a.x + x, a.y + y, z + a.z);
}

Vector Vector::operator-(const Vector& a) const
{
	return Vector(x - a.x, y - a.y, z - a.z);
}

Vector Vector::operator*(const Vector& a) const
{
	return Vector(x * a.x, y * a.y, z * a.z);
}

Vector Vector::operator*(real32 a) const
{
	return Vector(x * a, y * a, z * a);
}

Vector Vector::operator/(const Vector& a) const
{
	return Vector(x / a.x, y / a.y, z / a.z);
}

Vector Vector::operator/(const real32 a) const
{
	return Vector(x / a, y / a, z / a);
}

bool Vector::operator==(const Vector& a) const
{
	return (x == a.x && y == a.y && z == a.z);
}

/*
	Cos Angle between two vectors if both vectors are normalized.
*/
real32 Vector::DotProduct(Vector vector)
{
	return x * vector.x + y * vector.y + z * vector.z;
}

/*
	Returns a directional Vector to the two directional vectors
*/
Vector Vector::CrossProduct(Vector vector)
{
	return Vector(
		y * vector.z - z * vector.y,
		z * vector.x - x * vector.z,
		x * vector.y - y * vector.x
	);
}

real32 Vector::Length()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

real32 Vector::LengthSquared()
{
	return (x * x) + (y * y) + (z * z);
}

Vector Vector::Normalized()
{
	return *this / (Length() + 0.0001f);
}

Vector Vector::Convert2D()
{
	return Vector(x / z, y / z);
}

Vector Vector::Rotate(Vector angle, real32 degree)
{
	real32 radian = degree * pi32 / 180.0f;
	Vector newVector = *this - angle;
	real32 newX = newVector.x * cosf(radian) - newVector.y * sinf(radian);
	real32 newY = newVector.y * cosf(radian) + newVector.x * sinf(radian);
	return Vector(newX, newY, 0);
}

real32 Vector::Angle(Vector vector)
{
	return acosf(x * vector.x + y * vector.y + z * vector.z /
		(((x * x) + (y * y) + (z * z)) *
		((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z))));
}

Vector Vector::Interpolate(Vector vector, real32 t)
{
	return *this + (vector - *this) * t;
}

Vector Vector::InterpolateNormalized(Vector vector, real32 t)
{
	return Vector(*this + (vector - *this) * t).Normalized();
}