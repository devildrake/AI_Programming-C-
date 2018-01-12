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

	for (int i = 0; i < 15; i++) {
		actionTexts[i].SetText(" ");
	}

	PlayerAlive.SetPosition(Vector2D{0,100});
	HasWeapon.SetPosition(Vector2D{ 0,150 });
	WeaponLoaded.SetPosition(Vector2D{ 0,200 });
	HasBomb.SetPosition(Vector2D{ 0,250 });
	EnemyInSight.SetPosition(Vector2D{ 0,300 });
	EnemyAligned.SetPosition(Vector2D{ 0,350 });
	EnemyNearby.SetPosition(Vector2D{ 0,400 });
	EnemyAlive.SetPosition(Vector2D{ 0,450 });






	system("cls");

	loadTextures("../res/maze.png", "../res/coin.png");

	//srand((unsigned int)time(NULL));
	srand(time(NULL));

	GoalOrientedAgent *agent = new GoalOrientedAgent();

	//agent->loadSpriteTexture("../res/soldier.png", 4);

	agents.push_back(agent);

	foundPlan = false;

	goalWorld = WorldState::GenerateRandomState();

	//int a[8] = { 1, 0, 1, 0, 0, 0, 0, 0};
	//goalWorld = new WorldState(a);

	/*	preConditions[0] = 1; //Agent viu
	preConditions[1] = 1; //Té arma
	preConditions[2] = 1; //Arma carregada
	preConditions[3] = 2; //Té bomba
	preConditions[4] = 1; //Enemic visible
	preConditions[5] = 1; //Enemic alineat
	preConditions[6] = 1; //Enemic a prop
	preConditions[7] = 1; //Enemic viu*/

	//agents[0]->currentWorld->conditions[0] = 1;
	//agents[0]->currentWorld->conditions[1] = rand() % 2;
	//agents[0]->currentWorld->conditions[2] = rand() % 2;
	//agents[0]->currentWorld->conditions[3] = 0;
	//agents[0]->currentWorld->conditions[4] = rand() % 2;
	//agents[0]->currentWorld->conditions[5] = rand() % 2;
	//agents[0]->currentWorld->conditions[6] = rand()%2;
	//agents[0]->currentWorld->conditions[7] = 1;

	agents[0]->ResetWorldView();

	startingWorld = new WorldState(agents[0]->currentWorld->conditions);

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

void SceneGoalOriented::Reset() {
	delete goalWorld;
	goalWorld = WorldState::GenerateRandomState();

	agents[0]->ResetWorldView();

	startingWorld = new WorldState(agents[0]->currentWorld->conditions);
	ThinkAStar();
	mustDebug = false;

}

