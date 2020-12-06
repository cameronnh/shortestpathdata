// Weighted_Digraph.cpp
// Simulates a weighted, directed graph for demonstration of Dijkstra's algorithm
// Created by Chris Sousa, Marissa Kulz, and Cameron Jewett


#include "Weighted_Digraph.h"
#include<iostream>
#include<string>

Weighted_Digraph::Weighted_Digraph() {};
Weighted_Digraph::~Weighted_Digraph() {};

std::vector<int> Weighted_Digraph::calculateDistances(int start){	
	clearPaths();
	shortestPaths.at(start) = 0;
	parents.at(start) = std::to_string(start);
	remaining.emplace(start);
	while (remaining.size()) {
		int next = remaining.front();
		remaining.pop();
		for (auto i = 0; i < adjacencies.at(next).size(); i++) {
			if (adjacencies[next][i] < 0) {
				continue;
			}
			else if(shortestPaths.at(i) != -1 && adjacencies[next][i] + shortestPaths.at(next) > shortestPaths.at(i)){
				continue;
			}
			else{				
				shortestPaths.at(i) = shortestPaths.at(next) + adjacencies[next][i];
				//parents.at(i) = parents.at(next) + "->i";
				char c = i;
				parents.at(i) = parents.at(next) + c;
				remaining.emplace(i);
			}
		}
	}	
	return shortestPaths;
}

void Weighted_Digraph::clearPaths() {
	shortestPaths.clear();
	for (int i = 0; i < adjacencies.size(); i++) {
		shortestPaths.push_back(-1);
		parents.push_back("");
	}
}

void Weighted_Digraph::loadGraph(std::string path) {
	adjacencies.clear();
	try {
		std::ifstream readIn(path);
		std::string line;
		int weight;
		int i = 0;
		while (getline(readIn, line)) {
			std::vector<int> newRow;
			adjacencies.push_back(newRow);
			std::istringstream row(line);
			while (row >> weight) {
				adjacencies.at(i).push_back(weight);
			}
			i++;
		}
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

void Weighted_Digraph::printSolution() {
	int src = 0;
	int temp = 0;
	printf("Vertex\t\tPath");
	for (int i : calculateDistances(0)) {
		printf("\n%d -> %d \t\t",
			src, i);
		
		printPath(temp);
		temp++;
	}		
}

void Weighted_Digraph::printPath(int temp)
{	
	printf("%d", temp);
	//std::cout << parents.at(temp);		
}