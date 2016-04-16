#ifndef scene_node_h
#define scene_node_h
#include "PlyModel.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> 
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <iostream>
class SceneNode
{
private:

	PlyModel * mesh;
	std::vector<SceneNode *> children;
	SceneNode * parent;
	glm::mat4 local_transform;
	char * name;


public:
	SceneNode(PlyModel *pModel,char * nme);
	SceneNode(char * nme );
	SceneNode(const SceneNode &obj);
	SceneNode * attachChild(SceneNode * child);
	SceneNode * detachChild(SceneNode * child);
	void scaleLocalTransformMatrix(glm::vec3 scale);
	void translateLocalTransformMatrix(glm::vec3 trans);
	void rotateLocalTransformMatrix(float angle,glm::vec3 axis);
	void setTransformationMatrix(glm::mat4 mat);
	void initTransformationMatrix();
	void printChildren();
	void draw();
	~SceneNode();
	char * getName(){return name;}
	SceneNode * getParent(){return parent;}
	std::vector<SceneNode *> getChildren(){return children;}
};


#endif
