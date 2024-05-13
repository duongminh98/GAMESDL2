#include "common.h"
extern SDL_Texture *playTexture1;
SDL_Rect destBackground;
SDL_Rect play;
SDL_Rect highscore;
SDL_Rect out;
extern Game game;
extern SDL_Rect mouse;
static void logic();
static void draw();
void initButton()
{	
	SDL_QueryTexture(playTexture1, NULL, NULL, &destBackground.w, &destBackground.h);
	play.w=destBackground.w;
	play.h=destBackground.h;
	highscore.w=destBackground.w;
	highscore.h=destBackground.h;
	out.w=destBackground.w;
	out.h=destBackground.h;
	game.delegate.logic= logic;
	game.delegate.draw = draw;
}
static void logic()
{	
	if (collision(mouse.x, mouse.y, 1, 1, play.x, play.y, play.w, play.h) and game.mouse[0])
	{
		playSound(SND_MENU, CH_MENU);
		initStage();
	}
	else if (collision(mouse.x, mouse.y, 1, 1, highscore.x, highscore.y, highscore.w, highscore.h)and game.mouse[0])
	{
		playSound(SND_MENU, CH_MENU);
		initHighscores();
	}
	else if (collision(mouse.x,mouse.y,1,1,out.x,out.y,out.w,out.h)and game.mouse[0])
	{
		playSound(SND_MENU, CH_MENU);
		cleanup();
	}
}
static void draw()
{	
	drawButton();
}