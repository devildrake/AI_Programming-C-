#include "GoalOrientedPickUpBomb.h"

GoalOrientedPickUpBomb::GoalOrientedPickUpBomb() {
	id = 12;
	preConditions[0] = 1; //Agent viu
	preConditions[1] = 2; //Té arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 0; //Té bomba
	preConditions[4] = 2; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 2; //Enemic a prop
	preConditions[7] = 2; //Enemic viu

	postConditions[0] = 1;
	postConditions[1] = 2;
	postConditions[2] = 2;
	postConditions[3] = 1;
	postConditions[4] = 2;
	postConditions[5] = 2;
	postConditions[6] = 2;
	postConditions[7] = 2;
	cost = 5;
	name = "Pick Up Bomb";

}
