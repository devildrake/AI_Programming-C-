#pragma once
#include "GoalOrientedAgent.h"

class GoalOrientedAgent;
class GoalOrientedAction {

	//Agent_viu, Agent_te_Arma, Arma_carregada,  Agent_te_Bomba, Enemic_visible, Enemic_alineat ,Enemic_aprop, Enemic_viu
private:
public:
	int cost;
	int preConditions[8];
	int postConditions[8];
	int id;
	std::string name;

	virtual void Update(GoalOrientedAgent* agent) {

		agent->SetWorldStateConditions(postConditions);
		agent->SetPlanIndex(agent->GetPlanIndex() + 1);
		std::cout << "Doing Activity named: " + name << std::endl;

	}

};
