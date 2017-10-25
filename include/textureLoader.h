#pragma once

#include "headers.h"

//!This class is used to read models.
class TextureLoader
{
private:
	/*!Vector of models.*/
	std::vector<TextureLoader*> textures;

	/*!Our base directory with models.*/
	std::string baseDirectory;
public:
	/*!Constructor.*/
	TextureLoader(){};
	/*!Desctructor.*/
	~TextureLoader(){};

	/*!Sets our base directory.*/
	/**@param dir = Our base directory.*/
	void setBaseDirectory(std::string dir);

	/*!Load BMP file.*/
	/**@param sLocation = Location of a file.
	@param &texture = Refrence to the texture.
	@return 0 = Success code.*/
	int LoadBMP(std::string sLocation, GLuint &texture); 
};

