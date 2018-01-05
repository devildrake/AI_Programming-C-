#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "GoalOrientedAgent.h"
#include "Path.h"
#include "Graph.h"
#include <queue>
#include <map>
#include "Gold.h"
#include "Text.h"

class SceneGoalOriented :
	public Scene
{
public:
	SceneGoalOriented();
	~SceneGoalOriented();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	void DrawTexts();

private:
	SDL_Texture *background_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
	std::vector<GoalOrientedAgent*> agents;
};
