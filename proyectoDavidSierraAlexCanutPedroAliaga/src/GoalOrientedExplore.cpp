#include "GoalOrientedExplore.h"

GoalOrientedExplore::GoalOrientedExplore() {
	//0 es false, 1 es true, 2 es doesn't matter

	conditions[0] = 1; //Agent viu
	conditions[1] = 2; //Té arma
	conditions[2] = 2; //Arma carregada
	conditions[3] = 2; //Té bomba
	conditions[4] = 0; //Enemic visible
	conditions[5] = 2; //Enemic alineat
	conditions[6] = 2; //Enemic a prop
	conditions[7] = 1; //Enemic viu
}

void GoalOrientedExplore::Update() {
	agent->worldDictionary[agent->ENEMY_INSIGHT] = true;
}