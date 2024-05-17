#include "common.h"
extern Entity *player;
extern Stage stage;
extern SDL_Texture *bulletTexture;
extern SDL_Texture *alienBulletTexture;
void fireBullet()
{
	Entity *bullet;
	bullet = new Entity;
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;
	bullet->x = player->x;
	bullet->y = player->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->alive = 1;
	bullet->side = SIDE_PLAYER;
	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	bullet->y += (player->h / 2) - (bullet->h / 2);
	player->reload = 16;
}
void doBullets()
{
	Entity *b, *prev;
	prev = &stage.bulletHead;
	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;
		if (bulletHitFighter(b) or b->x < -b->w or b->y < -b->h or b->x > SCREEN_WIDTH or b->y > SCREEN_HEIGHT)
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}
			prev->next = b->next;
			free(b);
			b = prev;
		}
		prev = b;
	}
}
int bulletHitFighter(Entity *b)
{
	Entity *e;
	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e->side != b->side and collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
		{	
			b->alive = 0;
			e->alive = 0;
			addExplosions(e->x, e->y, 32);
			addShard(e);
			if (e == player)
    			{
        			playSound(SND_PLAYER_DIE, CH_PLAYER);

    			}
    		else
    			{	
    				addPointsPod(e->x + e->w / 2, e->y + e->h / 2);
        			playSound(SND_ALIEN_DIE, CH_ANY);
    			}
			return 1;
		}
	}
	return 0;
}
void fireAlienBullet(Entity *e)
{
    Entity *bullet;
    bullet =new Entity;
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;
    bullet->x = e->x;
    bullet->y = e->y;
    bullet->alive = 1;
    bullet->texture = alienBulletTexture;
    bullet->side = SIDE_ENEMY;
    aim(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);
    bullet->dx *= ALIEN_BULLET_SPEED;
    bullet->dy *= ALIEN_BULLET_SPEED;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    bullet->x += (e->w / 2) - (bullet->w / 2);
    bullet->y += (e->h / 2) - (bullet->h / 2);
    e->reload = 60;
    
}