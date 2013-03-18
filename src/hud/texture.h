#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <GL/glew.h>
// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

// Load any image to a mipmapped texture
GLuint loadImageToTexture(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

struct Image_ {
   unsigned long sizeX;
   unsigned long sizeY;
   char *data;
};

#endif
