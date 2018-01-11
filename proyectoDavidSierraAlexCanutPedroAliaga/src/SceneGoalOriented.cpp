#define NullVector Vector2D{-1-1}
#include "SceneGoalOriented.h"
#include "GoalOrientedAgent.h"
#include "WorldState.h"
#include <time.h>
using namespace std;


//static inline bool operator < (const GoalOrientedAction& lhs, const GoalOrientedAction& rhs) {
//	return lhs.cost>rhs.cost;
//}

static inline bool operator < (const WorldState& lhs, const WorldState& rhs) {
	return lhs.acumulatedCost>rhs.acumulatedCost;
}

int SceneGoalOriented::ActionHeuristic(WorldState* lhs, WorldState* rhs) {
	int temp = 0;
	for (int i = 0; i < 8; i++) {
		if (lhs->conditions[i] != 2 && rhs->conditions[i] != 2 && lhs->conditions[i] != rhs->conditions[i]) {
			temp++;
		}
	}
	return temp;
}

SceneGoalOriented::SceneGoalOriented()
{
	loadTextures("../res/maze.png", "../res/coin.png");

	//srand((unsigned int)time(NULL));
	srand(time(NULL));

	GoalOrientedAgent *agent = new GoalOrientedAgent;

	//agent->loadSpriteTexture("../res/soldier.png", 4);

	agents.push_back(agent);

	foundPlan = false;

	goalWorld = WorldState::GenerateRandomState();
	std::cout << "World state to go to ";
	goalWorld->DebugBits();
	ThinkAStar();

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
	if (foundPlan) {
		if (agents[0]->currentWorld != goalWorld) {

			agents[0]->currentWorld->DebugBits();
			actionsToComplete[agents[0]->GetPlanIndex()]->Update(agents[0]);
			std::cout << "Action done now: " << std::endl;
			agents[0]->currentWorld->DebugBits();

			//agents[0]->SetPlanIndex(agents[0]->GetPlanIndex()+1);

		}
		else {
			foundPlan = false;
			agents[0]->SetPlanIndex(0);

		}
	}
}

void SceneGoalOriented::ClearAStar() {
	foundPlan = false;
	while (!frontier.empty()) {
		frontier.pop();
	}

	for (std::unordered_map<WorldState*, WorldState*>::iterator it = came_from.begin(); it != came_from.end(); ++it) {
		it->second = nullptr;
	}

	for (std::unordered_map<WorldState*, float>::iterator it = cost_so_far.begin(); it != cost_so_far.end(); ++it) {
		it->second = -1;
	}
}


void SceneGoalOriented::ThinkAStar() {

	ClearAStar();

	//ES POSIBLE QUE EN ESTAS CUATRO LÏNEAS ALGO PATINE
	agents[0]->currentWorld->createdBy = agents[0]->idleAction;
	frontier.push(agents[0]->currentWorld);
	came_from[agents[0]->currentWorld] = agents[0]->currentWorld;
	cost_so_far[agents[0]->currentWorld] = 0;
	
	WorldState* current;

	std::vector<GoalOrientedAction*> availableActions;
	availableActions.push_back(agents[0]->aimAction);
	availableActions.push_back(agents[0]->approachAction);
	availableActions.push_back(agents[0]->blowUpAction);
	availableActions.push_back(agents[0]->exploreAction);
	availableActions.push_back(agents[0]->reloadAction);
	availableActions.push_back(agents[0]->runAwayAction);
	availableActions.push_back(agents[0]->shootAction);

	//LAS DOS LINEAS BAOJ ESTO NO LAS TENGO CLARAS
	current = agents[0]->currentWorld;
	came_from[current] = agents[0]->currentWorld;

	while (!frontier.empty()) {
		current = frontier.top();

		if (WorldState::Equals(*current, *goalWorld)) {
			goalWorld->createdBy = current->createdBy;
			break;
		}

		std::vector<WorldState>neighbours;

		for (int i = 0; i < 7; i++) {
			if (WorldState::isDoable(*current, availableActions[i])) {
				neighbours.push_back(WorldState(availableActions[i]->preConditions, availableActions[i]));

			}
		}

		for (int i = 0; i < neighbours.size(); i++) {
			int newCost = cost_so_far[current] + neighbours[i].createdBy->cost + ActionHeuristic(current, &neighbours[i]);
			if (cost_so_far[&neighbours[i]] == -1 || newCost < cost_so_far[&neighbours[i]]) {
				std::cout << "Add" << std::endl;
				cost_so_far[&neighbours[i]] = newCost;
				neighbours[i].acumulatedCost = newCost;
				frontier.push(&neighbours[i]);
				came_from[&neighbours[i]] = current;
			}
		}
		frontier.pop();
	}

	goalWorld->createdBy = current->createdBy;

	current = goalWorld;

	actionsToComplete.push_back(current->createdBy);


	while (!WorldState::Equals(*current, *agents[0]->currentWorld)) {
		//AQUI PEGA UNA NULLREFERENCE DEL CARAJO
		current = came_from[current];
		actionsToComplete.insert(actionsToComplete.begin(), current->createdBy);
	}
	foundPlan = true;

}

void SceneGoalOriented::DrawTexts() {
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