#include "GoalOrientedPickUpWeapon.h"

GoalOrientedPickUpWeapon::GoalOrientedPickUpWeapon() {
	//0 es false, 1 es true, 2 es doesn't matter
	id = 9;
	preConditions[0] = 1; //Agent viu
	preConditions[1] = 0;//T� arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 2; //T� bomba
	preConditions[4] = 2; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 2; //Enemic a prop
	preConditions[7] = 2; //Enemic viu

	postConditions[0] = 2;
	postConditions[1] = 1;
	postConditions[2] = 0;
	postConditions[3] = 2;
	postConditions[4] = 2;
	postConditions[5] = 2;
	postConditions[6] = 2;
	postConditions[7] = 2;
	cost = 1;
	name = "Pick up Weapon";

}

