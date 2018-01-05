#include "GoalOrientedApproach.h"

GoalOrientedApproach::GoalOrientedApproach() {
	conditions[0] = 1; //Agent viu
	conditions[1] = 1; //Té arma
	conditions[2] = 2; //Arma carregada
	conditions[3] = 2; //Té bomba
	conditions[4] = 1; //Enemic visible
	conditions[5] = 2; //Enemic alineat
	conditions[6] = 0; //Enemic a prop
	conditions[7] = 1; //Enemic viu
}

void GoalOrientedApproach::Update() {
	agent->worldDictionary[agent->ENEMY_NEAR]= true;
}