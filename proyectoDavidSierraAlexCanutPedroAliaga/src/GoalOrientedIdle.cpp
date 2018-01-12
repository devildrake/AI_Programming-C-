#include "GoalOrientedIdle.h"
#include <time.h>
GoalOrientedIdle::GoalOrientedIdle() {

	srand(time(NULL));
	//0 es false, 1 es true, 2 es doesn't matter
	id = 4;
	preConditions[0] = 2; //Agent viu
	preConditions[1] = 2; //Té arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 2; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 2; //Enemic a prop
	preConditions[7] = 2; //Enemic viu

	postConditions[0] = 2;
	postConditions[1] = 2;
	postConditions[2] = 2;
	postConditions[3] = 2;
	postConditions[4] = 2;
	postConditions[5] = 2;
	postConditions[6] = 2;
	postConditions[7] = 2;



	name = "Idle";


	//postConditions[0] = 1;
	//postConditions[1] = rand() % 2;
	//postConditions[2] = rand() % 2;
	//postConditions[3] = 1;
	//postConditions[4] = rand() % 2;
	//postConditions[5] = rand() % 2;
	//postConditions[6] = rand() % 2;
	//postConditions[7] = rand() % 2;
	/*agent->currentAction = this;

	agent->worldDictionary[agent->AGENT_ALIVE] = postConditions[0];
	agent->worldDictionary[agent->AGENT_HASWEAPON] = postConditions[1];
	agent->worldDictionary[agent->AGENT_WEAPONLOADED] = postConditions[2];
	agent->worldDictionary[agent->AGENT_HASBOMB] = postConditions[3];
	agent->worldDictionary[agent->ENEMY_INSIGHT] = postConditions[4];
	agent->worldDictionary[agent->ENEMY_ALIGNED] = postConditions[5];
	agent->worldDictionary[agent->ENEMY_NEAR] = postConditions[6];
	agent->worldDictionary[agent->ENEMY_ALIVE] = postConditions[7];

	agent->goalWorld[agent->AGENT_ALIVE] = rand() % 2;
	agent->goalWorld[agent->AGENT_HASWEAPON] = rand() % 2;
	agent->goalWorld[agent->AGENT_WEAPONLOADED] = rand() % 2;
	agent->goalWorld[agent->AGENT_HASBOMB] = rand() % 2;
	agent->goalWorld[agent->ENEMY_INSIGHT] = rand() % 2;
	agent->goalWorld[agent->ENEMY_ALIGNED] = rand() % 2;
	agent->goalWorld[agent->ENEMY_NEAR] = rand() % 2;
	agent->goalWorld[agent->ENEMY_ALIVE] = rand() % 2;*/
}
