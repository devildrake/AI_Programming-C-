#define NullVector Vector2D{-1-1}
#include "SceneAStar.h"

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

float SceneAStar::ManhattanHeuristic(Vector2D current, Vector2D target) {


	Vector2D currentPixel = cell2pix(current);
	Vector2D targetPixel = cell2pix(target);


	float distanceX = targetPixel.x - currentPixel.x;
	float distanceY = targetPixel.y - currentPixel.y;
	float modulusA, modulusB;

	modulusA = sqrtf(distanceX*distanceX + distanceY*distanceY);
	//cout << distance.x << " - " << distance.y << endl;

	if (currentPixel.x >= (num_cell_x*CELL_SIZE) / 2) {
		//Mitad derecha
		distanceX = targetPixel.x + num_cell_x*CELL_SIZE - currentPixel.x;

	}
	else {
		//Mitad izquierda
		distanceX = targetPixel.x - num_cell_x*CELL_SIZE - currentPixel.x;

	}
	modulusB = sqrtf(distanceX*distanceX + distanceY*distanceY);


	if (modulusA > modulusB)
		return modulusB;
	else
		return modulusA;
}

SceneAStar::SceneAStar()
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
	agents[0]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3)) {
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
		cout << "coinPos (Coordenadas) " << coinPosition.x << " - " << coinPosition.y << endl;
	}

	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;



}

SceneAStar::~SceneAStar()
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

void SceneAStar::update(float dtime, SDL_Event *event)
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

			}
			AStar();


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
					if (pix2cell(agents[0]->getPosition()) == coinPosition)
					{
						coinPosition = Vector2D(-1, -1);
						while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 3)) {
							coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
							cout << "coinPos (Coordenadas) " << coinPosition.x << " - " << coinPosition.y << endl;
						}
					}
					AStar();
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



}

