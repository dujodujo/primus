#include "Pathfinder.h"

Pathfinder::Pathfinder(int x, int y, int cellSize, int source, int target) :
  cellWidth(0),
  cellHeight(0),
  cellSize(cellSize),
  x(0),
  y(0),
  source(source),
  target(target),
  costToTarget(0.0) {
	graph = new NavGraph(false);
}

Pathfinder::~Pathfinder(){delete graph;}

void Pathfinder::createGraph(int x, int y) {
	createGrid(x, y);
}

bool Pathfinder::validNeighbour(int x, int y, int NumCellsX, int NumCellsY) {
	return !((x < 0) || (x >= NumCellsX) || (y < 0) || (y >= NumCellsY));
}

void Pathfinder::createGrid(int numCellsY, int numCellsX) {
	double cellWidth =  cellSize / numCellsY;
	double cellHeight = cellSize / numCellsX;

	double midX = cellWidth / 2;
	double midY = cellHeight / 2;

	for (int row=0; row < numCellsY; ++row) {
		for (int col=0; col < numCellsX; ++col) {
			graph->addNode(NavGraphNode(graph->getNextFreeNodeIndex(), 
				Ogre::Vector2(midX * (cellWidth * col), midY * (cellHeight * row))));
		}
	}

	for (int row = 0; row < numCellsY; ++row) {
		for (int col = 0; col < numCellsX; ++col) {
			addAllNeighboursToGridNode(row, col, numCellsX, numCellsY);
		}
	}
}  

void Pathfinder::addAllNeighboursToGridNode(int row, int col, int numCellsX, int numCellsY) {   
	for (int i=-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			int nodeX = col+j;
			int nodeY = row+i;

			if( (i == 0) && (j==0))
				continue;

			if(validNeighbour(nodeX, nodeY, numCellsX, numCellsY)) {
				Ogre::Vector2 positionNode = graph->getNode(row * numCellsX + col).getPosition();
				Ogre::Vector2 positionNodeNext = graph->getNode(nodeY * numCellsX  + nodeX).getPosition();

				double distance = positionNode.distance(positionNodeNext);

				NavGraph::EdgeType NewEdge(row * numCellsX + col, nodeY * numCellsX + nodeX);
				graph->addEdge(NewEdge);

				graph->getNode(row * numCellsX * col);

				if(!graph->isDigraph()) {
					NavGraph::EdgeType NewEdge(nodeY * numCellsX + nodeX, row * numCellsX + col, distance);
					graph->addEdge(NewEdge);
				}
			}
		}
	}
}

void Pathfinder::createPathDijkstra() {
  GraphSearchDijkstra<NavGraph> djk(*graph, source, target);
  path = djk.getPathToTarget();
  subTree = djk.getSPT();
  costToTarget = djk.getCostToTarget();
}