#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "Node.h"
#include "Graph.h"
#include "Connection.h"
#include <queue>
#include <map>

class ScenePlanning :
	public Scene
{
public:
	ScenePlanning();
	~ScenePlanning();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D currentTarget;
	int currentTargetIndex;
	Path path;
	int num_cell_x;
	int num_cell_y;
	bool draw_grid;
	std::vector<SDL_Rect> maze_rects;
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	void initMaze();
	bool loadTextures(char* filename_bg, char* filename_coin);
	std::vector< std::vector<int> > terrain;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	float EuclideanHeuristic(Vector2D, Vector2D);
	void Astar();
	void ScenePlanning::ResetVisited();
	std::vector<Node> nodos;
	Graph graph;
	std::priority_queue<Node> frontier;
	std::map<Vector2D, Vector2D> cameFrom;
	std::map<Vector2D, Node> mapeado;
	std::map<Vector2D, float> cost_so_far;
	bool foundPath;

};
