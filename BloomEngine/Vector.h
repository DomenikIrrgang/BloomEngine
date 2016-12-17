#ifndef VECTOR_H
#define VECTOR_H

#include "Definitions.h"
#include <math.h>

typedef struct Vector
{
	real32 x;
	real32 y;
	real32 z;

	Vector();
	Vector(real32 x, real32 y, real32 z);
	Vector& operator=(const Vector& a);
	Vector operator+(const Vector& a) const;
	Vector operator-(const Vector& a) const;
	Vector operator*(const Vector& a) const;
	Vector operator*(real32 a) const;
	Vector operator/(const Vector& a) const;
	Vector operator/(const real32 a) const;
	bool operator==(const Vector& a) const;
	real32 DotProduct(Vector vector);
	Vector CrossProduct(Vector vector);
	real32 Length();
	real32 LengthSquared();
	Vector Normalized();
	Vector Convert2D();
	Vector Rotate(Vector angle, real32 degree);
	real32 Angle(Vector vector);
	Vector Interpolate(Vector vector, real32 t);
	Vector InterpolateNormalized(Vector vector, real32 t);

} Vector;

#endif