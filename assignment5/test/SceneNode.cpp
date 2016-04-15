#include "SceneNode.h"

SceneNode::SceneNode(PlyModel *pModel,char * nme)
{

	parent=NULL;
	mesh=pModel;
	local_transform=glm::mat4( 1.0 );
	name=nme;

}
SceneNode::SceneNode(char * nme)
{

	parent=NULL;
	mesh=NULL;
	local_transform=glm::mat4( 1.0 );
	name=nme;
}
SceneNode::SceneNode(const SceneNode &obj)
{
	this->mesh=obj.mesh;
	this->parent=obj.parent;
	this->local_transform=obj.local_transform;
	this->children=obj.children;
	this->name=obj.name;
}

SceneNode *  SceneNode::attachChild(SceneNode *  child)
{
	child->parent=this;
	children.push_back(child);

	return this;

}

SceneNode *  SceneNode::detachChild(SceneNode * child)
{
	SceneNode * result=NULL;


	std::vector<SceneNode * >::iterator position = find(children.begin(), children.end(), child);

	if (position != children.end())
	{
		result=new SceneNode(*(*position));
		result->parent=NULL;
		children.erase(position);

	}
	return result;
}

void SceneNode::scaleLocalTransformMatrix(glm::vec3 scale)
{
	local_transform=glm::scale(local_transform,scale);
}

void SceneNode::translateLocalTransformMatrix(glm::vec3 trans)
{
	glm::mat4 tmp=glm::translate(glm::mat4(1.0f),trans);
	local_transform=tmp*local_transform;
}

void SceneNode::rotateLocalTransformMatrix(float angle,glm::vec3 axis)
{
	local_transform=glm::rotate(local_transform,angle,axis);
}
void SceneNode::setTransformationMatrix(glm::mat4 mat)
{
	local_transform=mat;
}
void SceneNode::printChildren()
{
	std::vector<SceneNode *>::iterator it;

	if(children.size()){
		
		for(it=children.begin() ; it < children.end(); it++) 
			printf("%s",(*it)->getName());  

	}

}
void SceneNode::initTransformationMatrix()
{
	mesh->computeScaleFactor(2);  
	glm::mat4 m1=glm::translate(glm::mat4(1.0f), glm::vec3(-mesh->centroid[0],-mesh->centroid[1],-mesh->centroid[2]));
	glm::mat4 m2=glm::scale(glm::mat4(1.0f),glm::vec3(mesh->scale_factor,mesh->scale_factor,mesh->scale_factor));
	local_transform=m2*m1;

}

void SceneNode::draw()
{
	printf("%s\n",name);
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(local_transform));
	mesh->draw();
	
	std::vector<SceneNode *>::iterator it;
	if(children.size()){

		for(it=children.begin() ; it < children.end(); it++) 
			(*it)->draw();  

	}
	glPopMatrix();
}
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