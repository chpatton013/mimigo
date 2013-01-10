#include "core/load_image.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>

struct Bitmap {
   unsigned long sizeX;
   unsigned long sizeY;
   char *data;
};

static unsigned int getint(FILE *fp) {
   int c, c1, c2, c3;
   c = getc(fp);
   c1 = getc(fp);
   c2 = getc(fp);
   c3 = getc(fp);
   return ((unsigned int) c) +
      (((unsigned int) c1) << 8) +
      (((unsigned int) c2) << 16) +
      (((unsigned int) c3) << 24);
}

static unsigned int getshort(FILE *fp){
   int c, c1;

   c = getc(fp);
   c1 = getc(fp);

   return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

bool ImageLoad(const char *filename, Bitmap *image) {
   FILE *file;
   unsigned long size;
   unsigned long i;
   unsigned short int planes;
   unsigned short int bpp;
   char temp;

   if ((file = fopen(filename, "rb"))==NULL) {
      printf("File Not Found : %s\n",filename);
      return false;
   }

   fseek(file, 18, SEEK_CUR);
   image->sizeX = getint (file);
   image->sizeY = getint (file);
   size = image->sizeX * image->sizeY * 3;
   planes = getshort(file);
   if (planes != 1) {
      printf("Planes from %s is not 1: %u\n", filename, planes);
      return false;
   }
   bpp = getshort(file);
   if (bpp != 24) {
      printf("Bpp from %s is not 24: %u\n", filename, bpp);
      return false;
   }
   fseek(file, 24, SEEK_CUR);

   image->data = (char *) malloc(size);
   if (image->data == NULL) {
      printf("Error allocating memory for color-corrected image data");
      return true;
   }

   if ((i = fread(image->data, size, 1, file)) != 1) {
      printf("Error reading image data from %s.\n", filename);
      return true;
   }

   for (i=0;i<size;i+=3) {
      temp = image->data[i];
      image->data[i] = image->data[i+2];
      image->data[i+2] = temp;
   }

   fclose(file);
   return 1;
}

void LoadTexture(const char* image_file, int texID) {
   Bitmap* image = new Bitmap();

   if (!ImageLoad(image_file, image)) {
      std::cout << "Error trying to load " << image_file << std::endl;
      exit(1);
   }

   glBindTexture(GL_TEXTURE_2D, texID);
   glTexImage2D(GL_TEXTURE_2D, 0, 3,
         image->sizeX, image->sizeY,
         0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}
