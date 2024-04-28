#include "Vector3D.h"
#include <cassert>
#include <cmath>

Vector3D::Vector3D(float aX, float aY, float aW) noexcept :
	fBaseVector(aX,aY),
	fW(aW)
{}

Vector3D::Vector3D(Vector2D aVector) noexcept :
	fBaseVector(aVector),
	fW(1.0f)
{}

float Vector3D::operator[](size_t aIndex) const
{
	assert(aIndex < 3);

	return *(reinterpret_cast<const float*>(this) + aIndex); //Its attempting to convert a Vector3D object into a float value.
}

Vector3D::operator Vector2D() const noexcept //This is for when we try to static_cast from Vector3D to Vector2D
{
	return (fBaseVector * (1.0f/ fW));
}

Vector3D Vector3D::operator*(const float aScalar) const noexcept 
{
	return Vector3D(x() * aScalar, y() * aScalar, w() * aScalar);
}

Vector3D Vector3D::operator+(const Vector3D& aOther) const noexcept
{
	return Vector3D(x() + aOther.x(), y() + aOther.y(), w() + aOther.x());
}

float Vector3D::dot(const Vector3D& aOther) const noexcept
{
	return x() * aOther.x() + y() * aOther.y() + w() * aOther.w();
}

std::ostream& operator<<(std::ostream& aOStream, const Vector3D& aVector) //We static_cast the Vector3D down to a Vector2D by using the function Vector2D() found on line 22
{
	return aOStream << static_cast<Vector2D>(aVector);
}