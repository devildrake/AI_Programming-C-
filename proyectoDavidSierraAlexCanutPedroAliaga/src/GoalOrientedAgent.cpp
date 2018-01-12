#include "GoalOrientedAgent.h"
#include "GoalOrientedAim.h"
#include "GoalOrientedApproach.h"
#include "GoalOrientedBlowUp.h"
#include "GoalOrientedExplore.h"
#include "GoalOrientedReload.h"
#include "GoalOrientedRunAway.h"
#include "GoalOrientedShoot.h"
#include "GoalOrientedIdle.h"
#include "GoalOrientedPickUpWeapon.h"
#include "GoalOrientedThrowWeapon.h"
#include "GoalOrientedUnAim.h"
#include "GoalOrientedUnLoad.h"
#include "GoalOrientedPickUpBomb.h"
#include "WorldState.h"
using namespace std;
GoalOrientedAgent::GoalOrientedAgent(){
	//currentWorld = WorldState::GenerateRandomState(-1);
	aimAction = new GoalOrientedAim();
	approachAction = new GoalOrientedApproach();
	blowUpAction = new GoalOrientedBlowUp();
	exploreAction = new GoalOrientedExplore();
	reloadAction = new GoalOrientedReload();
	runAwayAction = new GoalOrientedRunAway();
	shootAction = new GoalOrientedShoot();
	idleAction = new GoalOrientedIdle();
	pickUpWeaponAction = new GoalOrientedPickUpWeapon();
	throwWeaponAction = new GoalOrientedThrowWeapon();
	unLoadWeaponAction = new GoalOrientedUnLoad();
	unAimAction = new GoalOrientedUnAim();
	pickUpBombAction = new GoalOrientedPickUpBomb();
	currentWorld = WorldState::GenerateRandomState();
	currentWorld->conditions[0] = 1;
}

int GoalOrientedAgent::GetPlanIndex() {
	return planIndex;
}
void GoalOrientedAgent::SetPlanIndex(int a) {
	planIndex = a;
}

void GoalOrientedAgent::SetWorldStateConditions(int data[8]) {
	for (int i = 0; i < 8; i++) {
		if (data[i] != 2) {
			currentWorld->conditions[i] = data[i];
		}
	}
}

GoalOrientedAgent::~GoalOrientedAgent(){
	delete aimAction;
	delete approachAction;
	delete blowUpAction;
	delete exploreAction;
	delete idleAction;
	delete reloadAction;
	delete runAwayAction;
	delete shootAction;
	delete throwWeaponAction;
	delete pickUpWeaponAction;
	delete unAimAction;
	delete unLoadWeaponAction;
	delete pickUpBombAction;
}

void GoalOrientedAgent::ResetWorldView() {
	currentWorld->conditions[0] = 1;
	currentWorld->conditions[1] = rand() % 2;
	currentWorld->conditions[2] = rand() % 2;
	currentWorld->conditions[3] = 0;
	currentWorld->conditions[4] = rand() % 2;
	currentWorld->conditions[5] = rand() % 2;
	currentWorld->conditions[6] = rand() % 2;
	currentWorld->conditions[7] = 1;

	if (!currentWorld->conditions[1]) {
		currentWorld->conditions[2] = false; //Arma carregada
		currentWorld->conditions[5] = false; //Enemic alineat
	}

	if (!currentWorld->conditions[6]) {
		currentWorld->conditions[4] = false;
	}
	else {
		currentWorld->conditions[4] = true;
	}



	if (!currentWorld->conditions[4]) {
		currentWorld->conditions[5] = false;
	}

	
	/*	preConditions[0] = 1; //Agent viu
	preConditions[1] = 2; //Té arma
	preConditions[2] = 2; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 0; //Enemic visible
	preConditions[5] = 2; //Enemic alineat
	preConditions[6] = 2; //Enemic a prop
	preConditions[7] = 1; //Enemic viu*/



}

void GoalOrientedAgent::update(float dtime, SDL_Event *event)
{
	//Ccout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			//draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}


}
