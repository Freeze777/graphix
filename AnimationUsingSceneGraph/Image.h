
#ifndef image_h
#define image_h
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define checkImageWidth 64
#define checkImageHeight 64

class Image {
  public:
  unsigned int sizeX;
  unsigned int sizeY;
  char *data;
  int ImageLoad(char *filename, Image *image);
  Image * loadTexture(char *filename);
  void print();

  ~Image(){

    free(data);
  }

};









/*
void myinit(void)
{
  glClearColor (0.5, 0.5, 0.5, 0.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  Image *image1 = loadTexture();
  if(image1 == NULL){
      printf("Image was not returned from loadTexture\n");
      exit(0);
  }
  makeCheckImage();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  // Create Texture
  glGenTextures(2, texture);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0,
  GL_RGB, GL_UNSIGNED_BYTE, image1->data);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
  checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);


}*/

#endif
