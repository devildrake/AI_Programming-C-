#include "StateBank.h"

void StateBank::Enter() {
	agent->SetDestiny(entrance);

}

void StateBank::Exit() {
	agent->arrived = false;

}

void StateBank::Update(float dtime) {

}

StateBank::StateBank(Agent* agent,Vector2D entrance) {
	this->agent = agent;
	this->entrance = entrance;
}