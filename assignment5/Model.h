#ifndef model_h
#define model_h

#include "PlyUtility.h"
#include "PlyModel.h"
#include "SceneNode.h"

class Model{

public:

SceneNode * root;
Model();
~Model();

void draw();
SceneNode * createSceneGraph();


};



#endif
