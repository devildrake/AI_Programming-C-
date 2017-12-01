#pragma once
#include "State.h"
class StateSaloon : public State {
	
public:
	explicit StateSaloon();
	~StateSaloon()override;
	void Enter()override;
	void Exit()override;
	void Update()override;

};