#include "common.h"
class Game{
    public:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    int mouse[1];
    char inputText[MAX_LINE_LENGTH];
    void MainLogic()
    {
    	doStarfield();
		doPlayer();
		doEnemies();
		doFighters();
    	doMeteors();
		doBullets(); 
    	doMissile();
		doExplosions();
		doShard();
		doPointsPods();
    	spawnEnemies();
    }
    void MainDraw()
    {
    	drawBackground();
		drawStarfield();
		drawPointsPods();
		drawFighters();
    	drawBullets();
    	drawMeteors();
    	drawShard();
		drawExplosions();
    	drawMissile();
		drawHud();
    }
};
int main(int argc, char *argv[]);
