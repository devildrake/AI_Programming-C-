#include "GoalOrientedRunAway.h"

GoalOrientedRunAway::GoalOrientedRunAway() {
	conditions[0] = 1; //Agent viu
	conditions[1] = 0; //Té arma
	conditions[2] = 2; //Arma carregada
	conditions[3] = 0; //Té bomba
	conditions[4] = 1; //Enemic visible
	conditions[5] = 2; //Enemic alineat
	conditions[6] = 2; //Enemic a prop
	conditions[7] = 2; //Enemic viu
}

void GoalOrientedRunAway::Update() {
	agent->worldDictionary[agent->ENEMY_INSIGHT] = false;
}