#include "common.h"
#include <string.h>
using namespace std;
extern Game game;
extern Entity *player;
extern Stage stage;
extern SDL_Texture *bulletTexture;
extern SDL_Texture *enemyTexture;
extern SDL_Texture *alienBulletTexture;
extern SDL_Texture *playerTexture;
extern SDL_Texture *explosionTexture;
extern SDL_Texture *pointsTexture;
extern SDL_Texture *playTexture1;
extern SDL_Texture *highscoreTexture1;
extern SDL_Texture *exitTexture1;
extern SDL_Texture *playTexture2;
extern SDL_Texture *highscoreTexture2;
extern SDL_Texture *exitTexture2;
extern SDL_Texture *menuBackground;
extern SDL_Texture *meteoriteTexture;
extern SDL_Texture *missileTexture;
extern SDL_Texture *background;
extern SDL_Texture *fontTexture;
extern SDL_Texture *missileFlame;
extern SDL_Texture *enginePlayer;
extern SDL_Texture *engineEnemy;
extern SDL_Texture *flamePlayer;
extern SDL_Texture *flameEnemy;
extern SDL_Texture *soundOnTexture;
extern SDL_Texture *soundOffTexture;
extern Star stars[MAX_STARS];
extern SDL_Rect play;
extern SDL_Rect highscore;
extern SDL_Rect out;
extern SDL_Rect mouse;
extern SDL_Rect destBackground;
extern TTF_Font 	*ourFont;
SDL_Rect sound;
extern int toggle;
void prepareScene()
{
	SDL_SetRenderDrawColor(game.renderer, 32, 32, 32, 255);
	SDL_RenderClear(game.renderer);
}
void presentScene()
{
	SDL_RenderPresent(game.renderer);
}
void drawAtXY(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}
void drawAtXYPart(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;
	SDL_RenderCopy(game.renderer, texture, src, &dest);
}
void drawStarfield()
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		SDL_SetRenderDrawColor(game.renderer, 0, 255, 255, 255);
		SDL_RenderDrawLine(game.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
	}
}
void drawBackground()
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = SCREEN_WIDTH;
	dest.h = SCREEN_HEIGHT;
	SDL_RenderCopy(game.renderer, background, NULL, &dest);
}
void drawButton()
{	
	
	SDL_Rect Background;
	Background.x = 0;
	Background.y = 0;
	Background.w = SCREEN_WIDTH;
	Background.h = SCREEN_HEIGHT;
	play.x=SCREEN_WIDTH/2-destBackground.w/2;
	play.y=300;
	highscore.x=SCREEN_WIDTH/2-destBackground.w/2;
	highscore.y=300+destBackground.h+36;
	out.x=SCREEN_WIDTH/2-destBackground.w/2;
	out.y=300+destBackground.h*2+72;
	SDL_QueryTexture(soundOnTexture, NULL, NULL, &sound.w, &sound.h);
	sound.x=0;
	sound.y=SCREEN_HEIGHT-sound.h;
	SDL_RenderCopy(game.renderer, menuBackground, NULL, &Background);
	if (collision(mouse.x, mouse.y, 1, 1, play.x, play.y, play.w, play.h))
	{	
		drawAtXY(playTexture2, SCREEN_WIDTH/2-destBackground.w/2, 300);
	}
	else drawAtXY(playTexture1, SCREEN_WIDTH/2-destBackground.w/2, 300);     
	if (collision(mouse.x, mouse.y, 1, 1, highscore.x, highscore.y, highscore.w, highscore.h))
	{
		drawAtXY(highscoreTexture2, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h+36);
	}
	else drawAtXY(highscoreTexture1, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h+36);
	if (collision(mouse.x, mouse.y, 1, 1, out.x, out.y, out.w, out.h))
	{
		drawAtXY(exitTexture2, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h*2+72);
	}
	else drawAtXY(exitTexture1, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h*2+72);
	if(toggle==0)drawAtXY(soundOnTexture, sound.x, sound.y);
	else drawAtXY(soundOffTexture, sound.x, sound.y);
	if (collision(mouse.x, mouse.y, 1, 1, sound.x, sound.y, sound.w, sound.h) and game.mouse[0])
	{
		game.mouse[0]=0;
		if(toggle)toggle=0;
		else toggle=1;
	}
}
void drawShard()
{
   	Entity *d;
    for (d = stage.shardHead.next ; d != NULL ; d = d->next)
    {
        drawAtXYPart(d->texture, &d->rect, d->x, d->y);
    }
}
void drawExplosions()
{
    Entity *e;
    SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);
    for (e = stage.explosionHead.next ; e != NULL ; e = e->next)
    {
        SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(explosionTexture, e->a);
        SDL_Rect dest;
        dest.w=196;
        dest.h=190;
        dest.x=625;
        dest.y=36;
        //Thông số trên dựa theo thông số pixel của ảnh trong res
        drawAtXYPart(explosionTexture,&dest,e->x-e->dx,e->y-e->dy);
    }
    SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_NONE);
}
void drawFighters()
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		drawAtXY(e->texture, e->x, e->y);
		if(e!=player)
		{
			SDL_Rect dest1,dest2;
			SDL_QueryTexture(engineEnemy, NULL, NULL, &dest1.w, &dest1.h);
			dest1.w/=3.25;
			dest1.h/=3.25;
			dest1.x=e->x+e->w-10;
			dest1.y=e->y+e->h/2-dest1.h/2;
			SDL_RenderCopy(game.renderer,engineEnemy,NULL,&dest1);
			SDL_QueryTexture(flameEnemy, NULL, NULL, &dest2.w, &dest2.h);
			dest2.w/=3.25;
			dest2.h/=3.25;
			dest2.x=e->x+e->w+dest1.w-20;
			dest2.y=e->y+e->h/2-dest1.h/2+dest1.h/2-dest2.w/2;
			if(rand()%2)
				SDL_RenderCopy(game.renderer,flameEnemy,NULL,&dest2);
		}
		if(e==player)
		{		
				SDL_Rect dest1,dest2;
				SDL_QueryTexture(enginePlayer, NULL, NULL, &dest1.w, &dest1.h);
				dest1.w/=3.25;
				dest1.h/=3.25;
				dest1.x=e->x-dest1.w+10;
				dest1.y=e->y+e->h/2-dest1.h/2;
				SDL_RenderCopy(game.renderer,enginePlayer,NULL,&dest1);
			if(game.keyboard[SDL_SCANCODE_W] or game.keyboard[SDL_SCANCODE_S] or game.keyboard[SDL_SCANCODE_A] or game.keyboard[SDL_SCANCODE_D])
			{
				
				SDL_QueryTexture(flamePlayer, NULL, NULL, &dest2.w, &dest2.h);
				dest2.w/=1.25;
				dest2.h/=1.25;
				dest2.x=e->x-dest1.w-dest2.w+30;
				dest2.y=e->y+e->h/2-dest1.h/2+dest1.h/2-dest2.w/2;
				if(rand()%2)
				SDL_RenderCopy(game.renderer,flamePlayer,NULL,&dest2);
			}
		}

	}
}
void drawBullets()
{
	Entity *b;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		drawAtXY(b->texture, b->x, b->y);
	}
}
void drawMeteors()
{
	Entity *t;
	for (t = stage.meteorHead.next; t != NULL; t = t->next)
	{
		drawAtXY(t->texture, t->x, t->y);
	}
}
void drawMissile()
{
	Entity *m;
	for (m = stage.missileHead.next; m != NULL; m = m->next)
	{
		SDL_Rect dest;
		dest.x =m->x;
		dest.y =m->y;
		dest.w =m->w/1.5;
		dest.h =m->h/1.5;
		SDL_RenderCopy(game.renderer,m->texture, NULL, &dest);
		SDL_QueryTexture(missileFlame, NULL, NULL, &dest.w, &dest.h);
		dest.w*=2;
		dest.h*=2;
		dest.x =m->x+(m->w/1.5)-30;
		dest.y =m->y+(m->h/1.5)/2-dest.h/2;
		if(rand()%2)
		SDL_RenderCopy(game.renderer,missileFlame,NULL,&dest);
	}
}
void drawPointsPods()
{
    Entity *e;
    for (e = stage.pointsHead.next ; e != NULL ; e = e->next)
    {
        drawAtXY(e->texture, e->x, e->y);
    }
}