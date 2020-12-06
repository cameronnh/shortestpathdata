#pragma once
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

class Weighted_Digraph
{
private:
	std::vector<std::vector<int>> adjacencies;
	std::vector<int> shortestPaths;	
	std::vector<std::string> parents;
	std::queue<int> remaining;
	void clearPaths();	
	void printPath(int i);
public:
	Weighted_Digraph();
	~Weighted_Digraph();

	std::vector<int> calculateDistances(int start);
	void loadGraph(std::string path);
	void printSolution();
};