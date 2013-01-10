#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <GL/glut.h>

/*data structure for the image used for  texture mapping */
struct Image {
   unsigned long sizeX;
   unsigned long sizeY;
   char *data;
};

struct RGB {
   GLubyte r;
   GLubyte g;
   GLubyte b;
};

//forward declaration of image loading and texture set-up code
GLint LoadTexture(char* image_file);

#endif
