#include "Game.h"
Game* game = nullptr;

struct Timer
{
	Uint64 previous_ticks{};
	float elapsed_seconds{};

	void tick()
	{
		const Uint64 current_ticks{ SDL_GetPerformanceCounter() };
		const Uint64 delta{ current_ticks - previous_ticks };

		previous_ticks = current_ticks;
		static const Uint64 TICKS_PER_SECOND{ SDL_GetPerformanceFrequency() };
		elapsed_seconds = delta / static_cast<float>(TICKS_PER_SECOND);
		
	}
};


int main(int argc, char* argv[]) {

	game = new Game();

	game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	const int UPDATE_FREQUENCY{ 60 };
	const float CYCLE_TIME{ 1.0f / UPDATE_FREQUENCY };
	const float PHYSICS_CYCLE(1.0f / 180);
	static Timer system_timer;
	float accumulated_seconds{ 0.0f };
	float seconds{ 0.0f };
	int count = 0;
	SDL_Event event;

	while (game->running()) {

		system_timer.tick();
		accumulated_seconds += system_timer.elapsed_seconds;
		seconds += system_timer.elapsed_seconds;


		if (std::isgreater(seconds, PHYSICS_CYCLE)) {
			seconds = -PHYSICS_CYCLE;
			game->update();

		}

		if (std::isgreater(accumulated_seconds, CYCLE_TIME))
		{
			game->handleEvents();

			accumulated_seconds = -CYCLE_TIME;
			game->render();
		
		}

	}

	game->clean();

	return 0;

}
