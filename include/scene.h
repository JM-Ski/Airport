#pragma once

#include "headers.h"
#include "model.h"
#include "camera.h"
#include "lighting.h"
#include <array>
#include "modelExtractor.h"
#include "material.h"

//!This class is used to render a scene.
class Scene
{
private:

	/*!Screen width.*/
	int iScreenWidth;

	/*!Screen height.*/
	int iScreenHeight;

	/*!Our camera.*/
	Camera m_camera;

	//These are only used to create a UML diagram in Doxygen!
	Model m_model;
	Lighting m_light;
	Material m_material;
	ModelExtractor m_modelExtractor; 

	/* An array of models*/
	std::array<std::vector<Model>, 2> m_models; 
	/* An array of lights*/
	std::array<Lighting, 1> m_lights;
	/* An array of materials*/
	std::array<Material, 2> m_materials;
	/* An array of readers*/
	std::array<ModelExtractor*, 2> m_modelExtractors;
	/* Maths class*/
	VectorMaths m_maths;

public:
	/* Constructor*/
	Scene();
	/*!Update the scene.*/
	/**@param fElapesedTime = Refresh rate.
	  *@param iMousePosition = Position of a mouse.*/
	void update(float fElapsedTime, sf::Vector2i iMousePosition);
	
	/* Draw*/
	void draw();
	/*Process any events*/
	/**@param e = event.
	*@param window = Our window.*/
	void processEvent(sf::Event& e, sf::Window& window);
	/*Set the screen size*/
	/**@param iScreenWidth = Screen width.
	*@param iScreenHeight = Screen height.*/
	void setScreenSize(int iScreenWidth, int iScreenHeight);
	/*Read and populate model with data*/
	/**@param reader = Read the model data.
	*@param models = Vector of models.*/
	void readModelData(ModelExtractor* reader, std::vector<Model>& models);
};