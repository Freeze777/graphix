#ifndef scene_node_h
#define scene_node_h
#include "PlyModel.h"
#include <vector>
#include <string>
#include <map>
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
	std::map<int,SceneNode *> children;
	//std::vector<SceneNode *> children;
	SceneNode * parent;
	glm::mat4 local_transform;
	char * name;
	int id;


public:
	SceneNode(PlyModel *pModel,char * nme,int id);
	SceneNode(char * nme ,int id);
	SceneNode(const SceneNode &obj);
	SceneNode * attachChild(SceneNode * child);
	SceneNode * detachChild(SceneNode * child);
	void scaleLocalTransformMatrix(glm::vec3 scale);
	void translateLocalTransformMatrix(glm::vec3 trans);
	void rotateLocalTransformMatrix(float angle,glm::vec3 axis);
	void setTransformationMatrix(glm::mat4 mat);
	void initTransformationMatrix();
	void printChildren();
	float * getCentroid();
	void draw();
	~SceneNode();
	glm::mat4 getLocalTransform(){return local_transform;}
	glm::mat4 getGlobalTransform();
	char * getName(){return name;}
	int getId(){return id;}
	SceneNode * getParent(){return parent;}
	std::map<int,SceneNode *> getChildren(){return children;}
};


#endif