void SceneAStar::AStar() {
	ResetVisited();
	frontier.push(mapeado[pix2cell(agents[0]->getPosition())]);
	cameFrom[pix2cell(agents[0]->getPosition())] = NullVector;
	Vector2D current;
	Vector2D next;
	std::vector<Connection>neighbours;
	int ticksIniciales = SDL_GetTicks();
	while (!frontier.empty()) {
		current = frontier.top().coordenates;
		if (current == (coinPosition)) {
			cout << "Broke" << endl;
			break;
		}
		neighbours = graph.GetConnections(&nodos[current.x + current.y*num_cell_x]);
		frontier.pop();
		for (int i = 0; i < neighbours.size(); i++) {

			next = neighbours[i].GetToNode()->GetCoords();

			float newCost = cost_so_far[current] + neighbours[i].GetCost() + ManhattanHeuristic(next,coinPosition);

			//GETCOORDS ES CELDAS
			if ((cost_so_far[next] == 0) || (newCost<cost_so_far[next])) {
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
	current = coinPosition;
	path.points.push_back(cell2pix(current));

	while (current != pix2cell(agents[0]->getPosition())) {
		current = cameFrom[current];
		cout << current.x << " " << current.y << endl;
		path.points.insert(path.points.begin(), cell2pix(current));
	}
	foundPath = true;
	//ResetVisited();

}

void SceneAStar::draw()
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

const char* SceneAStar::getTitle()
{
	return "SDL Steering Behaviors :: SceneAStar";
}

void SceneAStar::drawMaze()
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

	for (int j = 0; j < nodos.size(); j++){
		if(nodos[j].cost>500)
					draw_circle(TheApp::Instance()->getRenderer(), cell2pix(nodos[j].GetCoords()).x, cell2pix(nodos[j].GetCoords()).y, 15, 0, 0, 255, 255);

	}


}

void SceneAStar::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void SceneAStar::initMaze()
{

	// Initialize a list of Rectagles describing the maze geometry (useful for collision avoidance)
	SDL_Rect rect = { 0, 0, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 608, 32, 64, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 736, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 608, 512, 64, 224 };
	maze_rects.push_back(rect);
	rect = { 0,32,32,288 };
	maze_rects.push_back(rect);
	rect = { 0,416,32,320 };
	maze_rects.push_back(rect);
	rect = { 1248,32,32,288 };
	maze_rects.push_back(rect);
	rect = { 1248,416,32,320 };
	maze_rects.push_back(rect);
	rect = { 128,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 288,128,96,32 };
	maze_rects.push_back(rect);
	rect = { 480,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 736,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 896,128,96,32 };
	maze_rects.push_back(rect);
	rect = { 1088,128,64,32 };
	maze_rects.push_back(rect);
	rect = { 128,256,64,32 };
	maze_rects.push_back(rect);
	rect = { 288,256,96,32 };
	maze_rects.push_back(rect);
	rect = { 480, 256, 320, 32 };
	maze_rects.push_back(rect);
	rect = { 608, 224, 64, 32 };
	maze_rects.push_back(rect);
	rect = { 896,256,96,32 };
	maze_rects.push_back(rect);
	rect = { 1088,256,64,32 };
	maze_rects.push_back(rect);
	rect = { 128,384,32,256 };
	maze_rects.push_back(rect);
	rect = { 160,512,352,32 };
	maze_rects.push_back(rect);
	rect = { 1120,384,32,256 };
	maze_rects.push_back(rect);
	rect = { 768,512,352,32 };
	maze_rects.push_back(rect);
	rect = { 256,640,32,96 };
	maze_rects.push_back(rect);
	rect = { 992,640,32,96 };
	maze_rects.push_back(rect);
	rect = { 384,544,32,96 };
	maze_rects.push_back(rect);
	rect = { 480,704,32,32 };
	maze_rects.push_back(rect);
	rect = { 768,704,32,32 };
	maze_rects.push_back(rect);
	rect = { 864,544,32,96 };
	maze_rects.push_back(rect);
	rect = { 320,288,32,128 };
	maze_rects.push_back(rect);
	rect = { 352,384,224,32 };
	maze_rects.push_back(rect);
	rect = { 704,384,224,32 };
	maze_rects.push_back(rect);
	rect = { 928,288,32,128 };
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


			if ( i==18||i == 19 || i == 20 ){
				if (j == 10 || j == 11 || j == 12 || j == 13 || j==9 || j==14 || j==15) {
					tmp.cost = tmp.waterNodeWeight;
				}
			}else
			tmp.cost = tmp.groundNodeWeight;


			nodos.push_back(tmp);
			cameFrom[Vector2D{ (float)i,(float)j }] = NullVector;
			cost_so_far[Vector2D{ (float)i,(float)j }] = 0;
			mapeado[Vector2D{ (float)i,(float)j }] = tmp;

		}
	}

	for (int i = num_cell_x; i < (nodos.size() - num_cell_x); i++) {
		if (!nodos[i].IsObstacle()) {
			if (i != num_cell_x * 10 && i != num_cell_x * 11 && i != num_cell_x * 12 && i != num_cell_x * 10 + num_cell_x - 1 && i != num_cell_x * 11 + num_cell_x - 1 && i != num_cell_x * 12 + num_cell_x - 1) {
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
	//LAS DE LA IZQUIERDA------------------------------------------------------------------------------------------

	graph.connections.push_back(Connection(nodos[num_cell_x * 10], nodos[num_cell_x * 11]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 10], nodos[num_cell_x * 10 + 1]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 10], nodos[num_cell_x * 10 + num_cell_x - 1]));

	graph.connections.push_back(Connection(nodos[num_cell_x * 11], nodos[num_cell_x * 12]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 11], nodos[num_cell_x * 11 + 1]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 11], nodos[num_cell_x * 11 + num_cell_x - 1]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 11], nodos[num_cell_x * 10]));

	graph.connections.push_back(Connection(nodos[num_cell_x * 12], nodos[num_cell_x * 11]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 12], nodos[num_cell_x * 12 + 1]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 12], nodos[num_cell_x * 12 + num_cell_x - 1]));

	//LAS DE LA DERECHA------------------------------------------------------------------------------------------

	graph.connections.push_back(Connection(nodos[num_cell_x * 10 + num_cell_x - 1], nodos[num_cell_x * 11 + num_cell_x - 1]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 10 + num_cell_x - 1], nodos[num_cell_x * 10 + num_cell_x - 2]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 10 + num_cell_x - 1], nodos[num_cell_x * 10]));

	graph.connections.push_back(Connection(nodos[num_cell_x * 11 + num_cell_x - 1], nodos[num_cell_x * 12 + num_cell_x - 1]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 11 + num_cell_x - 1], nodos[num_cell_x * 11 + num_cell_x - 2]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 11 + num_cell_x - 1], nodos[num_cell_x * 11]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 11 + num_cell_x - 1], nodos[num_cell_x * 10 + num_cell_x - 1]));

	graph.connections.push_back(Connection(nodos[num_cell_x * 12 + num_cell_x - 1], nodos[num_cell_x * 12 + num_cell_x - 2]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 12 + num_cell_x - 1], nodos[num_cell_x * 12]));
	graph.connections.push_back(Connection(nodos[num_cell_x * 12 + num_cell_x - 1], nodos[num_cell_x * 11 + num_cell_x - 1]));


}

void SceneAStar::ResetVisited() {
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

bool SceneAStar::loadTextures(char* filename_bg, char* filename_coin)
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

Vector2D SceneAStar::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D SceneAStar::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool SceneAStar::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}