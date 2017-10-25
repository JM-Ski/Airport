#include "material.h"

Material::Material(sf::Vector3f ambient, float fAmbientW, sf::Vector3f diffuse, float fDiffuseW, sf::Vector3f specular, float fSpecularW, float fShininess)
{
	//Ambient
	materialAmbient[0] = ambient.x;
	materialAmbient[1] = ambient.y;
	materialAmbient[2] = ambient.z;
	materialAmbient[3] = fAmbientW;

	//Diffuse
	materialDiffuse[0] = diffuse.x;
	materialDiffuse[1] = diffuse.y;
	materialDiffuse[2] = diffuse.z;
	materialDiffuse[3] = fDiffuseW;

	//SPecular
	materialSpecular[0] = specular.x;
	materialSpecular[1] = specular.y;
	materialSpecular[2] = specular.z;
	materialSpecular[3] = fSpecularW;

	//How shiny our model is
	materialShininess = fShininess;
}

void Material::initialize(GLenum modelIN)
{
	//Initializes the material
	glShadeModel(modelIN);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);
}
