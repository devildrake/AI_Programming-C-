#include "GoalOrientedRunAway.h"

GoalOrientedRunAway::GoalOrientedRunAway() {
	id = 6;
	preConditions[0] = 1; //Agent viu
	preConditions[1] = 0; //Té arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 0; //Té bomba
	preConditions[4] = 1; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 2; //Enemic a prop
	preConditions[7] = 2; //Enemic viu

	postConditions[0] = 1;
	postConditions[1] = 0;
	postConditions[2] = 2;
	postConditions[3] = 0;
	postConditions[4] = 0;
	postConditions[5] = 2;
	postConditions[6] = 0;
	postConditions[7] = 2;
}

void GoalOrientedRunAway::Update() {
	agent->worldDictionary[agent->ENEMY_INSIGHT] = false;
}