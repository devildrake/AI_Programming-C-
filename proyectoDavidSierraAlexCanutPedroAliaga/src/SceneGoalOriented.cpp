#define NullVector Vector2D{-1-1}
#include "SceneGoalOriented.h"
#include "GoalOrientedAgent.h"

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

int SceneGoalOriented::ActionHeuristic(GoalOrientedAgent* a, GoalOrientedAction* b) {
	int temp = 0;

	if (b->preConditions[0] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::AGENT_ALIVE] == b->preConditions[0])) {
			temp++;
		}
	}
	if (b->preConditions[1] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::AGENT_HASWEAPON] == b->preConditions[1])) {
			temp++;
		}
	}
	if (b->preConditions[2] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::AGENT_WEAPONLOADED] == b->preConditions[2])) {
			temp++;
		}
	}
	if (b->preConditions[3] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::AGENT_HASBOMB] == b->preConditions[3])) {
			temp++;
		}
	}
	if (b->preConditions[4] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::ENEMY_INSIGHT] == b->preConditions[4])) {
			temp++;
		}
	}
	if (b->preConditions[5] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::ENEMY_ALIGNED] == b->preConditions[5])) {
			temp++;
		}
	}
	if (b->preConditions[6] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::ENEMY_NEAR] == b->preConditions[6])) {
			temp++;
		}
	}
	if (b->preConditions[7] != 2) {
		if (!(a->worldDictionary[GoalOrientedAgent::ENEMY_ALIVE] == b->preConditions[7])) {
			temp++;
		}
	}
	return temp;
}

void SceneGoalOriented::update(float dtime, SDL_Event *event)
{



}

void SceneGoalOriented::ClearAStar() {
	while (!frontier.empty()) {
		frontier.pop();
	}
	came_from.clear();
	cost_so_far.clear();
}

bool EqualWorld(int conditions[], GoalOrientedAgent* a) {
	bool temp = true;


	if (conditions[0] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::AGENT_ALIVE] == conditions[0])) {
			temp = false;
		}
	}
	if (conditions[1] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::AGENT_HASWEAPON] == conditions[1])) {
			temp = false;
		}
	}
	if (conditions[2] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::AGENT_WEAPONLOADED] == conditions[2])) {
			temp = false;
		}
	}
	if (conditions[3] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::AGENT_HASBOMB] == conditions[3])) {
			temp = false;
		}
	}
	if (conditions[4] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::ENEMY_INSIGHT] == conditions[4])) {
			temp = false;
		}
	}
	if (conditions[5] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::ENEMY_ALIGNED] == conditions[5])) {
			temp = false;
		}
	}
	if (conditions[6] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::ENEMY_NEAR] == conditions[6])) {
			temp = false;
		}
	}
	if (conditions[7] != 2) {
		if (!(a->goalWorld[GoalOrientedAgent::ENEMY_ALIVE] == conditions[7])) {
			temp = false;
		}
	}


	return temp;
}


void SceneGoalOriented::ThinkAStar() {
	ClearAStar();
	agents[0]->currentAction = agents[0]->idleAction;
	frontier.push(agents[0]->currentAction);
	GoalOrientedAction* current;
		
	cost_so_far[agents[0]->aimAction] = -1;
	cost_so_far[agents[0]->approachAction] = -1;
	cost_so_far[agents[0]->blowUpAction] = -1;
	cost_so_far[agents[0]->exploreAction] = -1;
	cost_so_far[agents[0]->idleAction] = -1;
	cost_so_far[agents[0]->reloadAction] = -1;
	cost_so_far[agents[0]->runAwayAction] = -1;
	cost_so_far[agents[0]->shootAction] = -1;

	while (!frontier.empty()) {
		current = frontier.top();

		if (current != nullptr) {
			if (EqualWorld(current->postConditions, agents[0])) {
				break;
			}
			std::vector<GoalOrientedAction*> possibleActions;
			if (current->id != agents[0]->aimAction->id) {
				possibleActions.push_back(agents[0]->aimAction);
			}
			if (current->id != agents[0]->approachAction->id) {
				possibleActions.push_back(agents[0]->approachAction);
			}
			if (current->id != agents[0]->blowUpAction->id) {
				possibleActions.push_back(agents[0]->blowUpAction);
			}
			if (current->id != agents[0]->exploreAction->id) {
				possibleActions.push_back(agents[0]->exploreAction);
			}
			if (current->id != agents[0]->idleAction->id) {
				possibleActions.push_back(agents[0]->idleAction);
			}
			if (current->id != agents[0]->reloadAction->id) {
				possibleActions.push_back(agents[0]->reloadAction);
			}
			if (current->id != agents[0]->runAwayAction->id) {
				possibleActions.push_back(agents[0]->runAwayAction);
			}
			if (current->id != agents[0]->shootAction->id) {
				possibleActions.push_back(agents[0]->shootAction);
			}

			for (int i = 0; i < possibleActions.size(); i++) {
				if (!current->CheckConditions(possibleActions[i]->preConditions, 8)) {
					possibleActions[i] = nullptr;
				}
			}

			for (int i = 0; i < possibleActions.size(); i++) {
				float newCost = cost_so_far[current] + current->cost+ActionHeuristic(agents[0],current);
				if (possibleActions[i] != nullptr&&(cost_so_far[possibleActions[i]] == -1)||newCost<cost_so_far[possibleActions[i]]) {
					cost_so_far[possibleActions[i]] = newCost;
					frontier.push(possibleActions[i]);
					came_from[possibleActions[i]] = current;
				}
			}



		}
		else {
			frontier.pop();
		}

	}
	//FIN DEL WHILE

	//REVERSE PATH
	//current = GoalOrientedAction;
	//path.points.push_back(cell2pix(current));

	//while (current != pix2cell(agents[0]->getPosition())) {
	//	current = cameFrom[current];
	//	//cout << current.x << " " << current.y << endl;
	//	path.points.insert(path.points.begin(), cell2pix(current));
	//}
	//foundPath = true;
	//ResetVisited();







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