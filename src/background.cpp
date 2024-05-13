#include "common.h"
extern Game game;
Star stars[MAX_STARS];
void initStarfield()
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		stars[i].x=rand()%SCREEN_WIDTH;
		stars[i].y=rand()%SCREEN_HEIGHT;
		stars[i].speed=1+rand()%8;
	}
}
void doStarfield()
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		stars[i].x -= stars[i].speed;
		if (stars[i].x < 0)
		{
			stars[i].x = SCREEN_WIDTH + stars[i].x;
		}
	}
}