// Dijkstra's algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Vertex
{
	int number;
	int pathWeight;
	
	Vertex(int number, int pathWeight) {
		this->number = number;
		this->pathWeight = pathWeight;
	}
};

struct Path 
{
	int vertexNumber;
	int weight;
	Path(int vertexNumber, int weight) {
		this->vertexNumber = vertexNumber;
		this->weight = weight;
	}
};

struct Compare
{
	bool operator()(const Vertex& vertex1, const Vertex& vertex2) {
		return vertex1.pathWeight < vertex2.pathWeight;
	}
};

void initialisePathsAndIsInQueue(vector<vector<Path> >& paths, vector<bool>& isInQueue, int vertexNum);
void initialiseVertexes(vector<Vertex>& vertexes, int vertexNum);
void enterPaths(vector<vector<Path> >& paths, int pathNum);
void dijkstra(vector<vector<Path> > paths, vector<Vertex>& vertexes, vector<bool>& isInQueue, priority_queue<Vertex, vector<Vertex>, Compare>& vertexesQueue);
void printWeights(vector<Vertex> vertexes);

int main()
{
	int vertexNum, pathNum, startVertex;
	cin >> vertexNum >> pathNum >> startVertex;
	--startVertex;
	vector<vector<Path> > paths;
	vector<Vertex> vertexes;
	vector<bool> isInQueue;
	priority_queue<Vertex, vector<Vertex>, Compare> vertexesQueue;
	initialisePathsAndIsInQueue(paths, isInQueue, vertexNum);
	initialiseVertexes(vertexes, vertexNum);
	enterPaths(paths, pathNum);

	vertexesQueue.push(vertexes[startVertex]);
	while (!vertexesQueue.empty()) {
		dijkstra(paths, vertexes, isInQueue, vertexesQueue);
	}

	printWeights(vertexes);
}

void initialisePathsAndIsInQueue(vector<vector<Path> >& paths, vector<bool>& isInQueue, int vertexNum) {
	vector<Path> vertexPaths;
	for (int i = 0; i < vertexNum; i++) {
		paths.push_back(vertexPaths);
		isInQueue.push_back(false);
	}
}

void initialiseVertexes(vector<Vertex>& vertexes, int vertexNum) {
	Vertex *vertex = new Vertex(0, 0);
	vertexes.push_back(*vertex);
	for (int i = 1; i < vertexNum; i++) {
		vertex = new Vertex(i, INT_MAX);
		vertexes.push_back(*vertex);
	}
}

void enterPaths(vector<vector<Path> >& paths, int pathNum) {
	int vertex1, vertex2, pathWeight;
	Path* path;
	for (int i = 0; i < pathNum; i++) {
		cin >> vertex1 >> vertex2 >> pathWeight;
		--vertex1;
		--vertex2;
		path = new Path(vertex2, pathWeight);
		paths[vertex1].push_back(*path);
	}
}

void dijkstra(vector<vector<Path> > paths, vector<Vertex>& vertexes, vector<bool>& isInQueue, priority_queue<Vertex, vector<Vertex>, Compare>& vertexesQueue) {
	int startVertex = vertexesQueue.top().number;
	int startWeight = vertexesQueue.top().pathWeight;
	int vertexNumber, weight;
	vertexesQueue.pop();
	isInQueue[startVertex] = false;
	for (int i = 0; i < paths[startVertex].size(); i++) {
		vertexNumber = paths[startVertex][i].vertexNumber;
		weight = paths[startVertex][i].weight;
		if (vertexes[vertexNumber].pathWeight > startWeight + weight) {
			vertexes[vertexNumber].pathWeight = startWeight + weight;
			if (!isInQueue[vertexNumber]) {
				vertexesQueue.push(vertexes[vertexNumber]);
				isInQueue[vertexNumber] = true;
			}
		}
	}
}

void printWeights(vector<Vertex> vertexes) {
	for (int i = 0; i < vertexes.size(); i++) {
		cout << vertexes[i].number + 1 << " " << vertexes[i].pathWeight << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
