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

	GoalOrientedAgent *agent = new GoalOrientedAgent();

	//agent->loadSpriteTexture("../res/soldier.png", 4);

	agents.push_back(agent);

	foundPlan = false;

	//goalWorld = WorldState::GenerateRandomState();

	int a[8] = { 1, 1, 0, 0, 0, 0, 0, 0};
	goalWorld = new WorldState(a);

	/*	preConditions[0] = 1; //Agent viu
	preConditions[1] = 1; //Té arma
	preConditions[2] = 1; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 1; //Enemic visible
	preConditions[5] = 1; //Enemic alineat
	preConditions[6] = 1; //Enemic a prop
	preConditions[7] = 1; //Enemic viu*/

	agents[0]->currentWorld->conditions[0] = 1;
	agents[0]->currentWorld->conditions[1] = 1;
	agents[0]->currentWorld->conditions[2] = 0;
	agents[0]->currentWorld->conditions[3] = 0;
	agents[0]->currentWorld->conditions[4] = 1;
	agents[0]->currentWorld->conditions[5] = 1;
	agents[0]->currentWorld->conditions[6] = 1;
	agents[0]->currentWorld->conditions[7] = 1;



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
			if (agents[0]->GetPlanIndex() < actionsToComplete.size()-1) {
				if (actionsToComplete[agents[0]->GetPlanIndex()]!=nullptr) {
					agents[0]->currentWorld->DebugBits();
					actionsToComplete[agents[0]->GetPlanIndex()]->Update(agents[0]);
					std::cout << "Action done now: " << std::endl;
					agents[0]->currentWorld->DebugBits();
				}
				else {
					agents[0]->SetPlanIndex(agents[0]->GetPlanIndex() + 1);
				}
				//agents[0]->SetPlanIndex(agents[0]->GetPlanIndex()+1);
			}
			else {
				std::cout << "Plan Finish" << std::endl;
			}
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
		it->second = 0;
	}
}


void SceneGoalOriented::ThinkAStar() {


	ClearAStar();

	frontier.push(agents[0]->currentWorld);
	cost_so_far[agents[0]->currentWorld] = 0;

	WorldState* current;



	std::vector<GoalOrientedAction*> availableActions;
	availableActions.push_back(agents[0]->aimAction);
	availableActions.push_back(agents[0]->approachAction);
	//availableActions.push_back(agents[0]->blowUpAction);
	availableActions.push_back(agents[0]->exploreAction);
	availableActions.push_back(agents[0]->reloadAction);
	availableActions.push_back(agents[0]->runAwayAction);
	availableActions.push_back(agents[0]->shootAction);

	while (!frontier.empty()) {
		current = frontier.top();

		if (WorldState::Equals(*current, *goalWorld)) {

			came_from[goalWorld] = came_from[current];

			goalWorld->createdBy = current->createdBy;

			break;
		}

		std::vector<WorldState*>neighbours;

		for (int i = 0; i < availableActions.size(); i++) {
			if (WorldState::isDoable(*current, availableActions[i])) {
				if (createdWorldState[WorldState::GetBits(WorldState::ApplyPostConditions(current->conditions, availableActions[i]->postConditions)->conditions, 8)] != nullptr) {
					std::cout << "Exists" << std::endl;
				}
				else {
					WorldState* temp = new WorldState(WorldState::ApplyPostConditions(current->conditions, availableActions[i]->postConditions)->conditions, availableActions[i]);
					neighbours.push_back(temp);
					createdWorldState[WorldState::GetBits(temp->conditions, 8)] = temp;

				}
			}
		}
		frontier.pop();

		for (int i = 0; i < neighbours.size(); i++) {
			int newCost = cost_so_far[current] + neighbours[i]->createdBy->cost + ActionHeuristic(current, neighbours[i]);
			if (cost_so_far[neighbours[i]] == 0 || newCost < cost_so_far[neighbours[i]]) {
				//std::cout << "Add" << std::endl;
				cost_so_far[neighbours[i]] = newCost;
				neighbours[i]->acumulatedCost = newCost;
				frontier.push(neighbours[i]);
				came_from[neighbours[i]] = current;
			}
		}
		//frontier.pop();
	}

	//goalWorld->createdBy = current->createdBy;

	if (createdWorldState[WorldState::GetBits(goalWorld->conditions, 8)] != nullptr) {
		goalWorld = createdWorldState[WorldState::GetBits(goalWorld->conditions, 8)];
		mustAct = true;
	}
	else {
		mustAct = false;
	}
	if (mustAct) {

		came_from[goalWorld] = came_from[current];
		current = goalWorld;

		actionsToComplete.push_back(current->createdBy);


		while (!WorldState::Equals(*current, *agents[0]->currentWorld)) {
			//AQUI PEGA UNA NULLREFERENCE DEL CARAJO
			if (came_from[current] != nullptr&&current->createdBy!=nullptr) {
				current = came_from[current];
				actionsToComplete.insert(actionsToComplete.begin(), current->createdBy);
			}
			else {
				std::cout << "Break" << endl;
				break;
			}
		}
		foundPlan = true;

		//TODO DELETE PUNTEROSCOÑ

	}
	else {
		std::cout << "Plan not found" << std::endl;
		agents[0]->shootAction->Update(agents[0]);

	}
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