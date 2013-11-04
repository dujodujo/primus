#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <list>
#include <ostream>
#include <fstream>
#include "Util.h"

class GraphNode {  

protected:
	int index;

public:
	GraphNode() : index(-1) {}
	GraphNode(int idx) : index(idx) {}

	virtual ~GraphNode(){}

	int getIndex() const { return index; }
	void setIndex(int newIndex) { index = newIndex; }
};

class NavGraphNode : public GraphNode {

protected:
	Ogre::Vector2 position;

public:
	NavGraphNode() {}

	NavGraphNode(int id, Ogre::Vector2 position) :
		GraphNode(id), position(position) {}

	virtual ~NavGraphNode(){}

	Ogre::Vector2 getPosition() const { return position; }
	void setPosition(Ogre::Vector2 position) { this->position = position; }
};

#endif
