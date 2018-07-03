#pragma once
#include <iostream>
#include "Graph.cpp"
using namespace std;

template<class LabelType>
void print(LabelType & data){
	cout<<data<<" ";
}


template<class LabelType>
void TestGraph(Graph<LabelType> & graph){
	int temp;
	LabelType v1, v2;
	bool exit = false;
	do {
		cout<<"*****************************************************"<<endl;
		cout<<"Choose a function:"<<endl;
		cout<<"[1] isEmpty \n[2] isExist \n[3] isConnected \n[4] getNumberOfVertices \n[5] getNumberOfEdges";
		cout<<"\n[6] getEdgeWeight \n[7] add \n[8] remove \n[9] clear \n[10] DepthFirstTraversal \n[11] BreadthFirstTraversal";
		cout<<"\n[0] Exit Tree Tester \n";
		cout<<"*****************************************************"<<endl;

		cin>>temp;
		switch (temp){
		case 0:
			exit = true;
			break;

		case 1:
			if (graph.isEmpty())
				cout<<"Graph is Empty!"<<endl;
			else
				cout<<"Graph is NOT Empty!"<<endl;
			break;

		case 2:
			cout<<"Enter value of a vertex: ";
			cin>>v1;
			if (graph.isExist(v1))
				cout<<"It exists :)"<<endl;
			else
				cout<<"It doesn't exist :("<<endl;
			break;

		case 3:
			cout<<"Enter values of 2 vertices: ";
			cin>>v1>>v2;
			if (graph.isConnected(v1, v2))
				cout<<"They are connected"<<endl;
			else
				cout<<"They're not connected"<<endl;
			break;

		case 4:
			cout<<"Number of vertices in graph are "<<graph.getNumVertices()<<endl;
			break;

		case 5:
			cout<<"Number of edges in graph are "<<graph.getNumEdges()<<endl;
			break;

		case 6:
			cout<<"Enter values of vertices:";
			cin>>v1>>v2;
			if(graph.getEdgeWeight(v1, v2) != 0)
				cout<<"Edge wight is "<<graph.getEdgeWeight(v1, v2)<<endl;
			else
				cout<<"At least one of the vertices doesn't exist"<<endl;
			break;

		case 7:
			cout<<"Enter values of 2 vertices and edgeWeight: ";
			cin>>v1>>v2>>temp;
			if (graph.add(v1, v2, temp))
				cout<<"Edge is added"<<endl;
			else
				cout<<"Edge already exists"<<endl;
			break;

		case 8:
			cout<<"Enter values of two vertices to remove edge in between: ";
			cin>>v1>>v2;
			if (graph.remove(v1, v2))
				cout<<"Edge is Removed!"<<endl;
			else
				cout<<"Edge is not Removed!"<<endl;
			break;

		case 9:
			graph.clear();
			cout<<"Graph is cleared"<<endl;
			break;

		case 10:
			cout<<"Enter start point: ";
			cin>>temp;
			graph.depthFirstTraversal(temp, print);
			cout<<endl;
			break;

		case 11:
			cout<<"Enter start point: ";
			cin>>temp;
			graph.breadthFirstTraversal(temp, print);
			cout<<endl;
			break;

		default:
			break;
		}

	} while (!exit);
}

void main(){
	Graph<int> graph;
	TestGraph(graph);
}
