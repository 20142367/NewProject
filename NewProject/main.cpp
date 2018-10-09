#include "Game.h"

Game* g_game = 0;	// our Game object


int main(int argc, char* argv[]) {

	srand((unsigned int)time(NULL));

	g_game = new Game();

	g_game->init("MiniProject", 100, 100, 500, 500, false);

	while (g_game->running()) {
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}
	g_game->clean();

//	srand((unsigned int)time(NULL));
//	rand();


	return 0;
}