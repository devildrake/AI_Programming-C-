#include "GoalOrientedAgent.h"
#include "GoalOrientedAim.h"
#include "GoalOrientedApproach.h"
#include "GoalOrientedBlowUp.h"
#include "GoalOrientedExplore.h"
#include "GoalOrientedReload.h"
#include "GoalOrientedRunAway.h"
#include "GoalOrientedShoot.h"

using namespace std;
GoalOrientedAgent::GoalOrientedAgent(){


}

GoalOrientedAgent::~GoalOrientedAgent(){


}


void GoalOrientedAgent::ChangeState(int state) {

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
