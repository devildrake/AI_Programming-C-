#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "GoalOrientedAgent.h"
#include "GoalOrientedAction.h"
#include "Path.h"
#include "Graph.h"
#include <queue>
#include <map>
#include <unordered_map>
#include "Gold.h"
#include "Text.h"

class SceneGoalOriented :
	public Scene
{
public:
	SceneGoalOriented();
	~SceneGoalOriented();
	void ThinkAStar();
	int ActionHeuristic(int[],GoalOrientedAction*);
	void ClearAStar();
	priority_queue<GoalOrientedAction>frontier;
	unordered_map<GoalOrientedAction, GoalOrientedAction>came_from;
	map<GoalOrientedAction, float>cost_so_far;
	
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	void DrawTexts();

private:
	SDL_Texture *background_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
	std::vector<GoalOrientedAgent*> agents;
};
