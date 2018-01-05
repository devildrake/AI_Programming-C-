#include "GoalOrientedReload.h"

GoalOrientedReload::GoalOrientedReload() {
	//0 es false, 1 es true, 2 es doesn't matter

	conditions[0] = 1; //Agent viu
	conditions[1] = 1; //T� arma
	conditions[2] = 0; //Arma carregada
	conditions[3] = 2; //T� bomba
	conditions[4] = 2; //Enemic visible
	conditions[5] = 2; //Enemic alineat
	conditions[6] = 2; //Enemic a prop
	conditions[7] = 2; //Enemic viu
}

void GoalOrientedReload::Update() {
	agent->worldDictionary[agent->AGENT_WEAPONLOADED] = true;
}