#include "Graph.h"
#include "../Helper ADT's/LinkedQueue.cpp"
#include "../Helper ADT's/LinkedStack.cpp"

//-------------Utility functions-------------//

template <class LabelType>
Vertex<LabelType> * & Graph<LabelType>::getVertexPtr(LabelType v) const {
	//this function assumes we are sure the vertex with value "v" exists
	Vertex<LabelType> * vxPtr = headVertex;

	while (vxPtr){
		if (vxPtr->getData() == v)
			return vxPtr;
		vxPtr = vxPtr->getNextVertex();
	}
}

template <class LabelType>
Vertex<LabelType> * Graph<LabelType>::getPrevVertex(LabelType data) const {
	if (isEmpty()) return nullptr;

	if (headVertex->getData() == data)
		return nullptr;

	Vertex<LabelType> * ptr = headVertex;

	while (ptr->getNextVertex()){
		if (ptr->getNextVertex()->getData() == data)
			return ptr;
		ptr = ptr->getNextVertex();
	}

	return nullptr;
}

//----------------------------------------------------------------------------//

//-------------Constructors-------------//
template <class LabelType>
Graph<LabelType>::Graph(){
	headVertex = tailVertex = nullptr;
	numEdges = 0;
	numVertices = 0;
}

//-----------Main Operations-----------//
template <class LabelType>
bool Graph<LabelType>::add(LabelType vertex1, LabelType vertex2, int edgeWeight) {
	//If Graph is empty
	if (isEmpty()){
		//create two vertices
		Vertex<LabelType> * v1 = new Vertex<LabelType>(vertex1);
		Vertex<LabelType> * v2 = new Vertex<LabelType>(vertex2);
		//Add an edge from v1 to destination vertex2
		v1->addEdge(vertex2, edgeWeight);
		//general vertices in graphs
		v1->setNextVertex(v2);
		//Add an edge from v2 to destination vertex1
		v2->addEdge(vertex1, edgeWeight);
		//set head and tail
		headVertex = v1; tailVertex = v2;
		numEdges++; numVertices = 2;
		return true;
	}

	//if there is already both vertices and are connected, return false
	if (isConnected(vertex1, vertex2)) return false;

	//if both vertices exist but are not connected
	if (isExist(vertex1) && isExist(vertex2) && !isConnected(vertex1, vertex2)){
		Vertex<LabelType> * v = getVertexPtr(vertex1);
		v->addEdge(vertex2, edgeWeight);
		v = getVertexPtr(vertex2);
		v->addEdge(vertex1, edgeWeight);
		numEdges++;
		return true;
	}
	//if only vertex1 exist
	if (isExist(vertex1) && !isExist(vertex2)){
		Vertex<LabelType> * newVx = new Vertex<LabelType>(vertex2);
		newVx->addEdge(vertex1, edgeWeight);
		Vertex<LabelType> * v = getVertexPtr(vertex1);
		v->addEdge(vertex2, edgeWeight);
		tailVertex->setNextVertex(newVx);
		tailVertex = tailVertex->getNextVertex();
		numEdges++; numVertices++;
		return true;
	}

	//if only vertex2 exist
	if (!isExist(vertex1) && isExist(vertex2)){
		Vertex<LabelType> * newVx = new Vertex<LabelType>(vertex1);
		newVx->addEdge(vertex2, edgeWeight);
		Vertex<LabelType> * v = getVertexPtr(vertex2);
		v->addEdge(vertex1, edgeWeight);
		tailVertex->setNextVertex(newVx);
		tailVertex = tailVertex->getNextVertex();
		numEdges++; numVertices++;
		return true;
	}

	//if neither exists
	Vertex<LabelType> * v1 = new Vertex<LabelType>(vertex1);
	Vertex<LabelType> * v2 = new Vertex<LabelType>(vertex2);
	v1->addEdge(vertex2, edgeWeight);
	v2->addEdge(vertex1, edgeWeight);
	tailVertex->setNextVertex(v1);
	tailVertex = tailVertex->getNextVertex();
	tailVertex->setNextVertex(v2);
	tailVertex = tailVertex->getNextVertex();
	numEdges++; numVertices += 2;
	return true;
}

template <class LabelType>
bool Graph<LabelType>::remove(LabelType vertex1, LabelType vertex2){
	if (isEmpty() || !isExist(vertex1) || !isExist(vertex2)) return false;
	//At this point I know I have at least two vertices

	Vertex<LabelType> * v1 = getVertexPtr(vertex1);
	Vertex<LabelType> * v2 = getVertexPtr(vertex2);

	//if two vertices are not connected
	if (!v1->isConnected(vertex2)) return false;
	//At this point I am sure they are connected

	//remove edge from both vertices
	v1->removeEdge(vertex2);
	v2->removeEdge(vertex1);
	
	//if v1 is not connected to any vertex
	if (!v1->HasEdges()){
		if (v1 == headVertex)
			headVertex = headVertex->getNextVertex();
		else if (v1 == tailVertex){
			//move tail one step backward (P.S. I know getPrevVertex won't return nullptr
			//because I know v1 != headVertex and that the vertex1 exists
			tailVertex = getPrevVertex(tailVertex->getData());
			tailVertex->setNextVertex(nullptr);
		}
		//else .. if just a vertes in between graph
		else {
			Vertex<LabelType> * prev = getPrevVertex(vertex1);
			prev->setNextVertex(v1->getNextVertex());
		}
		delete v1;
		v1 = nullptr;
		numVertices--;
	}

	//if v2 is not connected to any vertex
	if (!v2->HasEdges()){
		//if last vertex in Graph (surely same as v2)
		if (headVertex == tailVertex)
			headVertex = tailVertex = nullptr;
		//if v2 is headVertex
		else if (v2 == headVertex)
			headVertex = headVertex->getNextVertex();
		//if v2 is tailVertex
		else if (v2 == tailVertex){
			//move tail one step backward (P.S. I know getPrevVertex won't return nullptr
			//because I know v2 != headVertex and that the vertex2 exists
			tailVertex = getPrevVertex(tailVertex->getData());
			tailVertex->setNextVertex(nullptr);
		}
		//else .. if just a vertes in between graph
		else {
			Vertex<LabelType> * prev = getPrevVertex(vertex2);
			prev->setNextVertex(v2->getNextVertex());
		}
		delete v2;
		v2 = nullptr;
		numVertices--;
	}
	numEdges--;
	return true;
}

