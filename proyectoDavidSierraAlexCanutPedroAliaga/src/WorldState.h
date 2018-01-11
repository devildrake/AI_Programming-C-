#pragma once
#include <stdlib.h>
class WorldState {
private:
	int id;
public:
	bool Equals(int, int);
	bool Equals(WorldState, WorldState);
	WorldState(int, int[]);
	int conditions[8];
	static WorldState* GenerateRandomState(int );
};