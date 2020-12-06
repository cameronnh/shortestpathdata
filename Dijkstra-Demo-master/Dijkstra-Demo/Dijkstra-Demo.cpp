// Dijkstra-Demo.cpp 
// A program using a Weighted Digraph class to demonstrate Dijksta's Algorithm
// Written by Chris Sousa, Marissa Kulz, and Cameron Jewett
//

#include "Weighted_Digraph.h"

int main()
{
	Weighted_Digraph digraph;
	digraph.loadGraph("matrix.txt");
	digraph.printSolution();
}