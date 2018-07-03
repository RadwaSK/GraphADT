/** An interface for the ADT undirected, connected graph.
@file GraphInterface.h */
#ifndef _GRAPH_INTERFACE
#define _GRAPH_INTERFACE

template<class LabelType>
class GraphInterface
{
public:
	
	//Gets the number of vertices in this graph.
	virtual int getNumVertices() const = 0;
	
	//Gets the number of edges in this graph.
	virtual int getNumEdges() const = 0;
	
	/* Creates an undirected edge in this graph between two vertices
	that have the given labels. If such vertices do not exist, creates
	them and adds them to the graph before creating the edge.
	@param edgeWeight The integer weight of the edge.
	@return True if the edge is created, or false otherwise..
	when an edge already exists */
	virtual bool add(LabelType vertex1, LabelType vertex2, int edgeWeight) = 0;
	
	/** Removes an edge from this graph. If a vertex has no other edges,
	it is removed from the graph since this is a connected graph.
	@return True if the edge is removed, or false otherwise.. if no edge exists */
	virtual bool remove(LabelType vertex1, LabelType vertex2) = 0;
	
	/** Gets the weight of an edge in this graph.
	@return The weight of the specified edge.
	If no such edge exists, returns a negative integer. */
	virtual int getEdgeWeight(LabelType start, LabelType end) const = 0;
	
	/** Performs a depth-first seEdgeh of this graph beginning at the given
	vertex and calls a given function once for each vertex visited.
	@param start A label for the first vertex.
	@param visit A client-defined function that performs an operation on
	or with each visited vertex. */
	virtual void depthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
	
	/** Performs a breadth-first seEdgeh of this graph beginning at the given
	vertex and calls a given function once for each vertex visited.
	@param start A label for the first vertex.
	@param visit A client-defined function that performs an operation on
	or with each visited vertex. */
	virtual void breadthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
}; // end GraphInterface
#endif