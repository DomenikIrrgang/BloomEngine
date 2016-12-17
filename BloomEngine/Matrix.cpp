#include "Matrix.h"

Matrix::Matrix(real32 c11, real32 c12, real32 c13, real32 c14,
		real32 c21, real32 c22, real32 c23, real32 c24,
		real32 c31, real32 c32, real32 c33, real32 c34,
		real32 c41, real32 c42, real32 c43, real32 c44) : m11(c11), m12(c12), m13(c13), m14(c14),
		m21(c21), m22(c22), m23(c23), m24(c24),
		m31(c31), m32(c32), m33(c33), m34(c34),
		m41(c41), m42(c42), m43(c43), m44(c44)
{
}

Matrix Matrix::operator+(const Matrix& matrix)
{
	return Matrix(m11 + matrix.m11, m12 + matrix.m12, m13 + matrix.m13, m14 + matrix.m14,
		m21 + matrix.m21, m22 + matrix.m22, m23 + matrix.m23, m24 + matrix.m24,
		m31 + matrix.m31, m32 + matrix.m32, m33 + matrix.m33, m34 + matrix.m34,
		m41 + matrix.m41, m42 + matrix.m42, m43 + matrix.m43, m44 + matrix.m44);
}

Matrix Matrix::operator*(const Matrix& matrix)
{
	return Matrix(
		matrix.m11 * m11 + matrix.m21 * m12 + matrix.m31 * m13 + matrix.m41 * m14,
		matrix.m12 * m11 + matrix.m22 * m12 + matrix.m32 * m13 + matrix.m42 * m14,
		matrix.m13 * m11 + matrix.m23 * m12 + matrix.m33 * m13 + matrix.m43 * m14,
		matrix.m14 * m11 + matrix.m24 * m12 + matrix.m34 * m13 + matrix.m44 * m14,
		matrix.m11 * m21 + matrix.m21 * m22 + matrix.m31 * m23 + matrix.m41 * m24,
		matrix.m12 * m21 + matrix.m22 * m22 + matrix.m32 * m23 + matrix.m42 * m24,
		matrix.m13 * m21 + matrix.m23 * m22 + matrix.m33 * m23 + matrix.m43 * m24,
		matrix.m14 * m21 + matrix.m24 * m22 + matrix.m34 * m23 + matrix.m44 * m24,
		matrix.m11 * m31 + matrix.m21 * m32 + matrix.m31 * m33 + matrix.m41 * m34,
		matrix.m12 * m31 + matrix.m22 * m32 + matrix.m32 * m33 + matrix.m42 * m34,
		matrix.m13 * m31 + matrix.m23 * m32 + matrix.m33 * m33 + matrix.m43 * m34,
		matrix.m14 * m31 + matrix.m24 * m32 + matrix.m34 * m33 + matrix.m44 * m34,
		matrix.m11 * m41 + matrix.m21 * m42 + matrix.m31 * m43 + matrix.m41 * m44,
		matrix.m12 * m41 + matrix.m22 * m42 + matrix.m32 * m43 + matrix.m42 * m44,
		matrix.m13 * m41 + matrix.m23 * m42 + matrix.m33 * m43 + matrix.m43 * m44,
		matrix.m14 * m41 + matrix.m24 * m42 + matrix.m34 * m43 + matrix.m44 * m44
	);
}

float& Matrix::operator()(int row, int column)
{
	return m[row - 1][column - 1];
}

float Matrix::operator()(int row, int column) const
{
	return m[row - 1][column - 1];
}

real32 Matrix::Determinant()
{
	return m11 * (m22 * m33 - m23 * m32) -
		m12 * (m21 * m33 - m23 * m31) +
		m13 * (m21 * m32 - m22 * m31);
}

Matrix Matrix::Inverted()
{
	float fInvDet = Determinant();
	if (fInvDet == 0.0f) return IdentityMatrix();
	fInvDet = 1.0f / fInvDet;
	Matrix result;
	result.m11 = fInvDet * (m22 * m33 - m23 * m32);
	result.m12 = -fInvDet * (m12 * m33 - m13 * m32);
	result.m13 = fInvDet * (m12 * m23 - m13 * m22);
	result.m14 = 0.0f;
	result.m11 = -fInvDet * (m21 * m33 - m23 * m31);
	result.m12 = fInvDet * (m11 * m33 - m13 * m31);
	result.m13 = -fInvDet * (m11 * m23 - m13 * m21);
	result.m14 = 0.0f;
	result.m11 = fInvDet * (m21 * m32 - m22 * m31);
	result.m12 = -fInvDet * (m11 * m32 - m12 * m31);
	result.m13 = fInvDet * (m11 * m22 - m12 * m21);
	result.m14 = 0.0f;
	result.m11 = -fInvDet * (m41 * result.m11 + m42 * result.m21 + m43 * result.m31);
	result.m12 = -fInvDet * (m41 * result.m12 + m42 * result.m22 + m43 * result.m32);
	result.m13 = -fInvDet * (m41 * result.m13 + m42 * result.m23 + m43 * result.m33);
	result.m14 = 1.0f;
	return result;
}

Matrix Matrix::Transponsed()
{
	return Matrix(m11, m21, m31, m41,
		m12, m22, m32, m42,
		m13, m23, m33, m43,
		m14, m24, m34, m44
	);
}

