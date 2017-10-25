#include "modelExtractor.h"

ModelExtractor::ModelExtractor(std::string sFileName)
{
	baseDirectory = "assets\\database\\";

	ReadDatabase(baseDirectory + sFileName);

	//Create a readable format afterwards
	createReadablePositionNumbers();
	createReadableOrientationNumbers();
	createReadableScaleNumbers();
}

void ModelExtractor::ReadDatabase(std::string filename)
{
	std::fstream modelfile(filename, std::ios_base::in);

	if(!modelfile.is_open())
	{
		std::cerr << "File " << filename << " not found.";
		DebugBreak();
		throw std::invalid_argument( "File not found" );
		return;	//ERROR!!!
	}

	std::string line;
	std::string token = "";
	while (getline(modelfile, line))
	{
		std::istringstream iss(line);

		// process the line
		token = "";

		iss >> token; // read to first whitespace
	
		if (token == "#")
		{
			// ignore rest of line
			// iss >> s;
		}
		else if (token == "r") { processModelRefrenceLine(iss); }
		else if (token == "n")	{ processModelNameLine(iss); }
		else if (token == "t") { processModelTextureLine(iss); }
		else if (token == "p") { processModelPositionLine(iss); }
		else if (token == "o") { processModelOrientationLine(iss); }
		else if (token == "s") { processModelScaleLine(iss); }
		else
		{
			// ignore any line without these qualifiers
			// ignore rest of line
		}
	}
	//Close the file
	modelfile.close();
}

void ModelExtractor::processModelRefrenceLine(std::istringstream& iss)
{
	int iRef;
	iss >> iRef;
	modelRefrence.push_back(iRef);
}

void ModelExtractor::processModelNameLine(std::istringstream& iss)
{
	std::string sName;
	iss >> sName;
	modelName.push_back(sName);
}

void ModelExtractor::processModelTextureLine(std::istringstream& iss)
{
	std::string sName;
	iss >> sName;
	textureName.push_back(sName);
}

void ModelExtractor::processModelPositionLine(std::istringstream& iss)
{
	for (int i = 0; i < 3; i++)
	{
		float fPosition; //Define some float		
		iss >> fPosition; //Use the next string in the line and conver it to float	
		position.push_back(fPosition); //Add this to our vector of normals
	}
}

void ModelExtractor::processModelOrientationLine(std::istringstream& iss)
{
	for (int i = 0; i < 3; i++)
	{
		float fOrientation; //Define some float		
		iss >> fOrientation; //Use the next string in the line and conver it to float	
		orientation.push_back(fOrientation); //Add this to our vector of normals
	}
}

void ModelExtractor::processModelScaleLine(std::istringstream& iss)
{
	for (int i = 0; i < 3; i++)
	{
		float fScale; //Define some float		
		iss >> fScale; //Use the next string in the line and conver it to float	
		scale.push_back(fScale); //Add this to our vector of normals
	}
}


void ModelExtractor::createReadablePositionNumbers()
{
	for (std::vector<int>::iterator it = modelRefrence.begin(); it != modelRefrence.end(); ++it)
	{
		int iPositionNumber = (*it); // Model refrence starts with 1!!!!!!

		int iPositionLimit = iPositionNumber * 3; // Scaling the limit by three

		// Add 1 to each index
		// And times that index by 3 which will tell you the last vertex
		//                           1    2  <---- Last one 1 x 2 = 2
		// For example, 1 index = v 0.0, 0.0
		//							 3	  4	 <----- Last one 2 x 2 = 4
		// For example, 2 index = v 1.0, 0.0

		sf::Vector3f newPosition = sf::Vector3f(position.at(iPositionLimit - 3), position.at(iPositionLimit - 2), position.at(iPositionLimit - 1));
		positionVectors.push_back(newPosition);
	}
}

void ModelExtractor::createReadableOrientationNumbers()
{
	for (std::vector<int>::iterator it = modelRefrence.begin(); it != modelRefrence.end(); ++it)
	{
		int iOrientationNumber = (*it); // Model refrence starts with 1!!!!!!

		int iOrientationLimit = iOrientationNumber * 3; // Scaling the limit by three

		// Add 1 to each index
		// And times that index by 3 which will tell you the last vertex
		//                           1    2  <---- Last one 1 x 2 = 2
		// For example, 1 index = v 0.0, 0.0
		//							 3	  4	 <----- Last one 2 x 2 = 4
		// For example, 2 index = v 1.0, 0.0
		
		sf::Vector3f newOrientation = sf::Vector3f(orientation.at(iOrientationLimit - 3), orientation.at(iOrientationLimit - 2), orientation.at(iOrientationLimit - 1));
		orientationVectors.push_back(newOrientation);
	}
}

void ModelExtractor::createReadableScaleNumbers()
{
	for (std::vector<int>::iterator it = modelRefrence.begin(); it != modelRefrence.end(); ++it)
	{
		int iScaleNumber = (*it); // Model refrence starts with 1!!!!!!

		int iScaleLimit = iScaleNumber * 3; // Scaling the limit by three

		// Add 1 to each index
		// And times that index by 3 which will tell you the last vertex
		//                           1    2  <---- Last one 1 x 2 = 2
		// For example, 1 index = v 0.0, 0.0
		//							 3	  4	 <----- Last one 2 x 2 = 4
		// For example, 2 index = v 1.0, 0.0
		
		sf::Vector3f newScale = sf::Vector3f(scale.at(iScaleLimit - 3), scale.at(iScaleLimit - 2), scale.at(iScaleLimit - 1));
		scaleVectors.push_back(newScale);
	}
}


std::vector<int> ModelExtractor::getRefrence()
{
	return modelRefrence;
}

std::vector<std::string> ModelExtractor::getName()
{
	return modelName;
}

std::vector<std::string> ModelExtractor::getTexture()
{
	return textureName;
}

std::vector<sf::Vector3f> ModelExtractor::getPosition()
{
	return positionVectors;
}

std::vector<sf::Vector3f> ModelExtractor::getOrientation()
{
	return orientationVectors;
}

std::vector<sf::Vector3f> ModelExtractor::getScale()
{
	return scaleVectors;
}

