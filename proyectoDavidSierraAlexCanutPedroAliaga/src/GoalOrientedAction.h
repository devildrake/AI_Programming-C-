#pragma once
#include "GoalOrientedAgent.h"
class GoalOrientedAgent;
class GoalOrientedAction {

	//Agent_viu, Agent_te_Arma, Arma_carregada,  Agent_te_Bomba, Enemic_visible, Enemic_alineat ,Enemic_aprop, Enemic_viu
private:
public:
	GoalOrientedAgent* agent;
	int preConditions[8];
	int postConditions[8];
	virtual void Update()=0;

	bool CheckConditions(std::map<GoalOrientedAgent::WorldInfo,bool> a) {
		bool temp = true;
		if (preConditions[0] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_ALIVE] == preConditions[0])) {
				temp = false;
			}
		}
		if (preConditions[1] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_HASWEAPON] == preConditions[1])) {
				temp = false;
			}
		}
		if (preConditions[2] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_WEAPONLOADED] == preConditions[2])) {
				temp = false;
			}
		}
		if (preConditions[3] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_HASBOMB] == preConditions[3])) {
				temp = false;
			}
		}
		if (preConditions[4] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_INSIGHT] == preConditions[4])) {
				temp = false;
			}
		}
		if (preConditions[5] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_ALIGNED] == preConditions[5])) {
				temp = false;
			}
		}
		if (preConditions[6] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_NEAR] == preConditions[6])) {
				temp = false;
			}
		}
		if (preConditions[7] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_ALIVE] == preConditions[7])) {
				temp = false;
			}
		}
		return temp;
	}
};
