#include "common.h"
#include <string.h>
using namespace std;
extern Game game;
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
extern Star stars[MAX_STARS];
extern SDL_Rect play;
extern SDL_Rect highscore;
extern SDL_Rect out;
extern SDL_Rect mouse;
extern SDL_Rect destBackground;
void prepareScene()
{
	SDL_SetRenderDrawColor(game.renderer, 32, 32, 32, 255);
	SDL_RenderClear(game.renderer);
}
void presentScene()
{
	SDL_RenderPresent(game.renderer);
}
void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
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
		int c = 32 * stars[i].speed;//Thêm hiệu ứng màu dựa vào tốc độ của sao
		SDL_SetRenderDrawColor(game.renderer, c, c, c, 255);
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
	SDL_RenderCopy(game.renderer, menuBackground, NULL, &Background);
	if (collision(mouse.x, mouse.y, 1, 1, play.x, play.y, play.w, play.h))
	{	
		blit(playTexture2, SCREEN_WIDTH/2-destBackground.w/2, 300);
	}
	else blit(playTexture1, SCREEN_WIDTH/2-destBackground.w/2, 300);     
	if (collision(mouse.x, mouse.y, 1, 1, highscore.x, highscore.y, highscore.w, highscore.h))
	{
		blit(highscoreTexture2, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h+36);
	}
	else blit(highscoreTexture1, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h+36);
	if (collision(mouse.x, mouse.y, 1, 1, out.x, out.y, out.w, out.h))
	{
		blit(exitTexture2, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h*2+72);
	}
	else blit(exitTexture1, SCREEN_WIDTH/2-destBackground.w/2, 300+destBackground.h*2+72);
}
void drawShard()
{
    Shard *d;
    for (d = stage.shardHead.next ; d != NULL ; d = d->next)
    {
        blitRect(d->texture, &d->rect, d->x, d->y);
    }
}
void drawExplosions()
{
    Explosion *e;
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
        blitRect(explosionTexture,&dest,e->x-e->dx,e->y-e->dy);
    }
    SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_NONE);
}
void drawFighters()
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
}
void drawBullets()
{
	Entity *b;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}
}
void drawMeteors()
{
	Entity *t;
	for (t = stage.meteorHead.next; t != NULL; t = t->next)
	{
		blit(t->texture, t->x, t->y);
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
		dest.w =m->w;
		dest.h =m->h;
		SDL_RenderCopy(game.renderer,m->texture, NULL, &dest);
	}
}
void drawPointsPods()
{
    Entity *e;
    for (e = stage.pointsHead.next ; e != NULL ; e = e->next)
    {
        blit(e->texture, e->x, e->y);
    }
}