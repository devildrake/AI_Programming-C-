#pragma once
#include <stdlib.h>
#include <string>
class GoalOrientedAction;
class WorldState {
private:
public:
	static bool Equals(WorldState, WorldState);
	WorldState(int[],GoalOrientedAction*);
	WorldState(int[]);
	WorldState();
	static std::string GetBits(int[],int);
	static bool isDoable(WorldState, GoalOrientedAction*);
	int acumulatedCost;
	int conditions[8];
	static WorldState* GenerateRandomState();
	static WorldState* ApplyPostConditions(int[8],int[8]);
	GoalOrientedAction* createdBy;
	void DebugBits();
};