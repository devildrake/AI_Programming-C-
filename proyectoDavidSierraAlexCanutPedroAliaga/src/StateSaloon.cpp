#include "StateSaloon.h"




void StateSaloon::Enter() {
	agent->SetDestiny(entrance);

}

void StateSaloon::Exit() {
	agent->arrived = false;

}

void StateSaloon::Update(float dtime) {
	if (agent->arrived) {
		if (agent->GetThirst() == 0) {
			agent->ChangeState(1);
		}
		else {
			if (agent->timerThirst >= agent->maxThirstTime/8) {
				agent->timerThirst = 0;
				agent->SetThirst(agent->GetThirst() - 1);
			}
		}
	}
	else {

	}
}

StateSaloon::StateSaloon(Agent* agent, Vector2D entrance) {
	this->agent = agent;
	this->entrance = entrance;
}