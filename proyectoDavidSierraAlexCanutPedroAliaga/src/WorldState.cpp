#include "WorldState.h"

WorldState::WorldState(int id, int data[]) {

	this->id = id;
	for (int i = 0; i < 8; i++) {
		conditions[i] = data[i];
	}
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
	WorldState* temp = new WorldState(id, tempData);

return temp;
}