#define NullVector Vector2D{-1-1}
#include "ScenePlanning.h"

using namespace std;

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

float ScenePlanning::EuclideanHeuristic(Vector2D current, Vector2D target) {

		Vector2D currentPixel = cell2pix(current);
		Vector2D targetPixel = cell2pix(target);


		float distanceX = targetPixel.x - currentPixel.x;
		float distanceY = targetPixel.y - currentPixel.y;
		float modulusA, modulusB;

		modulusA = sqrtf(distanceX*distanceX + distanceY*distanceY);

		return modulusA;
	}

ScenePlanning::ScenePlanning()
{
	waitAFrame = false;
	foundPath = false;
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze();
	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);


	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));



	agents[0]->setPosition(cell2pix(agents[0]->houseCoords));
	//agents[0]->setPosition(cell2pix(Vector2D(15,30)));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	//coinPosition = Vector2D(-1, -1);
	//while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3)) {
	//	coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	//	cout << "coinPos (Coordenadas) " << coinPosition.x << " - " << coinPosition.y << endl;
	//}

	while ((goldPieces.size() < 5)) {
		Vector2D goldPosition{ -1,-1 };
		
		goldPosition = Vector2D((float)(5+ rand() % num_cell_x -5), (float)(rand() % 5));

		if (isValidCell(goldPosition)) {
			goldPieces.push_back(Gold(goldPosition));
			cout << "goldPos (Coordenadas) " << goldPosition.x << " - " << goldPosition.y << endl;
			terrain[goldPosition.x][goldPosition.y] = 0;
		}
	}

	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;

	agents[0]->ChangeState(0);
}

ScenePlanning::~ScenePlanning()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePlanning::update(float dtime, SDL_Event *event)
{

	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (isValidCell(cell))
			{
				if (path.points.size() > 0)
					if (path.points[path.points.size() - 1] == cell2pix(cell))
						break;

				//path.points.push_back(cell2pix(cell));
				
				targetPosition = cell;
				cout << "Clicked at " << cell.x << " , " << cell.y << endl;
			}
			//AStar();


		}
		break;
	default:
		break;
	}
	if ((currentTargetIndex == -1) && (path.points.size()>0))
		currentTargetIndex = 0;

	if (currentTargetIndex >= 0)
	{
		float dist = Vector2D::Distance(agents[0]->getPosition(), path.points[currentTargetIndex]);
		if (dist < path.ARRIVAL_DISTANCE)
		{
			if (currentTargetIndex == path.points.size() - 1)
			{
				if (dist < 3)
				{
					path.points.clear();
					currentTargetIndex = -1;
					agents[0]->setVelocity(Vector2D(0, 0));
					// if we have arrived to the coin, replace it ina random cell!
					//if (pix2cell(agents[0]->getPosition()) == coinPosition)
					//{
					//	coinPosition = Vector2D(-1, -1);
					//	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 3)) {
					//		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
					//		cout << "coinPos (Coordenadas) " << coinPosition.x << " - " << coinPosition.y << endl;
					//	}
					//}
					//AStar();
				}
				else
				{
					//if (dtime > 0.3f)
					//dtime = 0.2f;


					Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], currentTarget, path.ARRIVAL_DISTANCE, dtime);
					if (foundPath) {
						agents[0]->update(steering_force, dtime, event);
					}
				}
				return;
			}
			currentTargetIndex++;
		}

		currentTarget = path.points[currentTargetIndex];
		Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], currentTarget, dtime);
		if (foundPath) {
			if (dtime > 0.04) {
				dtime = 0.04f;
			}
			//std::cout << dtime << std::endl;
			agents[0]->update(steering_force, dtime, event);
		}
	}
	else
	{
		if (foundPath) {
			agents[0]->update(Vector2D(0, 0), dtime, event);
		}
	}

	if (agents[0]->GetDestiny() != pix2cell(agents[0]->getPosition())&&!agents[0]->arrived) {
		AStar();
		//cout << "No ha llegado" << endl;
	}
	else if (agents[0]->GetDestiny() == pix2cell(agents[0]->getPosition()) && !agents[0]->arrived) {
		agents[0]->arrived = true;
		//cout << "Ha llegado" << endl;
	}
	agents[0]->Think(dtime);
	if (agents[0]->GetCurrentState() == agents[0]->state_mine&&agents[0]->arrived) {
		GoldHeuristic();
		AStar();
	}

	for (int i = 0; i < goldPieces.size(); i++) {
		if (goldPieces[i].mined) {
			goldPieces[i].mined = false;

			terrain[goldPieces[i].position.x][goldPieces[i].position.y] = 1;

			Vector2D goldPosition{ -1,-1 };

			goldPosition = Vector2D((float)(5 + rand() % num_cell_x - 5), (float)(rand() % 5));

			if (isValidCell(goldPosition)) {
				goldPieces.push_back(Gold(goldPosition));
				cout << "goldPos (Coordenadas) " << goldPosition.x << " - " << goldPosition.y << endl;
				terrain[goldPosition.x][goldPosition.y] = 0;
			}
		}
	}

}

