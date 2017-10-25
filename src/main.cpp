#include <headers.h>
#include "scene.h"


std::string OpenGLGetError()
{
	// opengl doesn't report error conditions, you have
	// to ask for any errors - this will return
	// a string representing any opon gl errors found
	// if all is ok you get the empty string
	// we also have output to cout of any errors and
	// a breakpoint if in debug mode

    std::string s = "";
    GLenum err; 

	err = glGetError();
	if (err == GL_NO_ERROR)
	{
		return s;
	}

	DebugBreak();	//want to know about the error - set a breakpoint here while debugging

    // loop scanning for errors and appending them to a string
    while (err != GL_NO_ERROR)
	{
        switch (err)
		{
		    case GL_NO_ERROR:
                //"No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
                break;

		    case GL_INVALID_ENUM:
                s = s + "GL_INVALID_ENUM "; //"An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
                break;

		    case GL_INVALID_VALUE:
                s = s + "GL_INVALID_VALUE "; //"A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
                break;

		    case GL_INVALID_OPERATION:
                s = s + "GL_INVALID_OPERATION "; //"The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
                break;

		    //case GL_INVALID_FRAMEBUFFER_OPERATION:
            //    s = "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
            //    break;

		    case GL_OUT_OF_MEMORY:
                s = s + "GL_OUT_OF_MEMORY "; //"There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
                break;

		    case GL_STACK_UNDERFLOW:
                s = s + "GL_STACK_UNDERFLOW";	//"An attempt has been made to perform an operation that would cause an internal stack to underflow.";
                break;

		    case GL_STACK_OVERFLOW:
                s = s + "GL_STACK_OVERFLOW"; //"An attempt has been made to perform an operation that would cause an internal stack to overflow.";
                break;
	    }
		// get next error, if any
		err = glGetError();
	}
	// return the error messages as a single string
	// and write out to console

	std::cout << "Open GL Error " << s << std::endl;

	return s;
}

int main()
{
	// better to use const int rather than define
	const float k_fRefreshRate = 0.01f;

	// Create a clock for measuring elapsed time
	sf::Clock clock;

	// SFML-2.3.2 depth buffering fails unless we create a more specific window - as below
	int iDepthBits = 24;
	int iStencilBits = 8;
	int iAntiAliasingLevel = 2;
	int iMajorVersion = 3;
	int iMinorVersion = 3;

	//Get desktop resolution
	sf::VideoMode iScreenSize = sf::VideoMode::getDesktopMode();

	sf::ContextSettings context(iDepthBits, iStencilBits, iAntiAliasingLevel, iMajorVersion, iMinorVersion)	;
	sf::Window window(sf::VideoMode(iScreenSize.width, iScreenSize.height, 32), "SFML Window", sf::Style::None, context);

	// check we got the settings we need
	sf::ContextSettings windowSettings = window.getSettings();

	//Scene
	Scene m_scene;

	//Set the screen size
	m_scene.setScreenSize(iScreenSize.width, iScreenSize.height);

	// check for any errors
	OpenGLGetError();

	// Start game loop
	while (window.isOpen())
	{
		sf::Event event; // Process events
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close(); // Close window : exit
			
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) window.close(); // Escape key : exit	
			else
			{
				m_scene.processEvent(event, window);
			}
		}

		//Elapsed time
		float fElapsedTime = clock.getElapsedTime().asSeconds();

		if(fElapsedTime > k_fRefreshRate) 
		{
			// Get mouse position relative to the window
			sf::Vector2i iMousePosition = sf::Mouse::getPosition(window);
	
			//Set mouse position relative to the window
			sf::Mouse::setPosition(sf::Vector2i(iScreenSize.width / 2, iScreenSize.height / 2), window);

			//Update the scene
			m_scene.update(k_fRefreshRate, iMousePosition);

			//Update the draw
			m_scene.draw();

			//Restart the clock
			clock.restart();
		    // Finally, display rendered frame on screen
			window.display();
		}
	}
	return EXIT_SUCCESS;
}