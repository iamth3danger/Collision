#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Color.h"
#include <string>
#include <vector>
#include "Velocity.h"
#include <iostream>
#include <cmath>
#include <iterator>

class platform {

public:
	float x, y, vX, vY;
	int r, g, b;  
	const int size = 25;
	float collisionX = -1, collisionY = -1;
	bool inCollision;

	static std::vector<std::string> vec;
	std::string id;

	SDL_Renderer* renderer;
	std::string file;

	platform(SDL_Renderer* renderer, float x, float y, Velocity* velocity, Color* color);

	bool checkCollision(platform* square);
	void collisionManager(platform* other);

	void checkWall();

	void render();
	void update();

	void anglelessCollision(platform* other);
	void resetCollision(int count);

	int getLeft();
	int getRight();
	int getTop();
	int getBottom();

private:

};

class IDGenerator {
public:
	static int _id;
	uint32_t next() { return _id++; }
private:
};