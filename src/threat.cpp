#include "common.h"
extern Stage stage;
extern Game game;
extern Entity *player;
extern SDL_Texture *meteoriteTexture;
extern int meteorsSpawnTimer;
extern int missileSpawnTimer;
extern SDL_Texture *missileTexture;
using namespace std;
void doMeteors()
{
    Entity *t, *prev;
    prev = &stage.meteorHead;
    for (t = stage.meteorHead.next ; t != NULL ; t = t->next)
    {	
    	if(player!=NULL)aim(player->x + (player->w / 2), player->y + (player->h / 2), t->x, t->y, &t->dx, &t->dy);
        t->x += t->dx*METEOR_SPEED;
        t->y += t->dy*METEOR_SPEED;
        if(player!=NULL and collision(player->x, player->y, player->w, player->h, t->x, t->y, t->w, t->h))
        {
        	player->alive=0;
        	addExplosions(player->x, player->y, 32);
			addShard(player);
        	playSound(SND_PLAYER_DIE, CH_PLAYER);
        }
        if ((t->x < -t->w or t->y < -t->h or t->x > SCREEN_WIDTH or t->y > SCREEN_HEIGHT) or bulletHitMeteor(t))
        {
        	playSound(SND_ALIEN_DIE, CH_ANY);
            if (t == stage.meteorTail)
            {
                stage.meteorTail = prev;
            }
            prev->next = t->next;
            free(t);
            t = prev;
        }
        prev = t;
    }
}
int bulletHitMeteor(Entity *b)
{
	Entity *e;
	for (e = stage.bulletHead.next; e != NULL; e = e->next)
	{
		if (e->side != b->side and collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
		{	
			b->alive = 0;
			e->alive = 0;
			addExplosions(b->x, b->y, 32);
			addShard(b);
			return 1;
		}
	}
	return 0;
}
int missileHitFighter(Entity *b)
{
	Entity *e;
	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
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
        			playSound(SND_ALIEN_DIE, CH_ANY);
    			}
			return 1;
		}
	}
	return 0;
}
void doMissile()
{
    Entity *m, *prev;
    prev = &stage.missileHead;
    for (m = stage.missileHead.next ; m != NULL ; m = m->next)
    {	

    	if(player!=NULL)aim(player->x + (player->w / 2), player->y + (player->h / 2), m->x, m->y, &m->dx, &m->dy);
        m->x += m->dx*MISSILE_SPEED;
        m->y += m->dy*MISSILE_SPEED;
        if (missileHitFighter(m) or (m->x < -m->w or m->y < -m->h or m->x > SCREEN_WIDTH or m->y > SCREEN_HEIGHT))
        {
            if (m == stage.missileTail)
            {
                stage.missileTail = prev;
            }
            prev->next = m->next;
            free(m);
            m = prev;
        }
        prev = m;
    }
}
void spawnMeteors()
{
	Entity *meteors;

	if (--meteorsSpawnTimer <= 0)
	{
		meteors =new Entity;
		memset(meteors, 0, sizeof(Entity));
		stage.meteorTail->next = meteors;
		stage.meteorTail = meteors;
		meteors->x = SCREEN_WIDTH;
		meteors->y = ((rand()*rand()) % (SCREEN_HEIGHT-100));
		meteors->texture = meteoriteTexture;
		SDL_QueryTexture(meteors->texture, NULL, NULL, &meteors->w, &meteors->h);
		meteors->side = SIDE_ENEMY;
		meteors->alive=1;
		meteorsSpawnTimer =FPS*2+(rand() % 60);
	}

}
void spawnMissile()
{
	Entity *missile;

	if (--missileSpawnTimer <= 0)
	{
		missile =new Entity;
		memset(missile, 0, sizeof(Entity));
		stage.missileTail->next = missile;
		stage.missileTail = missile;
		missile->x = SCREEN_WIDTH;
		missile->y = ((rand()*rand()) % (SCREEN_HEIGHT-100));
		missile->texture = missileTexture;
		SDL_QueryTexture(missile->texture, NULL, NULL, &missile->w, &missile->h);
		missile->w*=2;
		missile->h*=2;
		missile->side = SIDE_ENEMY;
		missile->alive=1;
		missileSpawnTimer =FPS*3+(rand() % 60);
	}

}


