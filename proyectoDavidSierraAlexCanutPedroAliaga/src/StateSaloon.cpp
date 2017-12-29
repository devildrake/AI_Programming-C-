#include "StateSaloon.h"




void StateSaloon::Enter() {
	agent->SetDestiny(entrance);

}

void StateSaloon::Exit() {
	agent->arrived = false;

}

void StateSaloon::Update(float dtime) {

}

StateSaloon::StateSaloon(Agent* agent, Vector2D entrance) {
	this->agent = agent;
	this->entrance = entrance;
}