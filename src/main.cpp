#include "common.h"
Game game;
Highscores highscores;
Stage stage;
int toggle=0;
using namespace std;
int main(int argc, char *argv[])
{
	memset(&game, 0, sizeof(Game));
	initSDL();
	atexit(cleanup);
	initGame();
	initMouse();
	while (1)
	{	
		if(toggle==1)
   		Mix_PauseMusic();
   		else if(toggle==0)
   		Mix_ResumeMusic();
		updateMouse();
		prepareScene();
		doInput();
		game.delegate.logic();
		game.delegate.draw();
		drawMouse();
		presentScene();
		SDL_Delay(16);
	}

	return 0;
}
