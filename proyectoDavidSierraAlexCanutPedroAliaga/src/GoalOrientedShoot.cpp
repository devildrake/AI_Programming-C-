#include "GoalOrientedShoot.h"

GoalOrientedShoot::GoalOrientedShoot() {
	//0 es false, 1 es true, 2 es doesn't matter

	conditions[0] = 1; //Agent viu
	conditions[1] = 1; //Té arma
	conditions[2] = 1; //Arma carregada
	conditions[3] = 2; //Té bomba
	conditions[4] = 1; //Enemic visible
	conditions[5] = 1; //Enemic alineat
	conditions[6] = 1; //Enemic a prop
	conditions[7] = 1; //Enemic viu

}

void GoalOrientedShoot::Update() {

	agent->worldDictionary[agent->AGENT_WEAPONLOADED] = false;
	agent->worldDictionary[agent->ENEMY_ALIVE] = false;
	agent->worldDictionary[agent->ENEMY_INSIGHT] = false;
	agent->worldDictionary[agent->ENEMY_ALIGNED] = false;
	agent->worldDictionary[agent->ENEMY_NEAR] = false;

}