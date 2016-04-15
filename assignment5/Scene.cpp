#include <Dunjun/Scene.hpp>
#include <Dunjun/Core/Hashmap.hpp>

#include <cstring>


Scene::Scene()
{
	
}

Scene::~Scene() 
{ 

}



Scene::NodeId Scene::addNode(NodeId parent_id,PlyModel mesh,const Transform& t)
{
	
	id_count++;




	return id_count;
}

void Scene::removeNode(NodeId id)
{
	id_count--;



	data.length--;
}


u32 Scene::nodeCount() const { return id_count; }

void Scene::linkNodes(NodeId parentId, NodeId childId)
{
	unlinkNode(childId);

	const Transform parentTransform = data.global[parentId];
	const Transform childTransform  = data.global[childId];

	// TODO(bill): check to see if this is correct
	const Transform localTransform = parentTransform / childTransform;

	data.local[childId]  = localTransform;
	data.parent[childId] = parentId;

	transformChild(childId, parentTransform);
}

void Scene::unlinkNode(NodeId childId)
{
	//remove link from parent
}

void Scene::transformChild(NodeId id, const Transform& parentTransform)
{
	data.global[id] = parentTransform * data.local[id];

	NodeId child = data.firstChild[id];
	while (isValid(child))
	{
		transformChild(child, data.global[id]);
		child = data.nextSibling[child];
	}
}

void Scene::updateLocal(NodeId id)
{
	NodeId parentId           = data.parent[id];
	Transform parentTransform = {};
	if (isValid(parentId))
		parentTransform = data.global[parentId];
	transformChild(id, parentTransform);
}

void Scene::updateGlobal(NodeId id)
{
	NodeId parentId           = data.parent[id];
	Transform parentTransform = {};
	if (isValid(parentId))
		parentTransform = data.global[parentId];
	data.local[id] = data.global[id] / parentTransform;
	transformChild(id, parentTransform);
}

////////////////

Transform Scene::getLocalTransform(NodeId id) const
{
	return data.local[id];
}

Transform Scene::getGlobalTransform(NodeId id) const
{
	return data.global[id];
}

////////////////

void Scene::setLocalTransform(NodeId id, const Transform& t)
{
	data.local[id] = t;
	updateLocal(id);
}

void Scene::setGlobalTransform(NodeId id, const Transform& t)
{
	data.global[id] = t;
	updateGlobal(id);
}


