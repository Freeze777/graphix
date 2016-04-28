#ifndef model_h
#define model_h

#include "PlyUtility.h"
#include "PlyModel.h"
#include "Walls.h"

class Model{
GLfloat origin[3] = {0.0, 0.0, 0.0};

public:
PlyModel *plymodel1;
PlyModel *plymodel2;
PlyUtility *ply1;
PlyUtility *ply2;
Walls *walls;

Model(char *filename);
~Model();

void readModelsFromFile(char *filename1,char *filename2);
void drawScene(float dim,float x,float y,float z,bool tex_toggle);
void drawAxis(float dim);
void markPoints(float dim);
void setScaleFactor(float dim); 

};



#endif
