#include "Gold.h"
#include <stdlib.h>

Gold::Gold(Vector2D pos) {
	position = pos;
	amount = (int)(rand() % 10);
	mined = false;
}