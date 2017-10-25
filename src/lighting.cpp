#include "lighting.h"

Lighting::Lighting(sf::Vector3f position, float fPositionW, sf::Vector3f diffuse, float fDiffuseW, sf::Vector3f specular, float fSpecularW, sf::Vector3f ambient, float fAmbientW)
{
	//Light position
	GLfLightPosition[0] = position.x;
	GLfLightPosition[1] = position.y;
	GLfLightPosition[2] = position.z;
	GLfLightPosition[3] = fPositionW;

	//Diffuse
	GLfLightDiffuse[0] = diffuse.x;
	GLfLightDiffuse[1] = diffuse.y;
	GLfLightDiffuse[2] = diffuse.z;
	GLfLightDiffuse[3] = fDiffuseW;

	//Specular
	GLfLightSpecular[0] = specular.x;
	GLfLightSpecular[1] = specular.y;
	GLfLightSpecular[2] = specular.z;
	GLfLightSpecular[3] = fSpecularW;

	//Ambient
	GLfLightAmbient[0] = ambient.x;
	GLfLightAmbient[1] = ambient.y;
	GLfLightAmbient[2] = ambient.z;
	GLfLightAmbient[3] = fAmbientW;

	//Default light model ambient
	GLfLightModelAmbient[0] = ambient.x;
	GLfLightModelAmbient[1] = ambient.y;
	GLfLightModelAmbient[2] = ambient.z;
	GLfLightModelAmbient[3] = fAmbientW;
}

void Lighting::setActive(GLenum iLightNumber, std::string sAmbientType)
{
	//Activate light postion
	glLightfv(iLightNumber, GL_POSITION, GLfLightPosition);
	glLightfv(iLightNumber, GL_DIFFUSE, GLfLightDiffuse);
	glLightfv(iLightNumber, GL_SPECULAR, GLfLightSpecular);

	//Setup ambient light
	if (sAmbientType == "light ambient") glLightfv(iLightNumber, GL_AMBIENT, GLfLightAmbient);
	else if (sAmbientType == "model ambient")
	{
		GLfloat Zero[4];
		Zero[0] = 0.f;
		Zero[1] = 0.f;
		Zero[2] = 0.f;
		Zero[3] = 1.f;

		glLightfv(iLightNumber, GL_AMBIENT, Zero);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GLfLightModelAmbient);	// use global ambient instead
	}

	//Enable the light
	glEnable(iLightNumber);
}