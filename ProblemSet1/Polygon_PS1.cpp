#include "Polygon.h"

float Polygon::getSignedArea() const noexcept
{
	float result = 0;
	for (size_t i = 1; i < fNumberOfVertices; i++)
	{
		result += (getVertex(i).y() + getVertex(i - 1).y()) * (getVertex(i).x() - getVertex(i - 1).x());
	}
	result += (getVertex(0).y() + getVertex(fNumberOfVertices - 1).y()) * (getVertex(0).x() - getVertex(fNumberOfVertices - 1).x());
	return -0.5f*result;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept
{
	Polygon result = *this;

	for (size_t i = 0; i < fNumberOfVertices; i++)
	{
		result.fVertices[i] = static_cast<Vector2D>(aMatrix * fVertices[i]);
	}

	return result;
}