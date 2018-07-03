#ifndef _GRAPH
#define _GRAPH

#include "Vertex.cpp"
#include "GraphInterface.h"

template<class LabelType>
class Graph : GraphInterface<LabelType>
{
	Vertex<LabelType> * headVertex;
	Vertex<LabelType> * tailVertex;
	int numVertices;
	int numEdges;
	//utility functions
	Vertex<LabelType> * & getVertexPtr(LabelType v) const ;
	Vertex<LabelType> * getPrevVertex(LabelType data) const ;
public:
	//constructors
	Graph();
	//main operations
	bool add(LabelType vertex1, LabelType vertex2, int edgeWeight) ;
	bool remove(LabelType vertex1, LabelType vertex2);
	void clear() ;
	bool isExist(LabelType vertex) const ;
	bool isEmpty() const ;
	bool isConnected(LabelType v1, LabelType v2) const ;
	//getters
	int getNumVertices() const ;
	int getNumEdges() const ;
	int getEdgeWeight(LabelType start, LabelType end) const ;
	//Traversals
	void depthFirstTraversal(LabelType start, void visit(LabelType&));
	void breadthFirstTraversal(LabelType start, void visit(LabelType&));
};

#endif