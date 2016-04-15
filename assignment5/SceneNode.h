#ifndef scene_node_h
#define scene_node_h
#include "PlyModel.h"
#include <vector>
#include <algorithm>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class SceneNode
{
private:
	typedef SceneNode * Nodeptr;
	PlyModel * mesh;
	std::vector<Nodeptr> children;
	Nodeptr parent;
	glm::mat4 local_transform;


public:
	SceneNode(PlyModel *pModel);
	SceneNode();
	SceneNode(const SceneNode &obj);
	Nodeptr attachChild(Nodeptr child);
	Nodeptr detachChild(Nodeptr child);
	void scaleLocalTransformMatrix(glm::vec3 scale);
	void translateLocalTransformMatrix(glm::vec3 trans);
	void rotateLocalTransformMatrix(float angle,glm::vec3 axis);
	void setTransformationMatrix(glm::mat4 mat);
	void draw();
	~SceneNode();
	
};


#endif
/*
    #include <glm/vec3.hpp> // glm::vec3
    #include <glm/vec4.hpp> // glm::vec4
    #include <glm/mat4x4.hpp> // glm::mat4
    #include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
    glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
    {
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
    } 
*/