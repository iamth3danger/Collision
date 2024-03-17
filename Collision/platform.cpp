#include "platform.h"



platform::platform(SDL_Renderer* renderer, float x, float y, Velocity* velocity, Color* color)
{
	IDGenerator::_id++;
	this->id = std::to_string(IDGenerator::_id);
	this->r = color->r;
	this->g = color->g;
	this->b = color->b;
	this->renderer = renderer;
	this->x = x;
	this->y = y;
	this->vX = velocity->vX;
	this->vY = velocity->vY;
}

void platform::collisionManager(platform* other) {	
	if (this->checkCollision(other) && this->inCollision == false && other->inCollision == false) {
		
		
		this->inCollision = true;
		other->inCollision = true;

		if (vec.back().compare(this->id + " collided with " + other->id) != 0 && vec.back().compare(other->id + " collided with " + this->id) != 0) {
			this->anglelessCollision(other);
		}
		
		vec.push_back(this->id + " collided with " + other->id);
	}

}



bool platform::checkCollision(platform* square)
{

	bool AisToTheRightOfB = this->getLeft() > square->getRight();
	bool AisToTheLeftOfB = this->getRight() < square->getLeft();
	bool AisAboveB = this->getBottom() < square->getTop();
	bool AisBelowB = this->getTop() > square->getBottom();
	return !(AisToTheRightOfB
		|| AisToTheLeftOfB
		|| AisAboveB
		|| AisBelowB);
	
}

void platform::checkWall() {

	if (x <= 5 && vX < 0) {
		vec.push_back("wall");
		vX *= -1;
	}

	if (x >= 800 - (1.5 * size) && vX > 0)
	{
		vec.push_back("wall");
		vX *= -1;
	}


	if (y <= 5 && vY < 0)
	{
		vec.push_back("wall");
		vY *= -1;
	}

	if (y >= 600 - (size) && vY > 0)
	{
		vec.push_back("wall");
		vY *= -1;
	}
}

void platform::update() {
	
	float timeDelta = 1.f / 120;
	x += vX * timeDelta;
	y += vY * timeDelta;
}
void platform::render() {

	SDL_Rect destR;
	destR.x = (int) x;
	destR.y = (int) y;
	destR.w = destR.h = this->size;

	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &destR);


}


void platform::anglelessCollision(platform* other) {


	float m1, m2;
	float center1X = this->x + (size / 2.0);
	float center1Y = this->y + (size / 2.0);

	float center2X = other->x + (size / 2.0);
	float center2Y = other->y + (size / 2.0);

	float gamma = atan2((center2Y - center1Y), (center2X - center1X));
	if (this->size >= other->size) {
		m1 = 1;
		m2 = other->size / ((float)this->size);
	}
	else {
		m2 = 1;
		m1 = this->size / ((float)other->size);
	}

	const float initDot = (this->vX * other->vX) + (this->vY * other->vY);
	
	const float scalar1 = ((2 * m2) / (m1 + m2)) *
		(((this->vX - other->vX) * (center1X - center2X) + (this->vY - other->vY) * (center1Y - center2Y)) /
		(pow(center1X - center2X, 2) + pow(center1Y - center2Y, 2)));

	const float scalar2 = ((2 * m1) / (m1 + m2)) *
		(((other->vX - this->vX) * (center2X - center1X) + (other->vY - this->vY) * (center2Y - center1Y)) /
		(pow(center2X - center1X, 2) + pow(center2Y - center1Y, 2)));

	this->vX -= (scalar1 * (center1X - center2X));
	this->vY -= (scalar1 * (center1Y - center2Y));


	other->vX -= (scalar2 * (center2X - center1X));
	other->vY -= (scalar2 * (center2Y - center1Y));
	const float finalDot = (this->vX * other->vX) + (this->vY * other->vY);

}




void platform::resetCollision(int count) {
	if (count % 5 == 0)
		this->inCollision = false;
}
int platform::getLeft() { return this->x; }

int platform::getRight() { return this->x + this->size; }

int platform::getTop() { return this->y; }

int platform::getBottom() { return this->y + size; }

