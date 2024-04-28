#define _USE_MATH_DEFINES

#include "Matrix3x3.h"
#include <cassert>
#include <cmath>

Matrix3x3::Matrix3x3() noexcept //Default constuctor for Matrix3x3
{
	fRows[0] = Vector3D(1.0f, 0.0f, 0.0f);
	fRows[1] = Vector3D(0.0f, 1.0f, 0.0f);
	fRows[2] = Vector3D(0.0f, 0.0f, 1.0f);
}

Matrix3x3::Matrix3x3(const Vector3D& aRow1, const Vector3D& aRow2, const Vector3D& aRow3) noexcept
{
	fRows[0] = aRow1;
	fRows[1] = aRow2;
	fRows[2] = aRow3;
}

Matrix3x3 Matrix3x3::operator*(const float aScalar) const noexcept //If we do a (3x3Matrix) * (float) the result will be a (3x3Matrix)
{
	return Matrix3x3(fRows[0] * aScalar, fRows[1] * aScalar, fRows[2] * aScalar);
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& aOther) const noexcept //If we do a (3x3Matrix) + (3x3Matrix) the result will be another (3x3Matrix)
{
	return Matrix3x3(fRows[0] + aOther.fRows[0], fRows[1] + aOther.fRows[1], fRows[2] + aOther.fRows[2]);
}

Vector3D Matrix3x3::operator*(const Vector3D& aVector) const noexcept //If we do a (3x3Matrix) * (Vector3D) the result will be a (Vector3D)
{
	return Vector3D(fRows[0].dot(aVector), fRows[1].dot(aVector), fRows[2].dot(aVector));
}

Matrix3x3 Matrix3x3::scale(const float aX, const float aY) //Refer to the Matrix PDF in order to understand why a scale matrix looks like this
{
	return Matrix3x3(	
						Vector3D(aX, 0.0f, 0.0f), 
						Vector3D(0.0f, aY, 0.0f), 
						Vector3D(0.0f, 0.0f, 1.0f)
					);
}

Matrix3x3 Matrix3x3::translate(const float aX, const float aY) //Refer to the Matrix PDF in order to understand why a translate matrix looks like this
{
	return Matrix3x3(
						Vector3D(1.0f, 0.0f, aX), 
						Vector3D(0.0f, 1.0f, aY), 
						Vector3D(0.0f, 0.0f, 1.0f)
					);
}

Matrix3x3 Matrix3x3::rotate(const float aAngleInDegree) //Refer to the Matrix PDF in order to understand why a rotate matrix looks like this
{
	float lRadTheta = aAngleInDegree * static_cast<float>(M_PI) / 180.0f;

	float lSinTheta = std::sin(lRadTheta);
	float lCosTheta = std::cos(lRadTheta);

	return Matrix3x3(
						Vector3D(lCosTheta,-lSinTheta,0.0f), 
						Vector3D(lSinTheta,lCosTheta,0.0f), 
						Vector3D(0.0f,0.0f,1.0f)
					);
}

const Vector3D Matrix3x3::row(size_t aRowIndex) const
{
	assert(aRowIndex < 3);
	
	return fRows[aRowIndex];
}

const Vector3D Matrix3x3::column(size_t aColumnIndex) const
{
	assert(aColumnIndex < 3);

	return Vector3D(row(0)[aColumnIndex], row(1)[aColumnIndex], row(2)[aColumnIndex]);
}