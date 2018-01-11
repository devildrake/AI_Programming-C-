#define NullVector Vector2D{-1-1}
#include "SceneGoalOriented.h"
#include "GoalOrientedAgent.h"
#include "WorldState.h"
using namespace std;


static inline bool operator < (const GoalOrientedAction& lhs, const GoalOrientedAction& rhs) {
	return lhs.cost>rhs.cost;
}

SceneGoalOriented::SceneGoalOriented()
{
	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	GoalOrientedAgent *agent = new GoalOrientedAgent;

	//agent->loadSpriteTexture("../res/soldier.png", 4);

	agents.push_back(agent);

}

SceneGoalOriented::~SceneGoalOriented()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneGoalOriented::update(float dtime, SDL_Event *event)
{

}

void SceneGoalOriented::ClearAStar() {
	while (!frontier.empty()) {
		frontier.pop();
	}

	//for (std::map<WorldState*, WorldState*>::iterator it = came_from.begin(); it != came_from.end(); ++it) {

	//}

	came_from.clear();
	cost_so_far.clear();
}


void SceneGoalOriented::ThinkAStar() {
	ClearAStar();

}

void SceneGoalOriented::DrawTexts() {
	Text Data("Alive", Vector2D(20, 5), 20);
	Data.SetText("I'm Alive");
	Data.DrawText();
}

void SceneGoalOriented::draw()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 255, 0, 127);

	//for (unsigned int i = 0; i < graph.connections.size(); ++i) {
	//	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), cell2pix(graph.connections[i].GetFromNode()->GetCoords()).x, cell2pix(graph.connections[i].GetFromNode()->GetCoords()).y, cell2pix(graph.connections[i].GetToNode()->GetCoords()).x, cell2pix(graph.connections[i].GetToNode()->GetCoords()).y);
	//}
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);

	//drawMaze();
	//drawCoin();
	DrawTexts();

}

const char* SceneGoalOriented::getTitle()
{
	return "SDL Steering Behaviors :: ScenePlanning";
}


bool SceneGoalOriented::loadTextures(char* filename_bg, char* filename_coin)
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
	//coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}