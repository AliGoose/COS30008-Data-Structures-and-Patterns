#include "Polygon.h"
#include <stdexcept>

Polygon::Polygon() noexcept:
	fNumberOfVertices(0)
{}

size_t Polygon::getNumberOfVertices() const noexcept
{
	return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex(size_t aIndex) const
{
	if (aIndex < fNumberOfVertices)
	{
		return fVertices[aIndex];
	}
	throw std::out_of_range("Illegal index value.");
}

void Polygon::readData(std::istream& aIStream)
{
	while (aIStream >> fVertices[fNumberOfVertices])
	{
		fNumberOfVertices++;
	}
}

float Polygon::getPerimeter() const noexcept
{
	std::cout << fNumberOfVertices << std::endl;
	float result = 0.0f;
	for (size_t i = 0; i < fNumberOfVertices; i++)
	{
		std::cout << i << std::endl;
		Vector2D IStart = fVertices[i];
		Vector2D IEnd = fVertices[(i + 1) % fNumberOfVertices];
		Vector2D ISegment = IEnd - IStart;

		result += ISegment.length();
	}
	return result;

	/*float perimeter;
	Vector2D segment;
	for (size_t i = 0; i < fNumberOfVertices; i++)
	{
		if (i == fNumberOfVertices - 1)
		{
			Vector2D segment(fVertices[0].x() - fVertices[i].x(), fVertices[0].y() - fVertices[i].y());
		}
		else
		{
			Vector2D segment(fVertices[i + 1].x() - fVertices[i].x(), fVertices[i + 1].y() - fVertices[i].y());
		}
		
		perimeter += segment.length();
	}
	return perimeter;*/
}



Polygon Polygon::scale(float aScalar) const noexcept
{
	Polygon result = *this;
	for (size_t i = 0; i < result.fNumberOfVertices; i++)
	{
		result.fVertices[i] = result.fVertices[i]* aScalar;
	}
	return result;
}
;