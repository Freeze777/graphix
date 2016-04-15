#include "SceneNode.h"

SceneNode::SceneNode(PlyModel *pModel)
{

	parent=NULL;
	mesh=pModel;
	local_transform=glm::mat4( 1.0 );

}
SceneNode::SceneNode()
{

	parent=NULL;
	mesh=NULL;
	local_transform=glm::mat4( 1.0 );
}
SceneNode::SceneNode(const SceneNode &obj)
{
	this->mesh=obj.mesh;
	this->parent=obj.parent;
	this->local_transform=obj.local_transform;
	this->children=obj.children;
}

SceneNode::Nodeptr  SceneNode::attachChild(SceneNode::Nodeptr  child)
{

	child->parent=this;
	children.push_back(child);

	return this;

}

SceneNode::Nodeptr  SceneNode::detachChild(SceneNode::Nodeptr child)
{
	SceneNode::Nodeptr result=NULL;


	std::vector<SceneNode::Nodeptr >::iterator position = find(children.begin(), children.end(), child);

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
	local_transform=glm::translate(local_transform,trans);
}

void SceneNode::rotateLocalTransformMatrix(float angle,glm::vec3 axis)
{
	local_transform=glm::rotate(local_transform,angle,axis);
}
void SceneNode::setTransformationMatrix(glm::mat4 mat)
{
	local_transform=mat;
}
void SceneNode::draw()
{

	
	mesh->draw(0,0,0,0,0);

	std::vector<Nodeptr>::iterator it;
	
	for(it=children.begin() ; it < children.end(); it++) 
         (*it)->draw();  
       
    
}
