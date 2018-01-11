#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Vector2D.h"
#include <string>
#include "SDL_SimpleApp.h"

class Text {
private:
	Vector2D position;
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;
	std::string text;
public:
	Text();
	Text(std::string txt, Vector2D pos, int size);
	void DrawText(bool);
	void DrawText();
	void SetPosition(Vector2D);
	void SetText(std::string a);
};