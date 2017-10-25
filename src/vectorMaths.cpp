#include "vectorMaths.h"

sf::Vector3f VectorMaths::crossProduct(sf::Vector3f first, sf::Vector3f second)
{
	float X = first.y * second.z - first.z * second.y;
	float Y = first.z * second.x - first.x * second.z;
	float Z = first.x * second.y - first.y * second.x;

	sf::Vector3f c = sf::Vector3f(X, Y, Z);
	return c;
}

sf::Vector3f VectorMaths::zero()
{
	sf::Vector3f zero = sf::Vector3f(0.f, 0.f, 0.f);
	return zero;
}

sf::Vector3f VectorMaths::defaultScale()
{
	sf::Vector3f scale = sf::Vector3f(1.f, 1.f, 1.f);
	return scale;
}

sf::Vector3f VectorMaths::defaultOrientation()
{
	sf::Vector3f orientation = sf::Vector3f(0.f, 0.f, 0.f);
	return orientation;
}