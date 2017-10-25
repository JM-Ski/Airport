#pragma once
#include <headers.h>
#include <array>

//!This class is used to create a lighting.
class Lighting
{
private:
	/*!Light position.*/
	GLfloat GLfLightPosition[4]; 
	/*!Diffuse light.*/
	GLfloat GLfLightDiffuse[4]; 
	/*!Specular light.*/
	GLfloat GLfLightSpecular[4]; 
	/*!Ambient light.*/
	GLfloat GLfLightAmbient[4]; 
	/*!Model ambient light.*/
	GLfloat GLfLightModelAmbient[4];

public:
	/*!Constructor.*/
	Lighting(){};

	/*!Light initializer.*/
	/**@param positionIn = Position of the light.
	*@param fPositionW = 1.f for directional, 0.f for spot light
	*@param diffuse = Diffuse effect.
	*@param fDiffuseW = Leave this at 1.f!!!.
	*@param specular = Specular effect.
	*@param fSpecularW = Leave this at 1.f!!!.
	*@param ambient = Ambient effect.
	*@param fAmbientW = Leave this at 1.f!!!.*/
	Lighting(sf::Vector3f positionIn, float fPositionW, sf::Vector3f diffuse, float fDiffuseW, sf::Vector3f specular, float fSpecularW, sf::Vector3f ambient, float fAmbientW);
	
	/*!Activate the light source.*/
	/**@param iLightNumber = Light number. You can only have maximum of 8 light sources active.
	*@param sAmbientType = Type of an ambient light*/
	void setActive(GLenum iLightNumber, std::string sAmbientType);
};