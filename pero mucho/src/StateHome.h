#pragma once
#include "State.h"
class StateHome : public State {
	
public:
	explicit StateHome();
	~StateHome()override;
	void Enter()override;
	void Exit()override;
	void Update()override;

};