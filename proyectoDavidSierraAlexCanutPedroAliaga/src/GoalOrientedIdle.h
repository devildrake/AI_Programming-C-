#pragma once
#include "GoalOrientedAction.h"

class GoalOrientedIdle : public GoalOrientedAction {
public:
	virtual void Update();
	GoalOrientedIdle();
};

