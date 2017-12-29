#include "Agent.h"
#include "StateBank.h"
#include "StateHome.h"
#include "StateMine.h"
#include "StateSaloon.h"
using namespace std;

Agent::Agent() : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
	             mass(0.1f),
	             max_force(150),
	             max_velocity(200),
	             orientation(0),
	             color({ 255,255,255,255 }),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
	             draw_sprite(false)
{
	steering_behavior = new SteeringBehavior;
	state_home = new StateHome(this,Vector2D(20,19));
	state_saloon = new StateSaloon(this, Vector2D(33, 19));
	state_bank = new StateBank(this, Vector2D(7, 19));
	state_mine = new StateMine(this, Vector2D(3, 3));
	maxEnergyTime = 10;
	maxThirstTime = 30;
	arrived = true;
	energy = 10;
	//mineEntranceCoords = Vector2D(2, 4);
	//bankCoords = Vector2D(7, 19);
	houseCoords= Vector2D(20, 19);
	//saloonCoords= Vector2D(34, 19);


}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behavior)
		delete (steering_behavior);
}

void Agent::SetCurrentGoldPiece(Gold* gold) {
	currentGoldPiece = gold;
}

Gold* Agent::GetCurrentGoldPiece() {
	return currentGoldPiece;
}

void Agent::ChangeState(int state) {
	std::cout << "Se llama a ChangeState" << std::endl;
	if(currentState!=nullptr)
	currentState->Exit();

	switch (state) {	
	//HOME
	case 0:
		currentState = state_home;
		std::cout << "home" << std::endl;

		break;
	//MINE
	case 1:
		currentState = state_mine;
		std::cout << "mine" << std::endl;

		break;
	//BANK
	case 2:
		currentState = state_bank;
		std::cout << "bank" << std::endl;

		break;
	//SALOON
	case 3:
		currentState = state_saloon;
		std::cout << "saloon" << std::endl;

		break;
	default:
		
		break;
	}
	currentState->Enter();
}

SteeringBehavior * Agent::Behavior()
{
	return steering_behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::setMass(float _mass)
{
	mass = _mass;
}

void Agent::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color = { r, g, b, a };
}

//void Agent::UpdateStats(float dtime){
//	timerThirst += dtime;
//	timerEnergy += dtime;
//
//	if (timerThirst >= maxThirstTime) {
//		timerThirst = 0;
//		thirst++;
//	}
//	if (timerEnergy >= maxEnergyTime) {
//		timerEnergy = 0;
//		energy--;
//	}
//
//	//cout << thirst << endl;
//}

void Agent::Think(float dtime) {
	//UpdateStats(dtime);
	if (currentState != nullptr) {
		//std::cout << "Llama al update" << std::endl;
		currentState->Update(dtime);
	}
	else {
		//cout << "agent update:" << endl;

	}
}

void Agent::update(Vector2D steering_force, float dtime, SDL_Event *event)
{
	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}


	Vector2D acceleration = steering_force / mass;
	velocity = velocity + acceleration * dtime;
	velocity = velocity.Truncate(max_velocity);

	position = position + velocity * dtime;


	// Update orientation
	if (velocity.Length()>0)
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);


	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;


}

void Agent::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (max_velocity)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}

int Agent::GetMaxThirst() {
	return maxThirst;
}
int Agent::GetThirst() {
	return thirst;
}

int Agent::GetEnergy() {
	return energy;
}
int Agent::GetMaxEnergy() {
	return maxEnergy;
}
int Agent::GetCoinsInBank() {
	return coinsInBank;
}
int Agent::GetWealthThreshold() {
	return wealthThreshold;
}
int Agent::GetGoldPieces() {
	return goldPieces;
}
int Agent::GetMaxGoldPieces() {
	return maxGoldPieces;
}

State* Agent::GetCurrentState() {
	return currentState;
}

void Agent::SetThirst(int a) {
	thirst = a;
}
void Agent::SetEnergy(int a) {
	energy = a;
}

void Agent::SetCoinsInBank(int a) {
	coinsInBank = a;
}
void Agent::SetWealthThreshold(int a) {
	wealthThreshold = a;
}
void Agent::SetGoldPieces(int a) {
	goldPieces = a;
}

void Agent::SetDestiny(Vector2D a) {
	destiny = a;
}

Vector2D Agent::GetDestiny() {
	return destiny;
}
