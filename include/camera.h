#pragma once
#include "headers.h"

//!This class is used to create a camera.
class Camera
{
private:	

	/*!The fraction is a possible speed implementation.*/
	float fFraction;

	/*!Camera position.*/
	sf::Vector3f position;
	/*!Horizontal angle.*/
	float fHorizontalAngle;
	/*!Vertical angle.*/
	float fVerticalAngle;
	
	/*!Field of View.*/
	float fFov;
	
	/*!Movement speed of a camera.*/
	float fSpeed;
	/*!Mouse sensitivbity.*/
	float fMouseSpeed;
	
	/*!Direction of a camera.*/
	sf::Vector3f direction;
	/*!Camera moving to the side.*/
	sf::Vector3f slide;

	/*!Direction state of a camera.*/
	enum Direction
	{ 
		Up, /*!< We are going up.*/
		Down, /*!< We are going down.*/
		Left, /*!< We are going left.*/
		Right, /*!< We are going right.*/
		FlyUp, /*!< We fly up.*/
		FlyDown, /*!< We fly down.*/
		None  /*!< None = We are not moving.*/
	};

	/*!Our current direction.*/
	Direction e_currentDirection;
	/*!Maths.*/
	VectorMaths m_maths;

public:
	/*!Constructor.*/
	Camera();

	/*!Update our camera.*/
	/**@param fElapsedTime = Refresh rate.
	*@param iMousePosition = Mouse position.
	*@param iScreenWidth = Screen width.
	*@param iScreenHeight = Screen height.*/
	void update(float fElapsedTime, sf::Vector2i iMousePosition, int iScreenWidth, int iScreenHeight);
	
	/*!Process any events.*/
	/**@param e = Event to be processed.*/
	void processEvent(sf::Event& e);
};