void SceneGoalOriented::update(float dtime, SDL_Event *event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			Reset();
			break;
	default:
		break;
	}


	if (foundPlan&&!mustDebug) {
		//CAMBIADO AQUI

		for (int i = 0; i < 15; i++) {
			actionTexts[i].SetText(" ");
		}

		//agents[0]->SetPlanIndex(0);
		if (agents[0]->currentWorld != goalWorld) {


			for (int i = 0; i < actionsToComplete.size(); i++) {
				if (actionsToComplete[i] != nullptr) {
					actionTexts[i].SetText(actionsToComplete[i]->name);
					actionTexts[i].SetPosition(Vector2D{ 900,50.0f+40.0f*i });
				}
			}


			if (agents[0]->GetPlanIndex() < actionsToComplete.size()) {
				if (actionsToComplete[agents[0]->GetPlanIndex()]!=nullptr) {
					actionsToComplete[agents[0]->GetPlanIndex()]->Update(agents[0]);
				}
				//SI ES UNA ACTIVIDAD NULA SE AUMENTA EL INDEX
				else {
					agents[0]->SetPlanIndex(agents[0]->GetPlanIndex() + 1);
				}
				//agents[0]->SetPlanIndex(agents[0]->GetPlanIndex()+1);
			}
			else {
				if (!mustDebug) {
					actionsToComplete.clear();
					std::cout << "Plan Finish" << std::endl;
					mustDebug = true;
				}
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

	for (std::unordered_map<std::string, WorldState*>::iterator it = createdWorldState.begin(); it != createdWorldState.end(); ++it) {
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
	availableActions.push_back(agents[0]->blowUpAction);
	availableActions.push_back(agents[0]->exploreAction);
	availableActions.push_back(agents[0]->reloadAction);
	availableActions.push_back(agents[0]->runAwayAction);
	availableActions.push_back(agents[0]->shootAction);
	availableActions.push_back(agents[0]->throwWeaponAction);
	availableActions.push_back(agents[0]->pickUpWeaponAction);
	availableActions.push_back(agents[0]->unAimAction);
	availableActions.push_back(agents[0]->unLoadWeaponAction);
	availableActions.push_back(agents[0]->pickUpBombAction);


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
					//std::cout << "That world state already existed" << std::endl;
					neighbours.push_back(createdWorldState[WorldState::GetBits(WorldState::ApplyPostConditions(current->conditions, availableActions[i]->postConditions)->conditions, 8)]);

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
			int newCost = cost_so_far[current] + neighbours[i]->createdBy->cost + ActionHeuristic(goalWorld, neighbours[i]);
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
		goalWorld->createdBy = createdWorldState[WorldState::GetBits(goalWorld->conditions, 8)]->createdBy;
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
		//agents[0]->shootAction->Update(agents[0]);

	}

	//CLEAR DEL VECTOR DE PUNTEROS

	//for (std::vector<GoalOrientedAction*>::iterator it = availableActions.begin(); it != availableActions.end(); ++it) {
	//	delete (*it);
	//}
	//availableActions.clear();

}

inline std::string  BoolToString(bool b)
{
	return b ? "true" : "false";
}

void SceneGoalOriented::DrawTexts() {
	WorldData.SetText("Starting World                                                       Goal World                                                       Actions Completed");
	WorldData.DrawText();
	PlayerAlive.SetText("Player Alive:  " + BoolToString(startingWorld->conditions[0]) + "                                                   Player Alive:  " + BoolToString(goalWorld->conditions[0]));
	PlayerAlive.DrawText();
	HasWeapon.SetText("Has Weapon:  " + BoolToString(startingWorld->conditions[1]) + "                                                  Has Weapon:  " + BoolToString(goalWorld->conditions[1]));
	HasWeapon.DrawText();
	WeaponLoaded.SetText("Weapon Loaded:  " + BoolToString(startingWorld->conditions[2]) + "                                            Weapon Loaded:  " + BoolToString(goalWorld->conditions[2]));
	WeaponLoaded.DrawText();
	HasBomb.SetText("Has Bomb:  " + BoolToString(startingWorld->conditions[3]) + "                                                     Has Bomb:  " + BoolToString(goalWorld->conditions[3]));
	HasBomb.DrawText();
	EnemyInSight.SetText("Enemy In Sight:  " + BoolToString(startingWorld->conditions[4]) + "                                               Enemy In Sight:  " + BoolToString(goalWorld->conditions[4]));
	EnemyInSight.DrawText();
	EnemyAligned.SetText("Enemy Aligned:  " + BoolToString(startingWorld->conditions[5]) + "                                               Enemy Aligned:  " + BoolToString(goalWorld->conditions[5]));
	EnemyAligned.DrawText();
	EnemyNearby.SetText("Enemy Nearby:  " + BoolToString(startingWorld->conditions[6]) + "                                               Enemy Nearby:  " + BoolToString(goalWorld->conditions[6]));
	EnemyNearby.DrawText();
	EnemyAlive.SetText("Enemy Alive:  " + BoolToString(startingWorld->conditions[7]) + "                                                   Enemy Alive:  " + BoolToString(goalWorld->conditions[7]));
	EnemyAlive.DrawText();

	for (int i = 0; i < 15; i++) {
		actionTexts[i].DrawText();
	}
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