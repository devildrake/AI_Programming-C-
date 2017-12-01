#include "Node.h"

Vector2D Node::GetCoords()
{
	return coordenates;

}

void Node::SetObstacle(bool a) {
	obstacle = a;
}
void Node::SetCoords(Vector2D coords) {
	coordenates = coords;
}

bool Node::IsObstacle() {
	return obstacle;
}

float Node::GetCost() {
	return cost;
}

