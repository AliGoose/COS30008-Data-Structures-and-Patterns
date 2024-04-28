#include "Matrix3x3.h"

#include <cassert>
#include <cmath>

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept
{
	Vector3D row1 = row(0); //Discoruaged to use direct access, always use accessor if possible, row().
	Vector3D row2 = row(1); //Only use accessor methods if they have an assertion in them
	Vector3D row3 = row(2);
	Vector3D col1 = aOther.column(0);
	Vector3D col2 = aOther.column(1);
	Vector3D col3 = aOther.column(2);
	return Matrix3x3(
						Vector3D(row1.dot(col1), row1.dot(col2), row1.dot(col3)),
						Vector3D(row2.dot(col1), row2.dot(col2), row2.dot(col3)),
						Vector3D(row3.dot(col1), row3.dot(col2), row3.dot(col3)));
}

float Matrix3x3::det() const noexcept
{
	Vector3D row1 = row(0); //Discoruaged to use direct access, always use accessor if possible, row().
	Vector3D row2 = row(1); //Result should be initalised 0.0f
	Vector3D row3 = row(2);

	float lResult = 0.0f;
	lResult = row1.x() * ((row2.y() * row3.w()) - (row2.w() * row3.y())) - row1.y() * ((row2.x() * row3.w()) - (row2.w() * row3.x())) + row1.w() * ((row2.x() * row3.y()) - (row2.y() * row3.x()));
	return	lResult;
}

bool Matrix3x3::hasInverse() const noexcept
{
	return det() != 0.0f;
}

Matrix3x3 Matrix3x3::transpose() const noexcept
{
	return Matrix3x3(column(0), column(1), column(2));
}

Matrix3x3 Matrix3x3::inverse() const
{
	assert(hasInverse());
	Vector3D row1 = row(0); //Discoruaged to use direct access, always use accessor if possible, row().
	Vector3D row2 = row(1); //Result should be initalised 0.0f
	Vector3D row3 = row(2);
	return  (Matrix3x3(
						Vector3D((row2.y() * row3.w()) - (row2.w() * row3.y()), (row1.w() * row3.y()) - (row1.y() * row3.w()), (row1.y() * row2.w()) - (row1.w() * row2.y())),
						Vector3D((row2.w() * row3.x()) - (row2.x() * row3.w()), (row1.x() * row3.w()) - (row1.w() * row3.x()), (row1.w() * row2.x()) - (row1.x() * row2.w())),
						Vector3D((row2.x() * row3.y()) - (row2.y() * row3.x()), (row1.y() * row3.x()) - (row1.x() * row3.y()), (row1.x() * row2.y()) - (row1.y() * row2.x())) )* (1 / det()));
}

std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix)
{
	return aOStream << "[" << aMatrix.fRows[0] << "," << aMatrix.fRows[1] << "," << aMatrix.fRows[2] << "]";   //Discoruaged to use direct access, always use accessor if possible, row().
}