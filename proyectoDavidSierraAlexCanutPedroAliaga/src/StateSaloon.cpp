#include "StateSaloon.h"




void StateSaloon::Enter() {
	agent->SetDestiny(entrance);

}

void StateSaloon::Exit() {
	agent->arrived = false;

}

std::string StateSaloon::GetName() {
	return "Saloon";
}

void StateSaloon::Update(float dtime) {
	agent->timerThirst += dtime;
	if (agent->arrived) {
		//std::cout << "Estoy en el  saloon" << std::endl;
		if (agent->GetThirst() == 0) {
			agent->ChangeState(1);
		}
		else {
			if (agent->timerThirst >= agent->maxThirstTime/8) {
				agent->timerThirst = 0;
				agent->SetThirst(agent->GetThirst() - 1);
				agent->SetCoinsInBank(agent->GetCoinsInBank() - 5);
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