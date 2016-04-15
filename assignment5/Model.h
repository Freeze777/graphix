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
PlyModel *plymodel3;
PlyUtility *ply1;
PlyUtility *ply2;
PlyUtility *ply3;
Walls *walls;
int flag=0;
Model(char *filename);
~Model();

void readModelsFromFile(char *filename1,char *filename2,char *filename3);
void drawScene(float dim,float x,float y,float z);
void drawAxis(float dim);
void markPoints(float dim);
void setScaleFactor(float dim); 

};



#endif
