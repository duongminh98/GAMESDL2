#include "common.h"
extern Stage stage;
extern Entity *player;
extern int enemySpawnTimer;
extern SDL_Texture *enemyTexture;
extern int enemySpawnTimerC;
void doFighters()
{
    Entity *e, *prev;
    prev = &stage.fighterHead;
    for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;
        if (e != player and e->x < -e->w)
        {
            e->alive = 0;
        }
        if (e->alive == 0)
        {
            if (e == player)
            {
                player = NULL;
            }
            if (e == stage.fighterTail)
            {
                stage.fighterTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}
void spawnEnemies()
{
	Entity *enemy;
	if (--enemySpawnTimer <= 0)
	{
		enemy =new Entity;
		memset(enemy, 0, sizeof(Entity));
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;
		enemy->x = SCREEN_WIDTH;
		enemy->y = ((rand()*rand()) % (SCREEN_HEIGHT-100));
		enemy->texture = enemyTexture;
        enemy->alive=1;
        enemy->dx = -(2 + (rand() % 4));
        enemy->dy = (-10 + (rand() % 20))/5;
        enemy->side = SIDE_ENEMY;
        enemy->reload = 60;
        enemySpawnTimer = FPS/2+(rand() % enemySpawnTimerC);
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
		
	}

}
void doEnemies()
{
    Entity *e;
    for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
    {
        if (e != player and player != NULL and --e->reload < 0)
        {	
        	playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
            fireAlienBullet(e);
        }
    }
}