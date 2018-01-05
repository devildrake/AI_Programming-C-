#pragma once
#include "GoalOrientedAgent.h"
class GoalOrientedAgent;
class GoalOrientedAction {

	//Agent_viu, Agent_te_Arma, Arma_carregada,  Agent_te_Bomba, Enemic_visible, Enemic_alineat ,Enemic_aprop, Enemic_viu
private:
public:
	GoalOrientedAgent* agent;
	int conditions[8];
	virtual void Update()=0;
	bool CheckConditions(std::map<GoalOrientedAgent::WorldInfo,bool> a) {
		bool temp = true;
		if (conditions[0] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_ALIVE] == conditions[0])) {
				temp = false;
			}
		}
		if (conditions[1] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_HASwEAPON] == conditions[1])) {
				temp = false;
			}
		}
		if (conditions[2] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_WEAPONLOADED] == conditions[2])) {
				temp = false;
			}
		}
		if (conditions[3] != 2) {
			if (!(a[GoalOrientedAgent::AGENT_HASBOMB] == conditions[3])) {
				temp = false;
			}
		}
		if (conditions[4] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_INSIGHT] == conditions[4])) {
				temp = false;
			}
		}
		if (conditions[5] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_ALIGNED] == conditions[5])) {
				temp = false;
			}
		}
		if (conditions[6] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_NEAR] == conditions[6])) {
				temp = false;
			}
		}
		if (conditions[7] != 2) {
			if (!(a[GoalOrientedAgent::ENEMY_ALIVE] == conditions[7])) {
				temp = false;
			}
		}
		return temp;
	}
};
