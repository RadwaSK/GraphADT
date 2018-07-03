#include "Edge.h"

//-------------Constructors-------------//

template <class LabelType>
Edge<LabelType>::Edge(LabelType d){
	destination = d;
	NextEdge = nullptr;
	weight = 0;
}

template <class LabelType>
Edge<LabelType>::Edge(LabelType d, long w){
	destination = d;
	NextEdge = nullptr;
	weight = w;
}

template <class LabelType>
Edge<LabelType>::Edge(LabelType d, Edge<LabelType> * nxtEdge){
	destination = d;
	NextEdge = nxtEdge;
	weight = 0;
}

template <class LabelType>
Edge<LabelType>::Edge(LabelType d, Edge<LabelType> * nxtEdge, long w){
	destination = d;
	NextEdge = nxtEdge;
	weight = w;
}

//-------------Setters-------------//

template <class LabelType>
void Edge<LabelType>::setDestination(LabelType d){
	destination = d;
}


template <class LabelType>
void Edge<LabelType>::setNext(Edge<LabelType> * nxt){
	NextEdge = nxt;
}

template <class LabelType>
void Edge<LabelType>::setWeight(long w) {
	weight = w;
}

//-------------Getters-------------//

template <class LabelType>
LabelType Edge<LabelType>::getDestination() const {
	return destination;
}

template <class LabelType>
Edge<LabelType> * Edge<LabelType>::getNext() const {
	return NextEdge;
}

template<class LabelType>
long Edge<LabelType>::getWeight() const {
	return weight;
}
