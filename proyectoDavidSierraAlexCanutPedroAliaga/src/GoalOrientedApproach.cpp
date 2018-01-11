#include "GoalOrientedApproach.h"

GoalOrientedApproach::GoalOrientedApproach() {
	preConditions[0] = 1; //Agent viu
	preConditions[1] = 1; //Té arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 1; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 0; //Enemic a prop
	preConditions[7] = 1; //Enemic viu

	postConditions[0] = 1;
	postConditions[1] = 1;
	postConditions[2] = 2;
	postConditions[3] = 2;
	postConditions[4] = 1;
	postConditions[5] = 2;
	postConditions[6] = 1;
	postConditions[7] = 1;
}

void GoalOrientedApproach::Update() {
	agent->worldDictionary[agent->ENEMY_NEAR]= true;
}