void ScenePlanning::AStar() {
	if (targetPosition != (agents[0]->GetDestiny())) {
		targetPosition = (agents[0]->GetDestiny());

		ResetVisited();
		frontier.push(mapeado[pix2cell(agents[0]->getPosition())]);
		cameFrom[pix2cell(agents[0]->getPosition())] = NullVector;
		Vector2D current;
		Vector2D next;
		std::vector<Connection>neighbours;
		int ticksIniciales = SDL_GetTicks();
		while (!frontier.empty()) {
			current = frontier.top().coordenates;
			if (current == (targetPosition)) {
				//cout << "Broke" << endl;
				break;
			}
			neighbours = graph.GetConnections(&nodos[current.x + current.y*num_cell_x]);
			frontier.pop();
			for (int i = 0; i < neighbours.size(); i++) {

				next = neighbours[i].GetToNode()->GetCoords();

				float newCost = cost_so_far[current] + neighbours[i].GetCost() + EuclideanHeuristic(next, targetPosition);

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
		current = targetPosition;
		path.points.push_back(cell2pix(current));

		while (current != pix2cell(agents[0]->getPosition())) {
			current = cameFrom[current];
			//cout << current.x << " " << current.y << endl;
			path.points.insert(path.points.begin(), cell2pix(current));
		}
		foundPath = true;
		//ResetVisited();

	}
}

void ScenePlanning::GoldHeuristic() {
	Gold goldToMine = goldPieces[0];
/*float shortestDistance = SceneMultipleTarget::ManhattanHeuristic(pix2cell(agents[0]->getPosition()), coins[0]);
	closestCoinPosition = coins[0];
	for (int i = 1; i < coins.size(); i++) {
		if (shortestDistance > SceneMultipleTarget::ManhattanHeuristic(pix2cell(agents[0]->getPosition()), coins[i])) {
			shortestDistance = SceneMultipleTarget::ManhattanHeuristic(pix2cell(agents[0]->getPosition()), coins[i]);
			closestCoinPosition = coins[i];
		}
	}*/
	float minHeuristicCalculus = goldToMine.amount / EuclideanHeuristic(pix2cell(agents[0]->getPosition()), goldToMine.position);

	for (int i = 0; i < goldPieces.size(); i++) {
		if (minHeuristicCalculus > goldPieces[i].amount / EuclideanHeuristic(pix2cell(agents[0]->getPosition()), goldPieces[i].position)) {
			minHeuristicCalculus = goldPieces[i].amount / EuclideanHeuristic(pix2cell(agents[0]->getPosition()), goldPieces[i].position);
			goldToMine = goldPieces[i];
		}
	}
	agents[0]->SetDestiny(goldToMine.position);
	agents[0]->SetCurrentGoldPiece(&goldToMine);
}

void ScenePlanning::draw()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 255, 0, 127);

	for (unsigned int i = 0; i < graph.connections.size(); ++i) {
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), cell2pix(graph.connections[i].GetFromNode()->GetCoords()).x, cell2pix(graph.connections[i].GetFromNode()->GetCoords()).y, cell2pix(graph.connections[i].GetToNode()->GetCoords()).x, cell2pix(graph.connections[i].GetToNode()->GetCoords()).y);
	}
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);


	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	draw_circle(TheApp::Instance()->getRenderer(), (int)currentTarget.x, (int)currentTarget.y, 15, 255, 0, 0, 255);

	agents[0]->draw();
}

