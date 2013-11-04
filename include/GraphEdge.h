#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include <ostream>
#include <fstream>


class GraphEdge {

protected:
  int start;
  int end;
  double cost;

public:
	GraphEdge(int start, int end, double cost) : 
		cost(cost), start(start), end(end) {}
  
	GraphEdge(int start, int end) : 
		cost(1.0), start(start), end(end) {}
  
	GraphEdge() : 
		cost(1.0), start(-1), end(-1) {}

	virtual ~GraphEdge(){}

	int getStart()const{return start;}
	void setStart(int NewIndex){start = NewIndex;}

	int   getEnd()const{return end;}
	void  setEnd(int NewIndex){end = NewIndex;}

	double getCost() const { return cost; }
	void  setCost(double NewCost) { cost = NewCost; }

	bool operator==(const GraphEdge& rhs) {
		return rhs.start == this->start &&
				rhs.end == this->end   &&
				rhs.cost == this->cost;
	}

	bool operator!=(const GraphEdge& rhs) {
		return !(*this == rhs);
	}
};


#endif