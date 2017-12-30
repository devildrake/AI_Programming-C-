#include "StateMine.h"



void StateMine::Enter() {
	std::cout << "Cambio a estado mina" << std::endl;
	agent->SetDestiny(entrance);

}

void StateMine::Exit() {
	agent->arrived = false;

}

Vector2D cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

void StateMine::Update(float dtime) {

	agent->timerThirst += dtime;
	agent->timerEnergy += dtime;

	if (agent->timerThirst >= agent->maxThirstTime) {
		agent->timerThirst = 0;
		agent->SetThirst(agent->GetThirst() + 1);
	}
	if (agent->timerEnergy >= agent->maxEnergyTime) {
		agent->timerEnergy = 0;
		agent->SetEnergy(agent->GetEnergy() - 1);
	}

	if (agent->arrived) {
		if (agent->GetCurrentGoldPiece() != nullptr) {

			if ((pix2cell(agent->getPosition())) == agent->GetCurrentGoldPiece()->position) {
				agent->GetCurrentGoldPiece()->mined = true;
				agent->SetGoldPieces(agent->GetGoldPieces() + agent->GetCurrentGoldPiece()->amount);
				//std::cout << "Llego al oro" << std::endl;
			}
			else {

			}
		}


		

		if (agent->GetGoldPieces() > agent->GetMaxGoldPieces()) {
			agent->ChangeState(2);
		}

		if (agent->GetThirst() > agent->GetMaxThirst()) {
			agent->ChangeState(3);
		}
	
	}

}

StateMine::StateMine(Agent* agent,Vector2D entrance) {
	this->agent = agent;
	this->entrance = entrance;

}