const char* ScenePlanning::getTitle()
{
	return "SDL Steering Behaviors :: ScenePlanning";
}

void ScenePlanning::drawMaze()
{
	if (draw_grid)
	{

		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
		for (unsigned int i = 0; i < maze_rects.size(); i++)
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &maze_rects[i]);
	}
	else
	{
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL);
	}

	for (int j = 0; j < nodos.size(); j++) {
		if (nodos[j].cost>500)
			draw_circle(TheApp::Instance()->getRenderer(), cell2pix(nodos[j].GetCoords()).x, cell2pix(nodos[j].GetCoords()).y, 15, 0, 0, 255, 255);

	}


}

void ScenePlanning::drawCoin()
{
	//cout << "DRAW" << endl;
	//Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;


	for (int i = 0; i < goldPieces.size(); i++) {
		Vector2D gold_coords = cell2pix(goldPieces[i].position);

		SDL_Rect dstrect = { (int)gold_coords.x - offset, (int)gold_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}

}

void ScenePlanning::initMaze()
{

	// Initialize a list of Rectagles describing the maze geometry (useful for collision avoidance)
	SDL_Rect rect = { 0, 0, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 128, 160, 1152, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 736, 1280, 32 };
	maze_rects.push_back(rect);

	rect = { 0,32,32,736 };
	maze_rects.push_back(rect);
	rect = { 1248,32,32,736 };
	maze_rects.push_back(rect);

	rect = { 416,512,32,268 };
	maze_rects.push_back(rect);
	rect = { 832,512,32,268 };
	maze_rects.push_back(rect);

	rect = { 32,480,128,32 };
	maze_rects.push_back(rect);
	rect = { 288,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 704,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 1120,480,128,32 };
	maze_rects.push_back(rect);

	// Initialize the terrain matrix (for each cell a zero value indicates it's a wall)

	// (1st) initialize all cells to 1 by default
	for (int i = 0; i < num_cell_x; i++)
	{
		vector<int> terrain_col(num_cell_y, 1);
		terrain.push_back(terrain_col);
	}
	// (2nd) set to zero all cells that belong to a wall
	int offset = CELL_SIZE / 2;
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{
			Vector2D cell_center((float)(i*CELL_SIZE + offset), (float)(j*CELL_SIZE + offset));
			for (unsigned int b = 0; b < maze_rects.size(); b++)
			{
				if (Vector2DUtils::IsInsideRect(cell_center, (float)maze_rects[b].x, (float)maze_rects[b].y, (float)maze_rects[b].w, (float)maze_rects[b].h))
				{
					terrain[i][j] = 0;
					break;
				}
			}

		}
	}


	for (int j = 0; j < num_cell_y; j++)
	{
		for (int i = 0; i < num_cell_x; i++)
		{

			Node tmp;
			tmp.SetObstacle(!terrain[i][j]);
			tmp.SetCoords(Vector2D{ (float)i,(float)j });

			tmp.cost = tmp.groundNodeWeight;


			nodos.push_back(tmp);
			cameFrom[Vector2D{ (float)i,(float)j }] = NullVector;
			cost_so_far[Vector2D{ (float)i,(float)j }] = 0;
			mapeado[Vector2D{ (float)i,(float)j }] = tmp;

		}
	}

	for (int i = num_cell_x; i < (nodos.size() - num_cell_x); i++) {
		if (!nodos[i].IsObstacle()) {
			if (!nodos[i - 1].IsObstacle()) {
				graph.connections.push_back(Connection(nodos[i], nodos[i - 1]));
				//std::cout << Connection(nodos[i], nodos[i - 1]).GetFromNode()->GetCoords().x<<std::endl;
			}if (!nodos[i + 1].IsObstacle()) {
				graph.connections.push_back(Connection(nodos[i], nodos[i + 1]));
			}if (!nodos[i - num_cell_x].IsObstacle()) {
				graph.connections.push_back(Connection(nodos[i], nodos[i - num_cell_x]));
			}if (!nodos[i + num_cell_x].IsObstacle()) {
				graph.connections.push_back(Connection(nodos[i], nodos[i + num_cell_x]));
			}
		}
	}

}
void ScenePlanning::ResetVisited() {
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

bool ScenePlanning::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D ScenePlanning::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D ScenePlanning::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool ScenePlanning::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}