Matrix IdentityMatrix()
{
	return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix TranslationMatrix(const Vector& vector)
{
	return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		vector.x, vector.y, vector.z, 1.0f);
}

Matrix RotationMatrixX(real32 rotation)
{
	Matrix result;
	result.m11 = 1.0f; result.m12 = 0.0f; result.m13 = 0.0f; result.m14 = 0.0f;
	result.m21 = 0.0f; result.m24 = 0.0f;
	result.m31 = 0.0f; result.m34 = 0.0f;
	result.m41 = 0.0f; result.m42 = 0.0f; result.m43 = 0.0f; result.m44 = 1.0f;
	result.m22 = result.m33 = cosf(rotation);
	result.m23 = sinf(rotation);
	result.m32 = -result.m24;
	return result;
}

Matrix RotationMatrixY(real32 rotation)
{
	Matrix result;
	result.m12 = 0.0f; result.m14 = 0.0f;
	result.m21 = 0.0f; result.m22 = 1.0f; result.m23 = 0.0f; result.m24 = 0.0f;
	result.m32 = 0.0f; result.m34 = 0.0f;
	result.m41 = 0.0f; result.m42 = 0.0f; result.m43 = 0.0f; result.m44 = 1.0f;
	result.m11 = result.m33 = cosf(rotation);
	result.m31 = sinf(rotation);
	result.m13 = -result.m31;
	return result;
}

Matrix RotationMatrixZ(real32 rotation)
{
	Matrix result;
	result.m13 = 0.0f; result.m14 = 0.0f;
	result.m23 = 0.0f; result.m24 = 0.0f;
	result.m31 = 0.0f; result.m32 = 0.0f; result.m33 = 1.0f; result.m34 = 0.0f;
	result.m41 = 0.0f; result.m42 = 0.0f; result.m43 = 0.0f; result.m44 = 1.0f;
	result.m11 = result.m22 = cosf(rotation);
	result.m12 = sinf(rotation);
	result.m21 = -result.m12;
	return result;
}

Matrix RoationMatrixAxis(Vector& vector, const real32 rotation)
{
	const real32 fSin = sinf(-rotation), fCos = cosf(-rotation);
	const real32 fOneMinusCos = 1.0f - fCos;

	const Vector vAxis = vector.Normalized();

	return Matrix((vAxis.x * vAxis.x) * fOneMinusCos + fCos,
		(vAxis.x * vAxis.y) * fOneMinusCos - (vAxis.z * fSin),
		(vAxis.x * vAxis.z) * fOneMinusCos + (vAxis.y * fSin), 0.0f,
		(vAxis.y * vAxis.x) * fOneMinusCos + (vAxis.z * fSin),
		(vAxis.y * vAxis.y) * fOneMinusCos + fCos,
		(vAxis.y * vAxis.z) * fOneMinusCos - (vAxis.x * fSin), 0.0f,
		(vAxis.z * vAxis.x) * fOneMinusCos - (vAxis.y * fSin),
		(vAxis.z * vAxis.y) * fOneMinusCos + (vAxis.x * fSin),
		(vAxis.z * vAxis.z) * fOneMinusCos + fCos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix ScalingMatrix(const Vector& vector)
{
	return Matrix(vector.x, 0.0f, 0.0f, 0.0f,
		0.0f, vector.y, 0.0f, 0.0f,
		0.0f, 0.0f, vector.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix CameraMatrix(const Vector& position, const Vector& direction, Vector& upVector)
{
	Vector ZAxis = (direction - position).Normalized();
	Vector XAxis = upVector.CrossProduct(ZAxis).Normalized();
	Vector YAxis = ZAxis.CrossProduct(XAxis).Normalized();

	return TranslationMatrix(position * -1.0f) * Matrix(XAxis.x, YAxis.x, ZAxis.x, 0.0f,
		XAxis.y, YAxis.y, ZAxis.y, 0.0f,
		XAxis.z, YAxis.z, ZAxis.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

/*
Transforms position vectors.
*/
Vector TransformCoordinates(const Vector& vector, const Matrix& matrix, float* const outW)
{
	Vector result(vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31 + matrix.m41,
		vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32 + matrix.m42,
		vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33 + matrix.m43);
	const float w = vector.x * matrix.m14 + vector.y * matrix.m24 + vector.z * matrix.m34 + matrix.m44;
	if (w != 1.0f) result = result / w;
	if (outW) *outW = w;
	return result;
}


/*
Transforms directional vectors with a given transponsed & inverted matrix.
*/
Vector TransformNormalWithInverted(Vector& vector, const Matrix& matrix)
{
	const float length = vector.Length();
	if (length == 0.0f) return vector;
	return Vector(vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31,
		vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32,
		vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33).Normalized() * length;
}

/*
Transforms directional vectors.
*/
Vector TransformNormal(Vector& vector, Matrix& matrix)
{
	const float length = vector.Length();
	if (length == 0.0f) return vector;
	const Matrix newMatrix = matrix.Inverted().Transponsed();
	return Vector(vector.x * newMatrix.m11 + vector.y * newMatrix.m21 + vector.z * newMatrix.m31,
		vector.x * newMatrix.m12 + vector.y * newMatrix.m22 + vector.z * newMatrix.m32,
		vector.x * newMatrix.m13 + vector.y * newMatrix.m23 + vector.z * newMatrix.m33).Normalized() * length;
}