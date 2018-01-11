#include "GoalOrientedAim.h"

GoalOrientedAim::GoalOrientedAim() {
	//0 es false, 1 es true, 2 es doesn't matter
	id = 0;
	preConditions[0] = 1; //Agent viu
	preConditions[1] = 1; //Té arma
	preConditions[2] = 1; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 1; //Enemic visible
	preConditions[5] = 0; //Enemic alineat
	preConditions[6] = 1; //Enemic a prop
	preConditions[7] = 1; //Enemic viu

	postConditions[0] = 1;
	postConditions[1] = 1;
	postConditions[2] = 1;
	postConditions[3] = 2;
	postConditions[4] = 1;
	postConditions[5] = 1;
	postConditions[6] = 1;
	postConditions[7] = 1;
}
