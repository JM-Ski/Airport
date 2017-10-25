#pragma once
#include <SFML\Graphics.hpp>

//!This class is used to peroform mathematic calculations.
class VectorMaths
{
public:
	/*!Constructor.*/
	VectorMaths(){};

	/*Destructor*/
	~VectorMaths(){};
	
	/*Cross product*/
	/**@param first = First vector.
	*@param second = Second vector.*/
	sf::Vector3f crossProduct(sf::Vector3f first, sf::Vector3f second);
	
	/*Empty vector*/
	/**@return zero = empty vector such as 0, 0, 0.*/
	sf::Vector3f zero();
	
	/*Default scale*/
	/**@return scale = default scale such as 1, 1, 1.*/
	sf::Vector3f defaultScale();

	/*Default orientation*/
	/**@return orientation = Default orientation such as 0, 0, 0.*/
	sf::Vector3f defaultOrientation();
};