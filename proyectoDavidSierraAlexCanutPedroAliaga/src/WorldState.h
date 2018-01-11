#pragma once
#include <stdlib.h>
class GoalOrientedAction;
class WorldState {
private:
public:
	static bool Equals(int, int);
	static bool Equals(WorldState, WorldState);
	WorldState(int[],GoalOrientedAction*);
	WorldState(int[]);
	static bool isDoable(WorldState, GoalOrientedAction*);
	int acumulatedCost;
	int conditions[8];
	static WorldState* GenerateRandomState(int );
	GoalOrientedAction* createdBy;
};