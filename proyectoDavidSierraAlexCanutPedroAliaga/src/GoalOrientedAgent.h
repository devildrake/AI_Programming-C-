#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include "SDL_SimpleApp.h"
#include "utils.h"
#include <map>


class GoalOrientedAction;
class WorldState;

class GoalOrientedAgent
{
private:
	int planIndex;

public:
	GoalOrientedAction* aimAction;
	GoalOrientedAction* approachAction;
	GoalOrientedAction* blowUpAction;
	GoalOrientedAction* exploreAction;
	GoalOrientedAction* reloadAction;
	GoalOrientedAction* runAwayAction;
	GoalOrientedAction* shootAction;
	GoalOrientedAction* idleAction;

	GoalOrientedAgent();
	~GoalOrientedAgent();
	void update(float dtime, SDL_Event *event);
	WorldState* currentWorld;
	void SetWorldStateConditions(int[8]);
	int GetPlanIndex();
	void SetPlanIndex(int);
};
