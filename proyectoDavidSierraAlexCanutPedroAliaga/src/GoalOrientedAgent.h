#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include "SDL_SimpleApp.h"
#include "utils.h"
#include <map>


class GoalOrientedAction;

class GoalOrientedAgent
{
private:
public:
	enum WorldInfo{AGENT_ALIVE,AGENT_HASWEAPON,AGENT_WEAPONLOADED,AGENT_HASBOMB,ENEMY_INSIGHT,ENEMY_ALIGNED,ENEMY_NEAR,ENEMY_ALIVE};
	std::map <WorldInfo, bool> worldDictionary;
	std::map <WorldInfo, bool > goalWorld;
	GoalOrientedAgent();
	~GoalOrientedAgent();
	void update(float dtime, SDL_Event *event);
	void ChangeState(int state);

	//puntero al actual
	GoalOrientedAction* currentAction;

	GoalOrientedAction* idleAction;
	GoalOrientedAction* aimAction;
	GoalOrientedAction* blowUpAction;
	GoalOrientedAction* approachAction;
	GoalOrientedAction* runAwayAction;
	GoalOrientedAction* exploreAction;
	GoalOrientedAction* reloadAction;
	GoalOrientedAction* shootAction;


};
