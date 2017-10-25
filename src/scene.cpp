#include "scene.h"

Scene::Scene()
{
	// Set color and depth clear value
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// draw single sided faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	ShowCursor(FALSE);
	glEnable(GL_LIGHTING);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.f, (float)iScreenWidth/iScreenHeight, 1.f, 500.f); //<--- perspective projection matrix

	//Materials
	m_materials.at(0) = Material(sf::Vector3f(0.2f, 0.2f, 0.2f), 1.f, sf::Vector3f(0.8f, 0.8f, 0.8f), 1.0f, sf::Vector3f(1.f, 1.f, 1.f), 1.f, 70.f);
	m_materials.at(1) = Material(sf::Vector3f(0.2f, 0.2f, 0.2f), 1.f, sf::Vector3f(0.8f, 0.8f, 0.8f), 1.0f, sf::Vector3f(0.f, 0.f, 0.f), 1.f, 70.f);

	//Lights
	m_lights.at(0) = Lighting(sf::Vector3f(0.f, 100.f, -0.f), 1.f, sf::Vector3f(1.f, 1.f, 1.f), 1.f, sf::Vector3f(1.f, 1.f, 1.f), 1.f, sf::Vector3f(0.3f, 0.3f, 0.3f), 1.f);

	//Model extractor
	m_modelExtractors.at(0) = new ModelExtractor("ModelWithSpecularLight.txt");
	m_modelExtractors.at(1) = new ModelExtractor("ModelWithoutSpecularLight.txt");

	//Read models from a file
	readModelData(m_modelExtractors.at(0), m_models.at(0)); // Models starting in the first array contain a specular light
	readModelData(m_modelExtractors.at(1), m_models.at(1)); // Models starting in the second array contain no specular light
}

void Scene::readModelData(ModelExtractor* reader, std::vector<Model>& models)
{
	//Add models to the vector
	for (int unsigned i = 0; i < reader->getRefrence().size(); i++)
		models.push_back(Model(reader->getName().at(i),
		reader->getTexture().at(i),
		reader->getPosition().at(i),
		reader->getOrientation().at(i),
		reader->getScale().at(i)));
}

void Scene::update(float fElapsedTime, sf::Vector2i iMousePosition)
{
	// Clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Update camera
	m_camera.update(fElapsedTime, iMousePosition, iScreenWidth, iScreenHeight);

	//Update lights
	m_lights.at(0).setActive(GL_LIGHT0, "model ambient");
}

void Scene::draw()
{
	// Render all of the models in the vector
	for (int unsigned i = 0; i < m_models.at(0).size(); i++)
	{
		m_materials.at(0).initialize(GL_SMOOTH);
		m_models.at(0).at(i).render(true, true);
	}

	// Render all of the models in the vector
	for (int unsigned i = 0; i < m_models.at(1).size(); i++)
	{
		m_materials.at(1).initialize(GL_SMOOTH);
		m_models.at(1).at(i).render(true, true);
	}
}

void Scene::processEvent(sf::Event& e, sf::Window& window)
{
	// Resize event : adjust viewport
	 if (e.type == sf::Event::Resized) glViewport(0, 0, e.size.width, e.size.height);

	 //Process camera events
	 m_camera.processEvent(e);
}

void Scene::setScreenSize(int iScreenWidthIN, int iScreenHeightIN)
{
	iScreenWidth = iScreenWidthIN;
	iScreenHeight = iScreenHeightIN;
}