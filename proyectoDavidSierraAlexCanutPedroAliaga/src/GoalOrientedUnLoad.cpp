#include "GoalOrientedUnLoad.h"

GoalOrientedUnLoad::GoalOrientedUnLoad() {
	id = 1;
	preConditions[0] = 1; //Agent viu
	preConditions[1] = 1; //Té arma
	preConditions[2] = 1; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 2; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 2; //Enemic a prop
	preConditions[7] = 2; //Enemic viu

	postConditions[0] = 1;
	postConditions[1] = 1;
	postConditions[2] = 0;
	postConditions[3] = 2;
	postConditions[4] = 2;
	postConditions[5] = 2;
	postConditions[6] = 2;
	postConditions[7] = 2;
	cost = 2;
	name = "Unload Weapon";

}
