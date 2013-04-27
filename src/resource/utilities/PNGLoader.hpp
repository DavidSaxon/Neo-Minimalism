/******************************************************\
| Function that loads a png image as an OpenGL texture |
|													   |
| @author David Saxon								   |
\******************************************************/

#ifndef OMICRON_RESOURCE_PNGLOADER_H_
#	define OMICRON_RESOURCE_PNGLOADER_H_

#include <iostream>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <png.h>

namespace png_loader {

	//PROTOTYPES
	bool loadPNG(char *name, int &outWidth, int &outHeight,
		bool &outHasAlpha, GLubyte **outData);

} //png_loader

#endif