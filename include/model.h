#pragma once
#include "headers.h"
#include "modelReader.h"
#include "textureLoader.h"

//!This class is used to create a model.
class Model
{
private:

	/*!Position of the model.*/
	sf::Vector3f position;
	/*!Orientation of the model.*/
	sf::Vector3f orientation;
	/*!Scale of the model.*/
	sf::Vector3f scale;

	
	/*!Rotation in X axis.*/
	GLuint m_xiRotationAngle;
	/*!Rotation in Y axis.*/
	GLuint m_yiRotationAngle;
	/*!Rotation in Z axis.*/
	GLuint m_ziRotationAngle;

	/*!A buffer of texture.*/
	GLuint m_textureID[2];

	/*!Model reader.*/
	ModelReader* m_modelReader;
	/*!Texture loader.*/
	TextureLoader* m_textureLoader;
public:
	/*!Constructor.*/
	Model(){};
	/*!Destructor.*/
	~Model(){};
	/*!Model constructor.*/
	/**@param sFileName = Name of a file.
	  *@param sTextureName = Texture name.
	  *@param postionIN = Position of a model.
	  *@param orientationIN = Orientation of a model.
	  *@param scaleIN = Scale of a model.*/
	Model(std::string sFileName, std::string sTextureName, sf::Vector3f positionIN, sf::Vector3f orientationIN, sf::Vector3f scaleIN);

	/*!Model rendering.*/
	/**@param drawWithNormals = Whether or not to draw with normals.
	*param drawWithTexture = Whether or not to draw with textures.*/
	void render(bool drawWithNormals, bool drawWithTexture);
};