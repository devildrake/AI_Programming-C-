#include "GoalOrientedAim.h"

GoalOrientedAim::GoalOrientedAim() {
	//0 es false, 1 es true, 2 es doesn't matter

	conditions[0] = 1; //Agent viu
	conditions[1] = 1; //Té arma
	conditions[2] = 1; //Arma carregada
	conditions[3] = 2; //Té bomba
	conditions[4] = 1; //Enemic visible
	conditions[5] = 0; //Enemic alineat
	conditions[6] = 1; //Enemic a prop
	conditions[7] = 1; //Enemic viu
}

void GoalOrientedAim::Update() {
	agent->worldDictionary[agent->ENEMY_ALIGNED] = true;
}