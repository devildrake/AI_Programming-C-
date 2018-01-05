#include "GoalOrientedBlowUp.h"

GoalOrientedBlowUp::GoalOrientedBlowUp() {
	conditions[0] = 1; //Agent viu
	conditions[1] = 2; //Té arma
	conditions[2] = 2; //Arma carregada
	conditions[3] = 2; //Té bomba
	conditions[4] = 1; //Enemic visible
	conditions[5] = 2; //Enemic alineat
	conditions[6] = 1; //Enemic a prop
	conditions[7] = 1; //Enemic viu
}

void GoalOrientedBlowUp::Update() {
	agent->worldDictionary[agent->AGENT_ALIVE] = false;
	agent->worldDictionary[agent->AGENT_HASBOMB] = false;
	agent->worldDictionary[agent->ENEMY_ALIVE] = false;
	agent->worldDictionary[agent->ENEMY_INSIGHT] = false;
	agent->worldDictionary[agent->ENEMY_NEAR] = false;
	agent->worldDictionary[agent->ENEMY_ALIGNED] = false;
}