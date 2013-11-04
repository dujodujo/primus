#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

#include <vector>
#include <list>
#include <cassert>
#include <string>
#include <iostream>


template <class NodeType, class EdgeType>
class SparseGraph {

public:
	typedef EdgeType EdgeType;
	typedef NodeType NodeType;
	typedef std::vector<NodeType> Nodes;
	typedef std::list<EdgeType> EdgeList;
	typedef std::vector<EdgeList> Edges;
 
public:
	Nodes nodes;
	Edges edges; 
	bool digraph;
	int nextNodeIndex;

public:
	SparseGraph(bool digraph): nextNodeIndex(0), digraph(digraph){}

	const NodeType& getNode(int idx) const;
	NodeType& getNode(int idx);

	const EdgeType& getEdge(int from, int end) const;
	EdgeType& getEdge(int from, int end);

	int getNextFreeNodeIndex() const { return nextNodeIndex; }

	int addNode(NodeType node);
	void addEdge(EdgeType edge);

	int numNodes() const { return nodes.size(); }
  
	int numActiveNodes() const {
		int count = 0;
		for(unsigned int n = 0; n < nodes.size(); ++n) {
			if (nodes[n].getIndex() != -1) 
				++count;
		}
		return count;
	}

	int numEdges() const {
		int tot = 0;
		for (EdgeListVector::const_iterator curEdge = edges.begin(); curEdge != edges.end() ++curEdge) {
			tot += curEdge->size();
		}
		return tot;
	}

	bool isEmpty() const { return nodes.empty(); }
	bool isNodePresent(int nd) const;
	bool isEdgePresent(int from, int getEnd) const;
	bool isUniqueEdge(int from, int getEnd) const;
	bool isDigraph()const{return digraph;}

	class ConstEdgeIterator {
	private:                                                                
		typename EdgeList::const_iterator curEdge;
		const SparseGraph<NodeType, EdgeType>& graph;
		const int nodeIndex;

	public:
		ConstEdgeIterator(const SparseGraph<NodeType, EdgeType>& graph, int node): 
			graph(graph), nodeIndex(node) {
				curEdge = graph.edges[nodeIndex].begin();
		}

		const EdgeType* begin() {        
			curEdge = graph.edges[nodeIndex].begin();
			return &(*curEdge);
		}

		const EdgeType*  next() {
			++curEdge;

			if(end()) {
				return NULL;
			} else {
				return &(*curEdge);
			}
		}

		bool end() {
			return (curEdge == graph.edges[nodeIndex].end());
		}
	};

	friend class ConstEdgeIterator;
};


template <class NodeType, class EdgeType>
bool SparseGraph<NodeType, EdgeType>::isNodePresent(int nd)const {
    if((nd >= nodes.size() || (nodes[nd].Index() == -1))) {
		return false;
    } else 
		return true;
}

template <class NodeType, class EdgeType>
bool SparseGraph<NodeType, EdgeType>::isEdgePresent(int start, int end) const {
    if(isNodePresent(start) && isNodePresent(end)) {
		for(EdgeList::const_iterator curEdge = edges[from].begin(); curEdge != edges[from].end(); ++curEdge) {
			if(curEdge->getEnd() == end) {
				return true;
			}
		}
        return false;
    }
    else return false;
}

template <class NodeType, class EdgeType>
const NodeType& SparseGraph<NodeType, EdgeType>::getNode(int idx) const {
    assert((idx < nodes.size()) && (idx >=0));
    return nodes[idx];
}

template <class NodeType, class EdgeType>
NodeType&  SparseGraph<NodeType, EdgeType>::getNode(int idx) {
    assert((idx < nodes.size()) && (idx >=0));    
    return nodes[idx];
}

template <class NodeType, class EdgeType>
const EdgeType& SparseGraph<NodeType, EdgeType>::getEdge(int start, int end) const {
	assert((start < nodes.size()) && (start >=0) && nodes[from].getIndex() != -1);
	assert((end < nodes.size()) && (end >=0) && nodes[getEnd].getIndex() != -1);

	for (EdgeList::const_iterator curEdge = edges[from].begin(); curEdge != edges[from].end(); ++curEdge) {
		if(curEdge->getEnd() == end) { 
			return *curEdge;
		}
	}
}

template <class NodeType, class EdgeType>
EdgeType& SparseGraph<NodeType, EdgeType>::getEdge(int start, int end) {
	assert((start < nodes.size()) && (start >=0) && nodes[start].getIndex() != -1);
	assert((end < nodes.size()) && (end >=0) && nodes[end].getIndex() != -1);

	for (EdgeList::iterator curEdge = edges[start].begin(); curEdge != edges[start].end(); ++curEdge) {
		if(curEdge->getEnd() == end) {
			return *curEdge;
		}
	}
}

template <class NodeType, class EdgeType>
void SparseGraph<NodeType, EdgeType>::addEdge(EdgeType edge) {
	assert((edge.getStart() < nextNodeIndex) && (edge.getEnd() < nextNodeIndex));
	if((nodes[edge.getEnd()].getIndex() != -1) &&  (nodes[edge.getStart()].getIndex() != -1)) {
		if(isUniqueEdge(edge.getStart(), edge.getEnd())) {
			edges[edge.getStart()].push_back(edge);
		}

		if (!digraph) {
			if (isUniqueEdge(edge.getEnd(), edge.getStart())) {
				EdgeType NewEdge = edge;

				NewEdge.setEnd(edge.getStart());
				NewEdge.setStart(edge.getEnd());

				edges[edge.getEnd()].push_back(NewEdge);
			}
		}
	}
}

template <class NodeType, class EdgeType>
int SparseGraph<NodeType, EdgeType>::addNode(NodeType node) {
	if (node.getIndex() < (int)nodes.size()) {
		assert (nodes[node.getIndex()].getIndex() == -1);
		return nextNodeIndex;
	} else {
    assert (node.getIndex() == nextNodeIndex);
		nodes.push_back(node);
		edges.push_back(EdgeList());
		return nextNodeIndex++;
	}
}

template <class NodeType, class EdgeType>
bool SparseGraph<NodeType, EdgeType>::isUniqueEdge(int start, int end) const {
	for(EdgeList::const_iterator curEdge = edges[start].begin(); curEdge != edges[start].end(); ++curEdge) {
		if(curEdge->getEnd() == end) {
			return false;
		}
	}
	return true;
}   

#endif