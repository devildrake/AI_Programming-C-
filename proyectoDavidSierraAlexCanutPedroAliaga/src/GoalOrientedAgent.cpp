#include "GoalOrientedAgent.h"
#include "GoalOrientedAim.h"
#include "GoalOrientedApproach.h"
#include "GoalOrientedBlowUp.h"
#include "GoalOrientedExplore.h"
#include "GoalOrientedReload.h"
#include "GoalOrientedRunAway.h"
#include "GoalOrientedShoot.h"
#include "GoalOrientedIdle.h"
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
