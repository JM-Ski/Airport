#include "model.h"

Model::Model(std::string sFileName, std::string sTextureName, sf::Vector3f positionIN, sf::Vector3f orientationIN, sf::Vector3f scaleIN)
{
	//Readers
	m_modelReader = new ModelReader(sFileName);
	m_textureLoader = new TextureLoader();
	m_textureLoader->LoadBMP(sTextureName, m_textureID[0]);

	//Transformations
	position = positionIN;
	orientation = orientationIN;
	
	//Rotation
	m_xiRotationAngle = orientation.x;
	m_yiRotationAngle = orientation.y;
	m_ziRotationAngle = orientation.z;
	
	//Scaling
	scale = scaleIN;
}

void Model::render(bool drawWithNormals, bool drawWithTexture)
{
		glPushMatrix();

	    //Position of our model
	    glTranslatef(position.x, position.y, position.z);
	    
		//Rotate
	    glRotatef(m_xiRotationAngle, 1.f, 0.f, 0.f);
	    glRotatef(m_yiRotationAngle, 0.f, 1.f, 0.f);
	    glRotatef(m_ziRotationAngle, 0.f, 0.f, 1.f);
	    
		//Scale
	    glScalef(scale.x, scale.y, scale.z);
	    
	    // activate and specify pointer to vertex array
	    glEnableClientState(GL_VERTEX_ARRAY);
	    std::vector<float>& vertices = m_modelReader->GetVertices();
	    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	    
	    // pointer to normal array
	    if (drawWithNormals)
	    {
	    	glEnableClientState(GL_NORMAL_ARRAY);
	    	std::vector<float>& normals = m_modelReader->GetNormals();
	    	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	    }
	    
	    if (drawWithTexture)
	    {
	    	glEnable(GL_TEXTURE_2D); // we are using textures
	    	std::vector<float>& textureCoordinates = m_modelReader->GetTextureCoordinates();  
	    	glBindTexture(GL_TEXTURE_2D, m_textureID[0]);
	    
	    	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // glTexCoordPointer will point on an array
	    	glTexCoordPointer(2, GL_FLOAT, 0, &textureCoordinates[0]);
	    }
	    
	    // draw the shape...
	    glDrawArrays(GL_TRIANGLES, 0, (unsigned int)vertices.size() / 3);
	    
	    // deactivate vertex arrays after drawing
	    glDisableClientState(GL_VERTEX_ARRAY);
	    
	    if (drawWithNormals)
	    {
	    	// deactivate
	    	glDisableClientState(GL_NORMAL_ARRAY);
	    }
	    
	    if (drawWithTexture)
	    {
	    	// tidy up
	    	glBindTexture(GL_TEXTURE_2D, NULL);
	    	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	    	glDisable(GL_TEXTURE_2D);
	    }
	    
	    glPopMatrix();
}