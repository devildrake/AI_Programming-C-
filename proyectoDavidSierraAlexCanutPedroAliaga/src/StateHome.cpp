#include "StateHome.h"

void StateHome::Enter() {
	agent->SetDestiny(entrance);
}

void StateHome::Exit() {
	agent->arrived = false;
}

void StateHome::Update(float dtime) {
	std::cout << "cosas" << std::endl;

	if (agent->arrived) {
		std::cout << "Esta en casa" << std::endl;
		if (this->agent->GetEnergy() == this->agent->GetMaxEnergy()) {
			this->agent->ChangeState(1);
		}
		else {
				agent->timerThirst += dtime;
				agent->timerEnergy += dtime;
			
				if (agent->timerThirst >= agent->maxThirstTime) {
					agent->timerThirst = 0;
					agent->SetThirst(agent->GetThirst()+1);
				}
				if (agent->timerEnergy >= agent->maxEnergyTime) {
					agent->timerEnergy = 0;
					agent->SetEnergy(agent->GetEnergy()+1);
				}
		}
	}
	else {
		std::cout << "No ha llegado a casa" << std::endl;
	}
}

StateHome::StateHome(Agent* agent, Vector2D entrance) {
	this->agent = agent;
	this->entrance = entrance;
}