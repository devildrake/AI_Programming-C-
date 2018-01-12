#include "WorldState.h"
#include "GoalOrientedAction.h"
WorldState::WorldState(int data[],GoalOrientedAction* action) {
	createdBy = action;
	for (int i = 0; i < 8; i++) {
		conditions[i] = data[i];
	}
	acumulatedCost = 0;
}

WorldState::WorldState(){
	conditions[0] = -1;
}

std::string WorldState::GetBits(int bits[],int size) {
	std::string temp = "";
	for (int i = 0; i < size; i++) {
		if (bits[i] == 0)
			temp += "0";
		else if (bits[i] == 1)
			temp += "1";
		else temp += "2";

	}
	return temp;
}

WorldState* WorldState::ApplyPostConditions(int arrayToChange[8], int postConditions[8]) {
	WorldState* temp = new WorldState(arrayToChange);
	for (int i = 0; i < 8; i++) {
		if (postConditions[i] != 2) {
			temp->conditions[i] = postConditions[i];
		}
	}


	return temp;
}


bool WorldState::isDoable(WorldState state, GoalOrientedAction* action) {
	bool temp = true;
	for (int i = 0; i < 8; i++) {
		if (action->preConditions[i] != 2 && state.conditions[i] != action->preConditions[i]) {
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

void WorldState::DebugBits() {
	std::string debugLog;

	for (int i = 0; i < 8; i++) {
		if (conditions[i])
			debugLog += "1";
		else
			debugLog += "0";

	}

	std::cout << debugLog << std::endl;
}

bool WorldState::Equals(WorldState lhs, WorldState rhs) {
	bool temp = true;
	for (int i = 0; i < 8; i++) {
		if ((lhs.conditions[i] != 2 && rhs.conditions[i] != 2) && lhs.conditions[i] != rhs.conditions[i]) {
			temp = false;
		}
	}
	return temp;
}

/*	preConditions[0] = 1; //Agent viu
	preConditions[1] = 1;//Té arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 2; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 2; //Enemic a prop
	preConditions[7] = 2; //Enemic viu*/

WorldState* WorldState::GenerateRandomState(){
	int tempData[8];
	for (int i = 1; i < 8; i++) {
		tempData[i] = rand() % 2;
	}
	tempData[0] = true;

	if (rand() % 100 < 10) {
		tempData[0] = false;
	}

	tempData[3] = false;
	if (tempData[7] == false) {
		tempData[6] = false;
		tempData[5] = false;
		tempData[4] = false;
	}

	if (tempData[1] == false) {
		tempData[2] = false;
	}

	if (tempData[4] == false) {
		tempData[6] = false;
		tempData[5] = false;
	}


	if (tempData[6] == false) {
		tempData[5] = false;
	}

	if (tempData[0]==false) {
		for (int i = 1; i < 8; i++) {
			tempData[i] = false;
		}
	}


	WorldState* temp = new WorldState(tempData);

return temp;
}