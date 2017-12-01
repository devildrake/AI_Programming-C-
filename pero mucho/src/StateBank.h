#pragma once
#include "State.h"
class StateBank : public State {

public:
	explicit StateBank();
	~StateBank()override;
	void Enter()override;
	void Exit()override;
	void Update()override;

};