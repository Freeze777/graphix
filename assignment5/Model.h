#ifndef model_h
#define model_h

#include "PlyUtility.h"
#include "PlyModel.h"
#include "Walls.h"
#include "SceneNode.h"

class Model{
GLfloat origin[3] = {0.0, 0.0, 0.0};

public:

SceneNode * root;
Walls *walls;
int flag=0;
Model();
~Model();

void draw();
void drawAxis(float dim);
void markPoints(float dim);


};



#endif
