#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "Velocity.h"
#include "Color.h"
#include "platform.h"
#include <cstdlib>
#include <string>

class Game
{

public:
	Game();
	~Game();
	static const int width;
	static const int height;
	static SDL_Renderer* renderer;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();


	void update();
	void render();
	void clean();

	bool running() { return isRunning; }



private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	//SDL_Renderer* renderer;

};