template <class LabelType>
void Graph<LabelType>::clear() {
	if (isEmpty()) return;

	Vertex<LabelType> * vx = headVertex;
	Vertex<LabelType> * vxToDelete;

	while (vx){
		vxToDelete = vx;
		vx = vx->getNextVertex();
		delete vxToDelete;
	}

	vx = vxToDelete = headVertex = tailVertex = nullptr;
}

template <class LabelType>
bool Graph<LabelType>::isExist(LabelType vx) const {
	if (isEmpty()) return false;

	Vertex<LabelType> * startPtr = headVertex;
	//while I still have vertices in graph
	while (startPtr){
		if (startPtr->getData() == vx)
			return true;
		startPtr = startPtr->getNextVertex();
	}

	return false;
}

template <class LabelType>
bool Graph<LabelType>::isEmpty() const {
	if (!headVertex) return true;
	return false;
}

template <class LabelType>
bool  Graph<LabelType>::isConnected(LabelType v1, LabelType v2) const {
	//if graph is empty, or there's no v1, or there's no v2
	if (isEmpty() || !isExist(v1) || !isExist(v2)) return false;

	//get Ptr to the vertex having value v1 .. I am sure it exists now,
	//so no need to make sure it is not equal to nullptr
	Vertex<LabelType> * vx1 = getVertexPtr(v1);
	if (vx1->isConnected(v2)) return true;

	//This part is temporarily and should be removed as it will return same
	//result of the above condition, bec. if v1 is connected with v2,
	//then v2 is connected with v1 .. this is a non-directional graph
	Vertex<LabelType> * vx2 = getVertexPtr(v2);
	if (vx2->isConnected(v1)) return true;

	//if not connected
	return false;
}

//-------------Getters-------------//
template <class LabelType>
int Graph<LabelType>::getNumVertices() const {
	return numVertices;
}

template <class LabelType>
int Graph<LabelType>::getNumEdges() const {
	return numEdges;
}

template <class LabelType>
int Graph<LabelType>::getEdgeWeight(LabelType start, LabelType end) const {
	if (!isExist(start) || !isExist(end)) return -1;

	//I made sure it exists, so no need to make sure it is not nullptr
	Vertex<LabelType> * v = getVertexPtr(start);
	if (!v->isConnected(end)) return -1;
	
	return v->getEdgeWeight(end);
}

//-------------Traversals-------------//
template <class LabelType>
void Graph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)){
	if (isEmpty() || !isExist(start)) return;

	if (numVertices == 1){
		visit(start);
		return;
	}

	Vertex<LabelType> * vx = getVertexPtr(start);
	Edge<LabelType> * edge = vx->getFirstEdge();
	LinkedStack<LabelType> S;
	LabelType value;
	
	//push 1st node
	S.push(start);
	vx->incProcessed();
	//Note: if proc. == 1, then it was pushed in stack,
	//if proc. == 0, then it wasn't pushed yet
	
	while (!S.isEmpty()){
		//visit top
		value = S.peek();
		visit(value);
		S.pop();

		//push edges to the current vertex
		while (edge){
			vx = getVertexPtr(edge->getDestination());
			if (vx->getProcessedCount() == 0){
				S.push(edge->getDestination());
				vx->incProcessed();
			}
			edge = edge->getNext();
		}
		//get vertex having value of stack top
		if(S.isEmpty()) break;

		vx = getVertexPtr(S.peek());
		edge = vx->getFirstEdge();
	}

	//reset processed counter
	vx = headVertex;
	while (vx){
		vx->resetProcessed();
		vx = vx->getNextVertex();
	}
}

template <class LabelType>
void Graph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)){
	if (isEmpty() || !isExist(start)) return;

	if (numVertices == 1){
		visit(start);
		return;
	}

	Vertex<LabelType> * vx = getVertexPtr(start);
	Edge<LabelType> * edge = vx->getFirstEdge();
	LinkedQueue<LabelType> Q;
	LabelType value;
	
	//push 1st node
	Q.enqueue(start);
	vx->incProcessed();
	//Note: if proc. == 1, then it was pushed in stack,
	//if proc. == 0, then it wasn't pushed yet
	
	while (!Q.isEmpty()){
		//visit top
		value = Q.peekFront();
		visit(value);
		Q.dequeue();

		//push edges to the current vertex
		while (edge){
			vx = getVertexPtr(edge->getDestination());
			if (vx->getProcessedCount() == 0){
				Q.enqueue(edge->getDestination());
				vx->incProcessed();
			}
			edge = edge->getNext();
		}
		//get vertex having value of stack top
		if(Q.isEmpty()) break;

		vx = getVertexPtr(Q.peekFront());
		edge = vx->getFirstEdge();
	}

	//reset processed counter
	vx = headVertex;
	while (vx){
		vx->resetProcessed();
		vx = vx->getNextVertex();
	}
}