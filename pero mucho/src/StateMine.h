#pragma once
#include "State.h"
class StateMine : public State {

public:
	explicit StateMine();
	~StateMine()override;
	void Enter()override;
	void Exit()override;
	void Update()override;

};
