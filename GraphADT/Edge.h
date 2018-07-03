#ifndef _EDGE
#define _EDGE

template <class LabelType>
class Edge
{
	LabelType destination;
	Edge<LabelType> * NextEdge;	//ptr to next Edge
	long weight;				//weight of Edge
public:
	//constructors
	Edge(LabelType d);
	Edge(LabelType d, long w);
	Edge(LabelType d, Edge<LabelType> * nxtEdge);
	Edge(LabelType d, Edge<LabelType> * nxtEdge, long w);
	//setters
	void setDestination(LabelType d);
	void setNext(Edge<LabelType> * nxt);
	void setWeight(long w);
	//getters
	LabelType getDestination() const ;
	Edge<LabelType> * getNext() const ;
	long getWeight() const ;
};

#endif