#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <cmath>
#include <math.h>

#include "GraphNode.h"
#include "GraphEdge.h"
#include "SparseGraph.h"
#include "GraphAlgorithms.h"
#include "Util.h"

class Pathfinder {

protected:
	typedef SparseGraph<NavGraphNode, GraphEdge> NavGraph;
	NavGraph* graph;

	std::list<int> path;
	std::vector<const GraphEdge*> subTree;

	double costToTarget;
	
	double cellWidth;
	double cellHeight;
	int cellSize;
	int x;
	int y;

	int source;
	int target;

public:
	Pathfinder(int x, int y, int cellSize, int source, int target);
	~Pathfinder();

	void createGraph(int x, int y);
	void createPathDijkstra();
	void createGrid(int NumsY, int NumsX);
	void addAllNeighboursToGridNode(int row, int col, int NumsX, int NumsY);
	bool validNeighbour(int x, int y, int NumsX, int NumsY);
	std::list<int> getPath() const { return this->path; }
};


#endif