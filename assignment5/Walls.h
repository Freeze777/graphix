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
float floor_mid[3]={7.50,7.50,7.50};
//float floor_mid[3]={0.0,0.0,0.0};
void draw(float dim);
void readNewTexture(char *filename);
Walls(char *filename);

};

#endif

