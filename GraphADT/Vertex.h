#ifndef _VERTEX
#define _VERTEX

#include "Edge.cpp"

template <class LabelType>
class Vertex
{
	LabelType data;
	Vertex<LabelType> * nextVertex;
	int inDegree, outDegree;
	Edge<LabelType> * firstEdge;
	int processed;
public:
	//constructors
	Vertex(LabelType d);
	//setters
	void setData(LabelType d);
	void setNextVertex(Vertex<LabelType> * v);
	void setFirstEdge( Edge<LabelType> * Edge );
	//getters
	LabelType getData() const ;
	Vertex<LabelType> * getNextVertex() const ;
	Edge<LabelType> * getFirstEdge() const ;
	int getProcessedCount() const ;
	//another functions
	void incProcessed();
	void resetProcessed();
	bool isConnected(LabelType v2) const ;
	void addEdge(LabelType v, int weight);
	void removeEdge(LabelType d);
	int getEdgeWeight(LabelType destination) const ;
	bool HasEdges() const ;
	//destructor
	~Vertex();
};

#endif