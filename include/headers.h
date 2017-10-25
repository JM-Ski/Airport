#include <stdio.h>
#include <tchar.h>

#define GL_GLEXT_PROTOTYPES 1		// ALLOW USE OF OPEN GL 1.5+ functionality!!!
#define GLEW_STATIC
// this needs to be the first include
#include <SFML\glew.h>		// make 1.5 functions into function pointers - bind at runtime.
#include <SFML\OpenGL.hpp>	// glew BEFORE opengl headers!!!!
#include <SFML\Graphics.hpp>
#include <SFML\wglext.h>
#include <SFML\glext.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "vectorMaths.h"

#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>