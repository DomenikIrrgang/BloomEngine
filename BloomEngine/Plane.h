#ifndef PLANE_H
#define PLANE_H

#include "Vector.h"
#include "Matrix.h"
#include "Definitions.h"

typedef struct Plane
{
	union
	{
		struct
		{
			real32 a, b, c;
		};
		Vector n;
	};

	real32 d;

	Plane(const Vector& n, const real32 d);
	Plane(real32 a, real32 b, real32 c, real32 d);
	Plane Normalized();
	real32 DotProductNormal(const Vector& vector);
	real32 DotProductCoords(const Vector& vector);
	Plane TransFormPlane(const Matrix& matrix);
} Plane;

Plane PlaneFromPointNormal(const Vector& p, const Vector& n);
Plane PlaneFromPointCoords(const Vector& v1, const Vector& v2, const Vector& v3);

#endif