#include "modelReader.h"

ModelReader::ModelReader(std::string filename)
{
	baseDirectory = "assets\\models\\";

	ReadModelObjData(baseDirectory + filename);

	//expand the data suitable for lDrawArrays()
	CreateExpandedVertices();
	CreateExpandedNormals();
	CreateExpandedTextureCoordinates();
}

void ModelReader::ReadModelObjData(std::string filename)
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
		else if (token == "g") { iss >> m_modelName; }
		else if (token == "v") { ProcessVertexLine(iss); }
		else if (token == "vn") { ProcessVertexNormalLine(iss); }
		else if (token == "vt") { ProcessVertexTextureLine(iss); }
		else if (token == "f") { ProcessFaceLine(iss); }
		else
		{
			// ignore any line without these qualifiers
			// ignore rest of line
		}
	}
	modelfile.close();
}

void ModelReader::ProcessVertexLine(std::istringstream& iss)
{
	for (int i = 0; i < 3; i++)
	{
		float fVertex; //Define some float
		iss >> fVertex; //Use the next string in the line and conver it to float
		m_vertices.push_back(fVertex); //Add this to our vector of vertices
	}
}

void ModelReader::ProcessVertexNormalLine(std::istringstream& iss)
{
	for (int i = 0; i < 3; i++)
	{
		float fNormal; //Define some float		
		iss >> fNormal; //Use the next string in the line and conver it to float	
		m_vertexNormals.push_back(fNormal); //Add this to our vector of normals
	}
}

void ModelReader::ProcessVertexTextureLine(std::istringstream& iss)
{
	for (int i = 0; i < 2; i++)
	{
		float fTexture; //Define some float
		iss >> fTexture; //Use the next string in the line and conver it to float
		m_vertexTextureCoordinates.push_back(fTexture); //Add this to our vector of texture coordinates
	}
}

void ModelReader::ProcessFaceLine(std::istringstream& iss)
{	
	static const int forwardSlash = 0x2F; // Slash	

	for (int i = 0; i < 3; i++)
	{
		int iVertexIndex; // Define some int
		iss >> iVertexIndex; //Use the next string in the line and conver it to int
		m_faceVertexIndices.push_back(iVertexIndex - 1); //Add this to our vector of indices

		int lookAhead = iss.peek();  // peek a character		
		if (lookAhead == forwardSlash) // If next character is a forward slash
		{
			iss.get(); //Read the next character with the .get(); operator
			
			int lookAhead2 = iss.peek(); // peek next character		
			if (lookAhead2 == forwardSlash) // If peek next character is also a forward slash
			{
				//We have normal index
				iss.get(); //Read the character (2nd slash)
				int iNormalIndex; // Define some int
				iss >> iNormalIndex; //Use the next string in the line and conver it to int
				m_faceNormalIndices.push_back(iNormalIndex - 1); //Add this to our vector of indices
			}
			else
			{
				//We have texture index  / normal index
				int iTextureIndex; // Define some int
				iss >> iTextureIndex; //Use the next string in the line and conver it to int
				m_faceTextureIndices.push_back(iTextureIndex - 1); //Add this to our vector of indices
				iss.get(); //Read the character (3rd slash)
				int iNormalIndex; // Define some int
				iss >> iNormalIndex; //Use the next string in the line and conver it to int
				m_faceNormalIndices.push_back(iNormalIndex - 1); //Add this to our vector of indices
			}
		}
	}
}

void ModelReader::CreateExpandedVertices()
{
	for (std::vector<unsigned int>::iterator it = m_faceVertexIndices.begin() ; it != m_faceVertexIndices.end(); ++it)
	{
		int vertexNumber = (*it) + 1; // With index + 1 which means that 0 become 1 for calculation purposes
		// 3 floats per triangular face

		int iVertexLimit = vertexNumber * 3; // Scaling the limit by three

		// Add 1 to each index
		// And times that index by 3 which will tell you the last vertex
		//                           1    2    3  <---- Last one 1 x 3 = 3
		// For example, 1 index = v 0.0, 0.0, 1.0
		//							 4	  5	   6 <----- Last one 2 x 3 = 6
		// For example, 2 index = v 1.0, 0.0, 1.0
		
		m_vertexTriplets.push_back(m_vertices.at(iVertexLimit - 3)); // The last onee
		m_vertexTriplets.push_back(m_vertices.at(iVertexLimit - 2)); // The middle one
		m_vertexTriplets.push_back(m_vertices.at(iVertexLimit - 1)); // The first one
	}
}

void ModelReader::CreateExpandedNormals()
{
	for (std::vector<unsigned int>::iterator it = m_faceNormalIndices.begin() ; it != m_faceNormalIndices.end(); ++it)
	{
		//here we have a 1 base index
		// get the face number as 0 indexed
		int iNormalNumber = (*it) + 1;

		int iNormalLimit = iNormalNumber * 3; // Scaling the limit by three

		// Add 1 to each index
		// And times that index by 3 which will tell you the last vertex
		//                           1    2    3  <---- Last one 1 x 3 = 3
		// For example, 1 index = v 0.0, 0.0, 1.0
		//							 4	  5	   6 <----- Last one 2 x 3 = 6
		// For example, 2 index = v 1.0, 0.0, 1.0		
		
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(iNormalLimit - 3)); // The last one
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(iNormalLimit - 2)); // The middle one
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(iNormalLimit - 1)); // The first one
	}
}

void ModelReader::CreateExpandedTextureCoordinates()
{
	for (std::vector<unsigned int>::iterator it = m_faceTextureIndices.begin(); it != m_faceTextureIndices.end(); ++it)
	{
		//here we have a 1 base index
		// get the face number as 0 indexed
		int iTextureNumber = (*it) + 1;

		int iTextureLimit = iTextureNumber * 2; // Scaling the limit by two

		// Add 1 to each index
		// And times that index by 3 which will tell you the last vertex
		//                           1    2  <---- Last one 1 x 2 = 2
		// For example, 1 index = v 0.0, 0.0
		//							 3	  4	 <----- Last one 2 x 2 = 4
		// For example, 2 index = v 1.0, 0.0
				
		m_vertexTexturePairs.push_back(m_vertexTextureCoordinates.at(iTextureLimit - 2)); // The last one b + 0
		m_vertexTexturePairs.push_back(m_vertexTextureCoordinates.at(iTextureLimit - 1)); // The first one   + 1
	}																					 

}

// Access to the vector data
std::vector<float>& ModelReader::GetVertices()
{
	return m_vertexTriplets;
}
std::vector<float>& ModelReader::GetNormals()
{
	return m_vertexNormalTriplets;
}
std::vector<float>& ModelReader::GetTextureCoordinates()
{
	return m_vertexTexturePairs;
}