#include "Velocity.h"

Velocity::Velocity() {
	int xFlip = rand() % 2 + 1;
	int yFlip = rand() % 2 + 1;
	int posX;
	if (xFlip == 1) {
		posX = 1;
	}
	else {
		posX = -1;
	}
	int posY;
	if (yFlip == 1) {
		posY = 1;
	}
	else {
		posY = -1;
	}
	//this->vX = 0;
	//this->vY = 0;
	this->vX = rand() % 6 * posX * 90;
	this->vY = rand() % 6 * posY * 90;
}