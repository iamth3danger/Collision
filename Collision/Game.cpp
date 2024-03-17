#include "Game.h"

Game::Game()
{}
Game::~Game()
{}
const int size = 50;

bool isPause = true;

SDL_Renderer* Game::renderer = nullptr;
platform* red;
platform* blue;
platform* green;
platform* yellow;
platform* arr[50];


SDL_Surface* surf;
SDL_Event event;

int count = 0;
int frameCount = 0;

const int Game::width = 800;
const int Game::height = 640;
std::vector<std::string> platform::vec = {"start"};

int IDGenerator::_id = 0;


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else { 
		isRunning = false; 
	}
	

	for (int i = 0; i < size; i++) {

		int xPos = 125 *(i % 6) + 50;
		int yPos = 125 * (i / 6) + 50;

		
		std::string id[] = { "red", "blue", "green", "yellow", "purple", "orange"};

		Color* color = new Color(id[i % 6]);
		Velocity* velocity = new Velocity();

		arr[i] = new platform(Game::renderer, xPos, yPos, velocity, color);

	}
	
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			isPause = !isPause;
			break;
		default:
			break;
		}
	default:
		break;
	}

}

void Game::update()
{
	frameCount++;

	if (isPause) {
		for (int i = 0; i < size; i++) {
			arr[i]->update();
		}
	}
	
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] != arr[j]) {
				arr[i]->collisionManager(arr[j]);
			}
		}
		arr[i]->checkWall();
	}
	
	for (int i = 0; i < size; i++) {
		arr[i]->resetCollision(frameCount);
	}
}

void Game::render()
{

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	

	
	for (int i = 0; i < size; i++) {
		arr[i]->render();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}