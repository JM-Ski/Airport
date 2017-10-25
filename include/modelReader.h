#pragma once

#include <cstring>
#include <assert.h>
#include <headers.h>

//!This class is used to read models.
class ModelReader
{
private:
		/*!Our base directory with models.*/
		std::string baseDirectory;

		/*!ASCII code for forward slash.*/
		static const int forwardSlash = 0x2F;

		/*!Vertices = V.*/
		std::vector<float> m_vertices;
		
		/*!Vertex normals = VN.*/
		std::vector<float> m_vertexNormals;

		/*!Texture Coordinates = VT resctricted to UV.*/
		std::vector<float> m_vertexTextureCoordinates;

		/*!Face vertex indices = F X // // .*/
		std::vector<unsigned int> m_faceVertexIndices;
		/*!Face texture indices = F // X // .*/
		std::vector<unsigned int> m_faceTextureIndices;
		/*!Face noraml indices = F // // X .*/
		std::vector<unsigned int> m_faceNormalIndices;   

		/*!Name of a model.*/
		std::string m_modelName;

		/*!Necessary data of vertices for OPENGL in readable format.*/
		std::vector<float> m_vertexTriplets;
		/*!Necessary data of normals for OPENGL in readable format.*/
		std::vector<float> m_vertexNormalTriplets;
		/*!Necessary data of texture coordinates for OPENGL in readable format.*/
		std::vector<float> m_vertexTexturePairs;

public:
		/*Constructor*/
	    /**@param sFileName = Name of a file.*/
		ModelReader(std::string sFileName);
		/*!Desctructor.*/
		~ModelReader(){};

		/*!Read the model.*/
		/**@param sFileName = Name of a file.*/
		void ModelReader::ReadModelObjData(std::string sFileName);

		/*!Processes vertex when encounters V.*/
		/**@param iss = Line input with vertex.*/
		void ProcessVertexLine(std::istringstream& iss);
		/*!Processes vertex when encounters VN.*/
		/**@param iss = Line input with normal.*/
		void ProcessVertexNormalLine(std::istringstream& iss);
		/*!Processes vertex when encounters VT.*/
		/**@param iss = Line input with texture coordinates.*/
		void ProcessVertexTextureLine(std::istringstream& iss);
		/*!Processes face when encounters F.*/
		/**@param iss = Line input with a face.*/
		void ProcessFaceLine(std::istringstream& iss);

		/*!Creates expanded vertices for OpenGl to read.*/
		void CreateExpandedVertices();
		/*!Creates expanded normals for OpenGl to read.*/
		void CreateExpandedNormals();
		/*!Creates expanded texture coordinates for OpenGl to read.*/
		void CreateExpandedTextureCoordinates();

		/*!Read vertices.*/
		/**@return m_vertexTriplets = Returns vector of vertices.*/
		std::vector<float>& GetVertices();
		/*!Read normals.*/
		/**@return m_vertexTriplets = Returns vector of normals.*/
		std::vector<float>& GetNormals();
		/*!Read texture coordinates.*/
		/**@return m_vertexTriplets = Returnes vector of texture coordinates.*/
		std::vector<float>& GetTextureCoordinates();

};

