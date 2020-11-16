// BasicGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include "DataValue.h"
#include "Vertex.h"
#include "Graph.h"

using namespace std;

//Do not modify this method
void createVertices(shared_ptr<Graph> graph)
{
	graph->addVertex("Austin");
	graph->addVertex("Denver");
	graph->addVertex("Chicago");
	graph->addVertex("Houston");
	graph->addVertex("Washington");
	graph->addVertex("Atlanta");
	graph->addVertex("Dallas");
}

//Do not modify this method
void createEdges(shared_ptr<Graph> graph)
{
	graph->addAdjacentVertex("Dallas", "Austin");
	graph->addAdjacentVertex("Dallas", "Chicago");
	graph->addAdjacentVertex("Dallas", "Denver");

	graph->addAdjacentVertex("Austin", "Dallas");
	graph->addAdjacentVertex("Austin", "Houston");

	graph->addAdjacentVertex("Chicago", "Denver");

	graph->addAdjacentVertex("Denver", "Chicago");
	graph->addAdjacentVertex("Denver", "Washington");

	graph->addAdjacentVertex("Houston", "Atlanta");

	graph->addAdjacentVertex("Washington", "Dallas");
	graph->addAdjacentVertex("Washington", "Atlanta");

	graph->addAdjacentVertex("Atlanta", "Washington");
	graph->addAdjacentVertex("Atlanta", "Houston");
}

//add code to do BFS search to this method
void doBFS(shared_ptr<Graph> graph, string startCity, string destinationCity)
{
	shared_ptr<Vertex> startVertex = graph->getTargetVertex(startCity);
	shared_ptr<Vertex> destinationVertex = graph->getTargetVertex(destinationCity);
	vector<pair <shared_ptr<Vertex>, shared_ptr<Vertex>> > routes;//to store the adjcentcies in

	if (startVertex == destinationVertex)
	{
		cout << endl << "Start city is the destination city";
		return;
	}
	
	shared_ptr<Vertex> currentVertex = startVertex;

	vector<shared_ptr<Vertex>> visited;
	vector<shared_ptr<Vertex>> queue;
	visited.push_back(currentVertex);	//puts the next vector into visited
	queue.push_back(currentVertex);		//to store order i travel			

	while (queue.size() != 0)
	{
		currentVertex = queue.front();		//takes the next vertex at front of queue and removes it
		queue.erase(queue.begin());
		
		vector<shared_ptr<Vertex>> Adj = currentVertex->getAdjacencies();
		for (int i = 0; i < Adj.size(); ++i)									//for each adjecentcy get whats not been visited
		{
			if (find(visited.begin(), visited.end(), Adj[i]) != visited.end())
			{
			}
			else
			{		
				routes.push_back(make_pair(currentVertex, Adj[i]));//to put the current then the adjcentcy in					
				visited.push_back(Adj[i]);
				queue.push_back(Adj[i]);
			}
		}
	}
	// the rest will just be for decoding the routes vector!! without this i would just have bst not shortest algorithm
	vector<string> results;
	currentVertex = destinationVertex;//set current to last

	while (currentVertex != startVertex)
	{
		for (int i = 0; i < routes.size(); ++i)
		{
			if (routes[i].second == currentVertex)
			{
				results.push_back(currentVertex->getDataValue()->getName());
				currentVertex = routes[i].first;				
			}
		}
	}	
	
	cout << endl << startVertex->getDataValue()->getName();
	while (results.size() != 0)
	{
		cout << endl << results.back();
		results.pop_back();
	}
}

//add code to do DFS search to this method
void doDFS(shared_ptr<Graph> graph, string startCity, string destinationCity)
{
	shared_ptr<Vertex> startVertex = graph->getTargetVertex(startCity);
	shared_ptr<Vertex> destinationVertex = graph->getTargetVertex(destinationCity);

	vector<shared_ptr<Vertex>> visited;
	vector<shared_ptr<Vertex>> order;
	visited.push_back(startVertex);	//puts the next vector into visited
	order.push_back(startVertex);//to store order i travel

	if (startVertex == destinationVertex)
	{
		cout << endl << "Start city is the destination city";
		return;
	}
	
	shared_ptr<Vertex> currentVertex = startVertex;
	cout << endl << currentVertex->getDataValue()->getName();
	while (currentVertex != destinationVertex)//while the destination is not found
	{
		vector<shared_ptr<Vertex>> allAdj = currentVertex->getAdjacencies();
		vector<shared_ptr<Vertex>> unvistedAdj;

		int size = allAdj.size();
		for (int i = 0; i < size; i++)//for every adjacentcy check if its in visited
		{
			if (find(visited.begin(), visited.end(), allAdj[i]) != visited.end())
			{				
			}
			else
			{
				unvistedAdj.push_back(allAdj[i]);//gets all the unvisited vectors
			}
		}		

		if (unvistedAdj.size() == 0)//if theres no vectors to visit
		{			
			order.pop_back();
			currentVertex = order.back();
		}
		else
		{
			currentVertex = unvistedAdj[0];				//gets the first adj
			visited.push_back(currentVertex);			//puts it into visited
			order.push_back(currentVertex);				//adds it to the order

			cout << endl << currentVertex->getDataValue()->getName();//count the new value
		}						
	}			
}

//Do not modify this method
int main()
{
	shared_ptr<Graph> graph = shared_ptr<Graph>(new Graph());

	//create  vertices
	createVertices(graph);

	//now add the edges
	try
	{
		createEdges(graph);
	}
	catch (invalid_argument e)
	{
		cout << "Invalid city, cannot create edges: " << e.what() << endl;
		cout << "Program exiting" << endl << endl;
		system("pause");
		return 0;
	}

	bool doAnother = true;
	while (doAnother)
	{
		cout << endl << "Enter the starting city, or x to exit: ";
		string startCity;
		getline(cin, startCity);
		if (tolower(startCity[0]) == 'x')
		{
			doAnother = false;
			continue;
		}

		cout << "Enter the destination city: ";
		string destinationCity;
		getline(cin, destinationCity);

		try
		{
			cout << endl << "BFS:";//only thing i modified
			doBFS(graph, startCity, destinationCity);
			cout << endl << endl << "DFS:";
			doDFS(graph, startCity, destinationCity);
		}
		catch (invalid_argument e)
		{
			cout << "Invalid city in search: " << e.what() << endl;
		}

		cout << endl;
	}

}


