#include "StateMine.h"



void StateMine::Enter() {
	std::cout << "Cambio a estado mina" << std::endl;
	agent->SetDestiny(entrance);

}

void StateMine::Exit() {
	agent->arrived = false;

}

void StateMine::Update(float dtime) {
	
}

StateMine::StateMine(Agent* agent,Vector2D entrance) {
	this->agent = agent;
	this->entrance = entrance;

}