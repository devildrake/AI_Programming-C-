#include "GoalOrientedShoot.h"

GoalOrientedShoot::GoalOrientedShoot() {
	//0 es false, 1 es true, 2 es doesn't matter

	preConditions[0] = 1; //Agent viu
	preConditions[1] = 1; //T� arma
	preConditions[2] = 1; //Arma carregada
	preConditions[3] = 2; //T� bomba
	preConditions[4] = 1; //Enemic visible
	preConditions[5] = 1; //Enemic alineat
	preConditions[6] = 1; //Enemic a prop
	preConditions[7] = 1; //Enemic viu

	postConditions[0] = 1;
	postConditions[1] = 1;
	postConditions[2] = 0;
	postConditions[3] = 2;
	postConditions[4] = 0;
	postConditions[5] = 0;
	postConditions[6] = 0;
	postConditions[7] = 0;

}

void GoalOrientedShoot::Update() {

	agent->worldDictionary[agent->AGENT_WEAPONLOADED] = false;
	agent->worldDictionary[agent->ENEMY_ALIVE] = false;
	agent->worldDictionary[agent->ENEMY_INSIGHT] = false;
	agent->worldDictionary[agent->ENEMY_ALIGNED] = false;
	agent->worldDictionary[agent->ENEMY_NEAR] = false;

}