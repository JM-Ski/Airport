#include "camera.h"

Camera::Camera()
{
	fFraction = 0.1f; 	//The fraction is a possible speed implementation.
	position = sf::Vector3f(0, 2, 5); 	// Position of the camera
	fHorizontalAngle = 3.14f; // horizontal angle : toward -Z
	fVerticalAngle = 0.0f; // vertical angle : 0, look at the horizon
	fFov = 90.0f; // Initial Field of View	
	fSpeed = 10.0f; // 3 units per second
	fMouseSpeed = 0.030f; // Mouse sensitivity

	e_currentDirection = Direction::None; // current direction that camera is facing 
}

void Camera::update(float fElapsedTime, sf::Vector2i iMousePosition, int iScreenWidth, int iScreenHeight)
{
	//Compute new orientation
	fHorizontalAngle += fMouseSpeed * fElapsedTime * float(iScreenWidth/2 - iMousePosition.x);
	fVerticalAngle += fMouseSpeed * fElapsedTime * float(iScreenHeight/2 - iMousePosition.y);

	//Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = sf::Vector3f(
		cos(fVerticalAngle) * sin(fHorizontalAngle),
		sin(fVerticalAngle),	  
		cos(fVerticalAngle) * cos(fHorizontalAngle));

	// Right vector
	slide = sf::Vector3f(
		sin(fHorizontalAngle - 3.14f/2.0f),
		0,
		cos(fHorizontalAngle - 3.14f/2.0f));

	//Up vector ::  perpendicular to both direction and right
	sf::Vector3f up = m_maths.crossProduct(slide, direction);

	if(e_currentDirection == Direction::Up) position += direction * fElapsedTime * fSpeed;
	if(e_currentDirection == Direction::Down) position -= direction * fElapsedTime * fSpeed;
	if(e_currentDirection == Direction::Left) position -= slide * fElapsedTime * fSpeed;
	if(e_currentDirection == Direction::Right) position += slide * fElapsedTime * fSpeed;
	if (e_currentDirection == Direction::FlyUp) position += sf::Vector3f(0.f, 1.f * fElapsedTime * fSpeed, 0.f);
	if (e_currentDirection == Direction::FlyDown) position += sf::Vector3f(0.f, -1.f * fElapsedTime * fSpeed, 0.f);

	// Camera matrix
	gluLookAt(position.x, position.y, position.z,
			position.x + direction.x, position.y + direction.y, position.z + direction.z,
			up.x, up.y, up.z);
}

void Camera::processEvent(sf::Event& e)
{
	//If player presses the key
	if (e.type == sf::Event::KeyPressed)
	{
		// We will set the direction of the camera that matches the pressed key
		if (e.key.code == sf::Keyboard::W) e_currentDirection = Direction::Up;
		if (e.key.code == sf::Keyboard::S) e_currentDirection = Direction::Down;
		if (e.key.code == sf::Keyboard::D) e_currentDirection = Direction::Right;
		if (e.key.code == sf::Keyboard::A) e_currentDirection = Direction::Left;
		if (e.key.code == sf::Keyboard::Space) e_currentDirection = Direction::FlyUp;
		if (e.key.code == sf::Keyboard::C) e_currentDirection = Direction::FlyDown;
	}

	if (e.type == sf::Event::KeyReleased)
	{
		//Else we want our camera to stop
		if (e.key.code == sf::Keyboard::W) e_currentDirection = Direction::None;
		if (e.key.code == sf::Keyboard::S) e_currentDirection = Direction::None;
		if (e.key.code == sf::Keyboard::D) e_currentDirection = Direction::None;
		if (e.key.code == sf::Keyboard::A) e_currentDirection = Direction::None;
		if (e.key.code == sf::Keyboard::Space) e_currentDirection = Direction::None;
		if (e.key.code == sf::Keyboard::C) e_currentDirection = Direction::None;
	}
}