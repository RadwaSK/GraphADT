#include "Vertex.h"

//-------------Constructors-------------//
template <class LabelType>
Vertex<LabelType>::Vertex(LabelType d){
	data = d;
	nextVertex = nullptr; firstEdge = nullptr;
	inDegree = outDegree = processed = 0;
}
//-------------Setters-------------//
template <class LabelType>
void Vertex<LabelType>::setData(LabelType d){
	data = d;
}

template <class LabelType>
void Vertex<LabelType>::setNextVertex(Vertex<LabelType> * v){
	nextVertex = v;
}

template <class LabelType>
void Vertex<LabelType>::setFirstEdge(Edge<LabelType> * Edge){
	if (firstEdge == nullptr){
		inDegree++; outDegree++;
	}
	firstEdge = Edge;
}

//-------------Getters-------------//
template <class LabelType>
LabelType Vertex<LabelType>::getData() const {
	return data;
}

template <class LabelType>
Vertex<LabelType> * Vertex<LabelType>::getNextVertex() const {
	return nextVertex;
}

template <class LabelType>
Edge<LabelType> * Vertex<LabelType>::getFirstEdge() const {
	return firstEdge;
}

template <class LabelType>
int Vertex<LabelType>::getProcessedCount() const {
	return processed;
}

//-------------Functions-------------//
template <class LabelType>
void Vertex<LabelType>::incProcessed(){
	processed++;
}

template <class LabelType>
void Vertex<LabelType>::resetProcessed(){
	processed = 0;
}

template <class LabelType>
bool Vertex<LabelType>::isConnected(LabelType v2) const {
	//if has no edges
	if (!HasEdges()) return false;

	Edge<LabelType> * edgePtr = firstEdge;
	//while I still have edge from this vertex
	while(edgePtr){
		if (edgePtr->getDestination() == v2)
			return true;
		edgePtr = edgePtr->getNext();
	}

	return false;
}

template <class LabelType>
void Vertex<LabelType>::addEdge(LabelType v, int weight){
	inDegree++; outDegree++;

	//if there is no edges
	if (!HasEdges()){
		firstEdge = new Edge<LabelType>(v, weight);
		return;
	}
	
	Edge<LabelType> * edgePtr = firstEdge;
	//to reach pointer to last edge
	while (edgePtr->getNext())
		edgePtr = edgePtr->getNext();
	
	Edge<LabelType> * newEdge = new Edge<LabelType>(v, weight);
	edgePtr->setNext(newEdge);
}

template <class LabelType>
void Vertex<LabelType>::removeEdge(LabelType d){
	if (!HasEdges()) return;

	if (firstEdge->getDestination() == d){
		Edge<LabelType> * EdgeToDelete = firstEdge;
		firstEdge = firstEdge->getNext();
		delete EdgeToDelete;
		EdgeToDelete = nullptr;
		inDegree--; outDegree--;
		return;
	}

	Edge<LabelType> * edgePtr = firstEdge->getNext();
	Edge<LabelType> * PrevEdgePtr = firstEdge;

	while (edgePtr){
		if (edgePtr->getDestination() == d){
			PrevEdgePtr->setNext(edgePtr->getNext());
			delete edgePtr;
			inDegree--; outDegree--;
			return;
		}
	}

}

template <class LabelType>
int Vertex<LabelType>::getEdgeWeight(LabelType destination) const {
	if (!isConnected(destination)) return 0;

	Edge<LabelType> * edgePtr = firstEdge;

	while (edgePtr){
		if (edgePtr->getDestination() == destination)
			return edgePtr->getWeight();
		edgePtr = edgePtr->getNext();
	}

	return 0;
}

template <class LabelType>
bool Vertex<LabelType>::HasEdges() const {
	return firstEdge;
}

//-------------Destructor-------------//
template <class LabelType>
Vertex<LabelType>::~Vertex(){
	if (!HasEdges()) return;

	Edge<LabelType> * edgePtr = firstEdge;
	Edge<LabelType> * EdgeToDelete;

	while (edgePtr){
		EdgeToDelete = edgePtr;
		edgePtr = edgePtr->getNext();
		delete EdgeToDelete;
	}

	firstEdge = edgePtr = EdgeToDelete = nullptr;
}
