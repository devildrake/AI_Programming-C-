#pragma once
#include "Vector2D.h"
#define CELL_SIZE 32
class Node
{
private:
	bool obstacle;
public:
	Vector2D coordenates;
	float cost;
	float acumulatedCost;
	Vector2D GetCoords();
	void SetObstacle(bool);
	void SetCoords(Vector2D coords);
	float GetCost();
	bool IsObstacle();
	const static int groundNodeWeight = CELL_SIZE;
	const static int forestNodeWeight = CELL_SIZE * 40;
	const static int waterNodeWeight = CELL_SIZE * 100;
};
