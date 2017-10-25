#include "headers.h"

//!This class is used to create a material.
class Material
{
private:
	/*!Material ambient effect.*/
	GLfloat materialAmbient[4];
	/*!Material diffuse effect.*/
	GLfloat materialDiffuse[4];
	/*!Material specular effect.*/
	GLfloat materialSpecular[4];
	/*!Material shininess effect.*/
	GLfloat materialShininess;
public:
	/*!Constructor.*/
	Material(){};

	/*!Material initializer.*/
	/**@param ambient = Ambient effect.
	*@param fAmbientW = Leave this at 1.f!!!.
	*@param diffuse = Diffuse effect.
	*@param fDiffuseW = Leave this at 1.f!!!.
	*@param specular = Specular effect.
	*@param fSpecularW = Leave this at 1.f!!!.
	*@param fShininess = Shniy effect.*/
	Material(sf::Vector3f ambient, float fAmbientW, sf::Vector3f diffuse, float fDiffuseW, sf::Vector3f specular, float fSpecularW, float fShininess);
	
	/*!Activates the material for the particular model.*/
	/**@param modelIN = Specific model.*/
	void initialize(GLenum modelIN);
};