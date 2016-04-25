#include "SceneNode.h"

SceneNode::SceneNode(PlyModel *pModel,char * nme,int i)
{

	parent=NULL;
	mesh=pModel;
	local_transform=glm::mat4( 1.0 );
	name=nme;
	id=i;


}
SceneNode::~SceneNode(){


}
SceneNode::SceneNode(char * nme,int i)
{

	parent=NULL;
	mesh=NULL;
	local_transform=glm::mat4( 1.0 );
	name=nme;
	id=i;
}
SceneNode::SceneNode(const SceneNode &obj)
{
	mesh=obj.mesh;
	parent=obj.parent;
	local_transform=obj.local_transform;
	children=obj.children;
	name=obj.name;
	id=obj.id;
}
float * SceneNode::getCentroid(){
	return mesh->centroid;


}
SceneNode *  SceneNode::attachChild(SceneNode *  child)
{
	child->parent=this;
	children[child->getId()]=child;

	return this;

}

SceneNode *  SceneNode::detachChild(SceneNode * child)
{
	 std::map<int,SceneNode *>::iterator it;

	
	it = children.find (child->getId());
	if(it!=children.end()){
    children.erase (it);
    child->parent=NULL;
	}
	return child;
}

void SceneNode::scaleLocalTransformMatrix(glm::vec3 scale)
{
	local_transform=glm::scale(local_transform,scale);
}

void SceneNode::translateLocalTransformMatrix(glm::vec3 trans)
{
	glm::mat4 tmp=glm::translate(glm::mat4(1.0f),trans);
	//local_transform=tmp*local_transform;
	local_transform=tmp*local_transform;
}

void SceneNode::rotateLocalTransformMatrix(float angle,glm::vec3 axis)
{
	//local_transform=glm::rotate(local_transform,angle,axis);
	glm::mat4 tmp=glm::rotate(glm::mat4(1.0f),angle,axis);
	local_transform=local_transform*tmp;
}
void SceneNode::setTransformationMatrix(glm::mat4 mat)
{
	local_transform=mat;
}
void SceneNode::printChildren()
{
	 std::map<int,SceneNode *>::iterator it;

	if(children.size()){
		
		for(it=children.begin() ; it != children.end(); it++) 
			{	
				printf("[%d %s],",(it->first),(it->second)->getName());  
			}
	}
	printf("\n");
}
void SceneNode::initTransformationMatrix()
{
	mesh->computeScaleFactor(2);  
	//glm::mat4 m1=glm::translate(glm::mat4(1.0f), glm::vec3(-mesh->centroid[0]*mesh->scale_factor,-mesh->centroid[1]*mesh->scale_factor,-mesh->centroid[2]*mesh->scale_factor));
	glm::mat4 m1=glm::translate(glm::mat4(1.0f), glm::vec3(-mesh->centroid[0],-mesh->centroid[1],-mesh->centroid[2]));
	glm::mat4 m2=glm::scale(glm::mat4(1.0f),glm::vec3(mesh->scale_factor,mesh->scale_factor,mesh->scale_factor));
	local_transform=m2*m1;

}

glm::mat4 SceneNode::getGlobalTransform(){

SceneNode * tmp=parent;
glm::mat4 mat=glm::mat4(1.0)*local_transform;
while(parent){

//mat=parent->getLocalTransform()*mat;
mat=mat*parent->getLocalTransform();
parent=parent->getParent();

}


return mat;

}

void SceneNode::draw()
{
//	printf("%s\n",name);
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(local_transform));
	mesh->draw();
	
	 std::map<int,SceneNode *>::iterator it;

	if(children.size()){

		for(it=children.begin() ; it != children.end(); it++) 
			(it->second)->draw();  

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