#include "GoalOrientedBlowUp.h"
GoalOrientedBlowUp::GoalOrientedBlowUp() {
	id = 2;
	preConditions[0] = 1; //Agent viu
	preConditions[1] = 2; //Té arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 1; //Té bomba
	preConditions[4] = 1; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 1; //Enemic a prop
	preConditions[7] = 1; //Enemic viu

	postConditions[0] = 0;
	postConditions[1] = 0;
	postConditions[2] = 0;
	postConditions[3] = 0;
	postConditions[4] = 0;
	postConditions[5] = 0;
	postConditions[6] = 0;
	postConditions[7] = 0;
	cost = 5;
	name = "Blow Up";

}
