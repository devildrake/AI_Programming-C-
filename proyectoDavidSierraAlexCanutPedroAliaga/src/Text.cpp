#include "Text.h"

Text::Text(std::string txt, Vector2D pos, int size) : text(txt), position(pos) {
	font = TTF_OpenFont("../res/arial.ttf", size); //this opens a font style and sets a size
}
void Text::DrawText(bool a) {
	SDL_Color White;
	if (a) {
		 White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	}
	else {
		 White = { 255, 255, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	}

	surface = TTF_RenderText_Solid(font, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first	
	texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), surface); //now you can convert it into a texture
	SDL_Rect Message_rect; //create a rect
						   //Message_rect.x = position.x;  //controls the rect's x coordinate 
						   //Message_rect.y = position.y; // controls the rect's y coordinte
						   //Amb anchor
	Message_rect.x = position.x;// - surface->w / 2;
	Message_rect.y = position.y;// - surface->h / 2;

	Message_rect.w = surface->w; // controls the width of the rect
	Message_rect.h = surface->h; // controls the height of the rect

								 //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

								 //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(TheApp::Instance()->getRenderer(), texture, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

																					 //Don't forget too free your surface and texture
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

}

void Text::SetText(std::string a) {
	text = a;
}