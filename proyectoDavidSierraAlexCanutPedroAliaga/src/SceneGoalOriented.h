#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "GoalOrientedAction.h"
//#include "GoalOrientedAim.h"
//#include "GoalOrientedApproach.h"
//#include "GoalOrientedBlowUp.h"
//#include "GoalOrientedExplore.h"
//#include "GoalOrientedIdle.h"
//#include "GoalOrientedReload.h"
//#include "GoalOrientedRunAway.h"
//#include "GoalOrientedShoot.h"
#include "Path.h"
#include "Graph.h"
#include <queue>
#include <map>
#include <unordered_map>
#include "Text.h"

class SceneGoalOriented :
	public Scene
{
public:
	SceneGoalOriented();
	~SceneGoalOriented();
	void ThinkAStar();
	int ActionHeuristic(WorldState* ,WorldState*);
	void ClearAStar();
	std::priority_queue<WorldState*>frontier;
	std::unordered_map<WorldState*, WorldState*>came_from;
	std::unordered_map<WorldState*, float>cost_so_far;

	std::unordered_map<std::string, WorldState*>createdWorldState;

	std::vector<GoalOrientedAction*> actionsToComplete;
	bool foundPlan;
	bool mustAct;
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	void DrawTexts();
	std::vector<GoalOrientedAgent*> agents;

private:
	Text Data;
	SDL_Texture *background_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
	WorldState* goalWorld;
};
