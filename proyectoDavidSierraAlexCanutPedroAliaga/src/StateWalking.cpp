#include "StateWalking.h"
#define NullVector {-1,-1};

//Sobrecarga del operador <
static inline bool operator < (const Vector2D& lhs, const Vector2D& rhs) {
	bool temp = false;
	if (lhs.y > rhs.y) {
		temp = true;
	}

	else if (lhs.y == rhs.y) {
		if (lhs.x > rhs.x) {
			temp = true;
		}
	}

	return temp;
}

static inline bool operator < (const Node& lhs, const Node& rhs) {
	return lhs.acumulatedCost>rhs.acumulatedCost;
}

void StateWalking::AStar() {

	ResetVisited();
	frontier.push(mapeado[pix2cell(agents[0]->getPosition())]);
	cameFrom[pix2cell(agents[0]->getPosition())] = NullVector;
	Vector2D current;
	Vector2D next;
	std::vector<Connection>neighbours;
	int ticksIniciales = SDL_GetTicks();
	while (!frontier.empty()) {
		current = frontier.top().coordenates;
		if (current == (target)) {
			std::cout << "Broke" << std::endl;
			break;
		}
		neighbours = graph.GetConnections(&nodos[current.x + current.y*num_cell_x]);
		frontier.pop();
		for (int i = 0; i < neighbours.size(); i++) {

			next = neighbours[i].GetToNode()->GetCoords();

			float newCost = cost_so_far[current] + neighbours[i].GetCost() + EuclideanHeuristic(next, target);

			//GETCOORDS ES CELDAS
			if ((cost_so_far[next] == 0) || (newCost < cost_so_far[next])) {
				neighbours[i].GetToNode()->acumulatedCost = newCost;
				cost_so_far[next] = newCost;
				frontier.push(*neighbours[i].GetToNode());
				cameFrom[next] = current;
			}
		}
		//frontier.pop();

	}
	//std::cout << "Calcular el path tarda" << SDL_GetTicks() - ticksIniciales << std::endl;

	//REVERSE PATH
	current = target;
	path.points.push_back(cell2pix(current));

	while (current != pix2cell(agents[0]->getPosition())) {
		current = cameFrom[current];
		std::cout << current.x << " " << current.y << std::endl;
		path.points.insert(path.points.begin(), cell2pix(current));
	}
	foundPath = true;
	//ResetVisited();

}

void StateWalking::ResetVisited() {
	for (int j = 0; j < num_cell_y; j++)
	{
		for (int i = 0; i < num_cell_x; i++)
		{
			cameFrom[Vector2D{ (float)i,(float)j }] = NullVector;
			cost_so_far[Vector2D{ (float)i,(float)j }] = 0;
		}
	}

	for (int i = 0; i < nodos.size(); i++) {
		nodos[i].acumulatedCost = 0;
	}

	int frontierSize = frontier.size();

	for (int i = 0; i < frontierSize; i++) {
		frontier.pop();
	}
}

Vector2D StateWalking::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D StateWalking::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

float StateWalking::EuclideanHeuristic(Vector2D current, Vector2D target) {


	Vector2D currentPixel = cell2pix(current);
	Vector2D targetPixel = cell2pix(target);


	float distanceX = targetPixel.x - currentPixel.x;
	float distanceY = targetPixel.y - currentPixel.y;
	float modulusA, modulusB;

	modulusA = sqrtf(distanceX*distanceX + distanceY*distanceY);

	return modulusA;
}