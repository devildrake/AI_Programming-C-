#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "Graph.h"
#include <queue>
#include <map>
#include "Gold.h"
#include "State.h"

class StateWalking : public State {

public:
	explicit StateWalking();
	~StateWalking()override;
	void Enter()override;
	void Exit()override;
	void Update()override;

private:
	int num_cell_x;
	int num_cell_y;
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D currentTarget;
	int currentTargetIndex;
	Path path;
	bool foundPath;
	std::vector< std::vector<int> > terrain;
	std::vector<Node> nodos;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	Graph graph;
	std::priority_queue<Node> frontier;
	std::map<Vector2D, Vector2D> cameFrom;
	std::map<Vector2D, Node> mapeado;
	std::map<Vector2D, float> cost_so_far;


public :
	void AStar();
	void ResetVisited();
	float EuclideanHeuristic(Vector2D, Vector2D);


};