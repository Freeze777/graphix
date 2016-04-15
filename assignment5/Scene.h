#ifndef scene_h
#define scene_h
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <map>
#include "PlyModel.h"

class Scene{
private:
	typedef GLuint NodeId;
	typedef GLuint u32;
	const NodeId EmptyNodeId = (NodeId)(-1);
 	//std::map<int,SceneNode *> m;
 	std::map<int,u32> m;
 	u32 id_count=0;

	
public:
	Scene();
	~Scene();
		//SceneNode root;

	
	NodeId addNode(NodeId id, const Transform& t);
	void removeNode(NodeId id);

	u32 nodeCount() const;

	void linkNodes(NodeId parentId, NodeId childId);
	void unlinkNode(NodeId childId);

	void transformChild(NodeId childId, const Transform& t);

	// Helper Functions

	void updateLocal(NodeId id);
	void updateGlobal(NodeId id);

	Transform getLocalTransform(NodeId id) const;
	Transform getGlobalTransform(NodeId id) const;

	void setLocalTransform(NodeId id, const Transform& t);
	void setGlobalTransform(NodeId id, const Transform& t);

};




#endif

