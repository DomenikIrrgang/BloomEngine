#include "Plane.h"

Plane::Plane(const Vector& n, const real32 d)
{
	this->n = n;
	this->d = d;
}

Plane::Plane(real32 a, real32 b, real32 c, real32 d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

Plane Plane::Normalized()
{
	const float length = n.Length();
	return Plane(n / length, d / length);
}

real32 Plane::DotProductNormal(const Vector& vector)
{
	return a * vector.x + b * vector.y + c * vector.z;
}

real32 Plane::DotProductCoords(const Vector& vector)
{
	return a * vector.x + b * vector.y + c * vector.z + d;
}

Plane PlaneFromPointCoords(const Vector& v1, const Vector& v2, const Vector& v3)
{
	return PlaneFromPointNormal(v1, (v3 - v2).CrossProduct((v1 - v2)));
}

Plane PlaneFromPointNormal(const Vector& p, const Vector& n)
{
	return Plane(n, -n.x * p.x - n.y * p.y - n.z * p.z);
}

Plane Plane::TransFormPlane(const Matrix& matrix)
{
	const real32 a = this->a * matrix.m11 + this->b * matrix.m21 + this->c * matrix.m31;
	const real32 b = this->a * matrix.m12 + this->b * matrix.m22 + this->c * matrix.m32;
	const real32 c = this->a * matrix.m13 + this->b * matrix.m23 + this->c * matrix.m33;
	return Plane(a, b, c, this->d - (a * matrix.m41 + b * matrix.m42 + c * matrix.m43));
}