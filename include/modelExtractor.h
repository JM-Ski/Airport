#pragma once

#include "headers.h"

//!This class is used to extract information about the model from a file.
class ModelExtractor
{
private:
	/*!Our base directory with text files.*/
	std::string baseDirectory;

	/*!Model ID.*/
	std::vector<int> modelRefrence;
	/*!Model name.*/
	std::vector<std::string> modelName;
	/*!Model texture name.*/
	std::vector<std::string> textureName;
	
	/*!Position of the model.*/
	std::vector<float> position;
	/*!Orientation of the model.*/
	std::vector<float> orientation;
	/*!Scale of the model.*/
	std::vector<float> scale;
	
	/*!Vector with positions.*/
	std::vector<sf::Vector3f> positionVectors;
	/*!Vector with orientations.*/
	std::vector<sf::Vector3f> orientationVectors;
	/*!Vector with scales.*/
	std::vector<sf::Vector3f> scaleVectors;

public:
	/*!Constructor.*/
	/**@param fileName = Name of a file.*/
	ModelExtractor(std::string fileName);
	
	/*!Desctructor.*/
	~ModelExtractor(){};

	/*!Read a text file*/
	/**@param sFileName = Name of a file.*/
	void ReadDatabase(std::string sFileName);

	/*!Processes model ID when encounters R.*/
	/**@param iss = Line input with ID.*/
	void processModelRefrenceLine(std::istringstream& iss);
	/*!Processes model name when encounters N.*/
	/**@param iss = Line input with the name.*/
	void processModelNameLine(std::istringstream& iss);
	/*!Processes model texture when encounters T.*/
	/**@param iss = Line input with the texture.*/
	void processModelTextureLine(std::istringstream& iss);
	/*!Processes model position when encounters P.*/
	/**@param iss = Line input with the position.*/
	void processModelPositionLine(std::istringstream& iss);
	/*!Processes model orientation when encounters O.*/
	/**@param iss = Line input with the orientation.*/
	void processModelOrientationLine(std::istringstream& iss);
	/*!Processes model scale when encounters S.*/
	/**@param iss = Line input with the scale.*/
	void processModelScaleLine(std::istringstream& iss);

	/*!Creates expanded positions for OpenGl to read.*/
	void createReadablePositionNumbers();
	/*!Creates expanded orientations for OpenGl to read.*/
	void createReadableOrientationNumbers();
	/*!Creates expanded scales for OpenGl to read.*/
	void createReadableScaleNumbers();

	/*!Get ID.*/
	/**@return modelRefrence = Returns vector of IDs.*/
	std::vector<int> getRefrence();
	/*!Get model name.*/
	/**@return modelName = Returns vector of names.*/
	std::vector<std::string> getName();
	/*!Get texture.*/
	/**@return textureName = Returns vector of textures.*/
	std::vector<std::string> getTexture();
	/*!Get position.*/
	/**@return positionVectors = Returns vector of positions.*/
	std::vector<sf::Vector3f> getPosition();
	/*!Get orientation.*/
	/**@return orientationVectors = Returns vector of orientations.*/
	std::vector<sf::Vector3f> getOrientation();
	/*!Get scale.*/
	/**@return scaleVectors = Returns vector of scales.*/
	std::vector<sf::Vector3f> getScale();

};