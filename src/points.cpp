#include "common.h"
extern Entity *player;
extern Stage stage;
extern SDL_Texture *pointsTexture;
extern int enemySpawnTimerC;
void addPointsPod(int x, int y)
{
    Entity *e;
    e = new Entity;
    memset(e, 0, sizeof(Entity));
    stage.pointsTail->next = e;
    stage.pointsTail = e;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->health = FPS * 10;
    e->texture = pointsTexture;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w/2;
    e->y -= e->h/2;
}
void doPointsPods()
{
    Entity *e, *prev;
    prev = &stage.pointsHead;
    for (e = stage.pointsHead.next ; e != NULL ; e = e->next)
    {
        if (e->x < 0)
        {
            e->x = 0;
            e->dx = -e->dx;
        }
        if (e->x + e->w > SCREEN_WIDTH)
        {
            e->x = SCREEN_WIDTH - e->w;
            e->dx = -e->dx;
        }
        if (e->y < 0)
        {
            e->y = 0;
            e->dy = -e->dy;
        }
        if (e->y + e->h > SCREEN_HEIGHT)
        {
            e->y = SCREEN_HEIGHT - e->h;
            e->dy = -e->dy;
        }
        e->x += e->dx;
        e->y += e->dy;
        if (player != NULL and collision(e->x, e->y, e->w, e->h, player->x, player->y, player->w, player->h))
        {
            e->health = 0;
            stage.score++;
            enemySpawnTimerC-=10;
            playSound(SND_POINTS, CH_POINTS);
        }
        if (--e->health <= 0)
        {
            if (e == stage.pointsTail)
            {
                stage.pointsTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}