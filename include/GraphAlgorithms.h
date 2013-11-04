#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include <vector>
#include <list>
#include <queue>
#include <stack>

#include "SparseGraph.h"
#include "PriorityQueue.h"

template <class GraphType>
class GraphSearchDijkstra {

public:
	typedef typename GraphType::EdgeType Edge;
  
public:
	const GraphType& graph;

	std::vector<const Edge*> shortestPathTree;
	std::vector<double> costToThisNode; 
	std::vector<const Edge*> searchFrontier;
	int source;
	int target;

public:
	GraphSearchDijkstra(const GraphType &graph, int source, int target) : 
		graph(graph),
		shortestPathTree(graph.numNodes()),
		costToThisNode(graph.numNodes()),
		searchFrontier(graph.numNodes()),
        source(source),
        target(target) {
			search();     
	}

	GraphSearchDijkstra(const GraphType &graph) : 
		graph(graph),
		shortestPathTree(graph.numNodes()),
		costToThisNode(graph.numNodes()),
		searchFrontier(graph.numNodes()),
        source(0),
        target(0) {
			search();
	}

	void search();
	std::vector<const Edge*> getSPT() const { return shortestPathTree; }
	std::list<int> getPathToTarget() const;
	double getCostToTarget() const { return costToThisNode[target]; }
	double getCostToNode(unsigned int nd) const { return costToThisNode[nd]; }

	double calculateDijskstra(int nd1, int nd2);
};

template<class GraphType>
double GraphSearchDijkstra<GraphType>::calculateDijskstra(int nd1, int nd2) {
	return 0;
}

template <class GraphType>
void GraphSearchDijkstra<GraphType>::search() {
	IndexedPriorityQLow<double> pq(costToThisNode, graph.numNodes());

	pq.insert(source);

	while(!pq.empty()) {
		int nextClosestNode = pq.pop();
		shortestPathTree[nextClosestNode] = searchFrontier[nextClosestNode];

		if(nextClosestNode == target) 
			return;

		GraphType::ConstEdgeIterator ConstEdgeItr(graph, nextClosestNode);

		for(const Edge* pE=ConstEdgeItr.begin(); !ConstEdgeItr.end(); pE=ConstEdgeItr.next()) {
			double newCost = costToThisNode[nextClosestNode] + pE->getCost();

			if(searchFrontier[pE->getEnd()] == 0) {
				costToThisNode[pE->getEnd()] = newCost;
				pq.insert(pE->getEnd());
				searchFrontier[pE->getEnd()] = pE;
			} else if((newCost < costToThisNode[pE->getEnd()]) && (shortestPathTree[pE->getEnd()] == 0)) {
				costToThisNode[pE->getEnd()] = newCost;
				pq.changePriority(pE->getEnd());
				searchFrontier[pE->getEnd()] = pE;
			}
		}
	}
}

template <class GraphType>
std::list<int> GraphSearchDijkstra<GraphType>::getPathToTarget()const {
	std::list<int> path;

	if (target < 0)  
		return path;

	int nd = target;
	path.push_front(nd);

	while ((nd != source) && (shortestPathTree[nd] != 0)) {
		nd = shortestPathTree[nd]->getStart();
		path.push_front(nd);
	}
	return path;
}



template <class GraphType>
class GraphSearchAStar {

private:
	typedef typename GraphType::EdgeType Edge;

private:
	const GraphType& graph;

	std::vector<double> gcosts;
	std::vector<double> fcosts;

	std::vector<const Edge*> shortestPathTree;
	std::vector<const Edge*> searchFrontier;

	int source;
	int target;

	void search();

public:
	GraphSearchAStar(GraphType &graph, int source, int target) : 
	  graph(graph),
      shortestPathTree(graph.NumNodes()),                              
      searchFrontier(graph.NumNodes()),
      gcosts(graph.NumNodes(), 0.0),
      fcosts(graph.NumNodes(), 0.0),
      source(source),
      target(target) {
		search();
	}
 
	std::vector<const Edge*> getSPT() const { return shortestPathTree; }
	std::list<int> getPathToTarget()const;
	double GetCostToTarget() const { return gcosts[target]; }

	double calculateEuclidian(int nd1, int nd2);
	double calculateEuclidianNoisy(int nd1, int nd2);
};

template<class GraphType>
double GraphSearchAStar<GraphType>::calculateEuclidian(int nd1, int nd2) {
	NavGraphNode nod1 = graph.getNode(nd1);
	NavGraphNode nod2 = graph.getNode(nd2);
	return nod1.getPosition().distance(nod2.getPosition());
}

template<class GraphType>
double GraphSearchAStar<GraphType>::calculateEuclidianNoisy(int nd1, int nd2) {
	NavGraphNode nod1 = graph.getNode(nd1);
	NavGraphNode nod2 = graph.getNode(nd2);
	return nod1.getPosition().distance(nod2.getPosition()) * std::rand() * 0.1f;
}

template<class GraphType>
void GraphSearchAStar<GraphType>::search() {
	IndexedPriorityQLow<double> pq(fcosts, graph.numNodes());

	pq.insert(source);

	while(!pq.empty()) {
		int nextClosestNode = pq.pop();

		//move node from the frontier to the spanning tree
		shortestPathTree[nextClosestNode] = searchFrontier[nextClosestNode];

		//if target found exit
		if(nextClosestNode == target) 
			return;

		//now to test all the edges attached to this node
		GraphType::ConstEdgeIterator ConstEdgeItr(graph, nextClosestNode);

		for(const Edge* pE = ConstEdgeItr.begin(); !ConstEdgeItr.end(); pE = ConstEdgeItr.next()) {
			//calculate the heuristic cost from this node to the target (H)                       
			double hcost = calculateEuclidian(target, pE->getEnd());
			//calculate the 'real' cost to this node from the source (G)
			double gcost = gcosts[nextClosestNode] + pE->cost();

			//if node has not been added to the frontier, add it and update
			//the G and F costs
			if(searchFrontier[pE->getEnd()] == NULL) {
				fcosts[pE->getEnd()] = gcost + hcost;
				gcosts[pE->getEnd()] = gcost;
				pq.insert(pE->getEnd());
				searchFrontier[pE->getEnd()] = pE;
			}

			//if this node is already on the frontier but the cost to get here
			//is cheaper than has been found previously, update the node
			//costs and frontier accordingly.
			else if((gcost < gcosts[pE->getEnd()]) && (shortestPathTree[pE->getEnd()] == NULL)) {
				fcosts[pE->getEnd()] = gcost + hcost;
				gcosts[pE->getEnd()] = gcost;
				pq.changePriority(pE->getEnd());
				searchFrontier[pE->getEnd()] = pE;
			}
		}
	}
}

template <class GraphType>
std::list<int> GraphSearchAStar<GraphType>::getPathToTarget() const {
	std::list<int> path;

	if(target < 0) {  
		return path;
	}

	int nd = target;
	path.push_front(nd);
    
	while ((nd != m_iSource) && (m_ShortestPathTree[nd] != 0)) {
		nd = shortestPathTree[nd]->getStart();
		path.push_front(nd);
	}
	return path;
}

#endif