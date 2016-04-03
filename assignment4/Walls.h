#ifndef floor_h
#define floor_h
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Image.h"
class Walls{

private:
float v[4][3];
Image *img;

public:
void draw(float dim);
void readNewTexture(char *filename);
Walls(char *filename);

};

#endif

