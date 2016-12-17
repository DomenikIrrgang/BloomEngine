#ifndef MATRIX_H
#define MATRIX_H

#include "Definitions.h"
#include <math.h>
#include "Vector.h"

typedef struct Matrix
{
	union
	{
		struct
		{
			real32 m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
		};
		float m[4][4];
	};

	Matrix()
	{}

	Matrix(real32 c11, real32 c12, real32 c13, real32 c14,
		real32 c21, real32 c22, real32 c23, real32 c24,
		real32 c31, real32 c32, real32 c33, real32 c34,
		real32 c41, real32 c42, real32 c43, real32 c44);
	Matrix operator+(const Matrix& matrix);
	Matrix operator*(const Matrix& matrix);
	float& operator()(int row, int column);
	float operator()(int row, int column) const;
	real32 Determinant();
	Matrix Inverted();
	Matrix Transponsed();
} Matrix;


Matrix IdentityMatrix();
Matrix TranslationMatrix(const Vector& vector);
Matrix RotationMatrixX(real32 rotation);
Matrix RotationMatrixY(real32 rotation);
Matrix RotationMatrixZ(real32 rotation);
Matrix RoationMatrixAxis(Vector& vector, const real32 rotation);
Matrix ScalingMatrix(const Vector& vector);
Matrix CameraMatrix(const Vector& position, const Vector& direction, Vector& upVector);
Vector TransformCoordinates(const Vector& vector, const Matrix& matrix, float* const outW);
Vector TransformNormalWithInverted(Vector& vector, const Matrix& matrix);
Vector TransformNormal(Vector& vector, Matrix& matrix);

#endif