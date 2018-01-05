#include "StateBank.h"

void StateBank::Enter() {
	agent->SetDestiny(entrance);

}

void StateBank::Exit() {
	agent->arrived = false;

}

std::string StateBank::GetName() {
	return "Bank";
}

void StateBank::Update(float dtime) {
	if (agent->arrived) {
		agent->SetCoinsInBank(agent->GetGoldPieces() + agent->GetCoinsInBank());
		agent->SetGoldPieces(0);
		if (agent->GetCoinsInBank() < agent->GetWealthThreshold()) {
			agent->ChangeState(1);
		}
		else {
			agent->ChangeState(0);
			agent->SetWealthThreshold(agent->GetWealthThreshold() + 30);
		}

	}
}

StateBank::StateBank(Agent* agent,Vector2D entrance) {
	this->agent = agent;
	this->entrance = entrance;
}