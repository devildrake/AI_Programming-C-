#include "WorldState.h"
#include "GoalOrientedAction.h"
WorldState::WorldState(int data[],GoalOrientedAction* action) {
	createdBy = action;
	for (int i = 0; i < 8; i++) {
		conditions[i] = data[i];
	}
	acumulatedCost = 0;
}

bool WorldState::isDoable(WorldState state, GoalOrientedAction* action) {
	bool temp = true;
	for (int i = 0; i < 8; i++) {
		if (state.conditions[i] != 2 && action->preConditions[i] != 2 && state.conditions[i] != action->preConditions[i]) {
			temp = false;
		}
	}
	return temp;
}

WorldState::WorldState(int data[]) {
	createdBy = nullptr;
	for (int i = 0; i < 8; i++) {
		conditions[i] = data[i];
	}
	acumulatedCost = 0;
}

bool WorldState::Equals(int id1, int id2) {
	return id1 == id2;
}

bool WorldState::Equals(WorldState lhs, WorldState rhs) {
	bool temp = true;
	for (int i = 0; i < 8; i++) {
		if (lhs.conditions[i] != 2 && rhs.conditions[i] != 2 && lhs.conditions[i] != rhs.conditions[i]) {
			temp = false;
		}
	}
	return temp;
}

static WorldState* GenerateRandomState(int id){
	int tempData[8];
	for (int i = 0; i < 8; i++) {
		tempData[i] = rand() % 2;
	}
	tempData[0] = true;
	WorldState* temp = new WorldState(tempData);

return temp;
}