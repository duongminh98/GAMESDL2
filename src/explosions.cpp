#include "common.h"
extern SDL_Texture *explosionTexture;
extern Stage stage;
extern Game game;
void addExplosions(int x, int y, int num)
{
    Entity *e;
    for (int i = 0 ; i < num ; i++)
    {
        e = new Entity;
        memset(e, 0, sizeof(Entity));
        stage.explosionTail->next = e;
        stage.explosionTail = e;
        e->x = x + (rand() % 36) - (rand() % 36);e->dx = ((rand() % 10) - (rand() % 10))/10;
        e->y = y + (rand() % 36) - (rand() % 36);e->dy = ((rand() % 10) - (rand() % 10))/10;
        e->r=rand()%255;
        e->g=rand()%255;
        e->b=rand()%255;
        e->a = rand() % FPS * 3;
    }
}
void addShard(Entity *e)
{
    Entity *d;
    int w, h;
    w = e->w / 2;
    h = e->h / 2;
    for (int y = 0 ; y <= h ; y += h)
    {
        for (int x = 0 ; x <= w ; x += w)
        {
            d = new Entity;
            memset(d, 0, sizeof(Entity));
            stage.shardTail->next = d;
            stage.shardTail = d;
            d->dx = (rand() % 5) - (rand() % 5);
            d->dy = -5;
            d->x = e->x + e->w /2;
            d->y = e->y + e->h /2;
            d->life = FPS * 2;
            d->texture = e->texture;
            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = w;
            d->rect.h = h;
        }
    }
}
void doExplosions()
{
    Entity *e, *prev;
    prev = &stage.explosionHead;
    for (e = stage.explosionHead.next ; e != NULL ; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;
        if (--e->a <= 0)
        {
            if (e == stage.explosionTail)
            {
                stage.explosionTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}
void doShard()
{
    Entity *d, *prev;
    prev = &stage.shardHead;
    for (d = stage.shardHead.next ; d != NULL ; d = d->next)
    {
        d->x += d->dx;
        d->y += d->dy;
        d->dy += 0.5;
        if (--d->life <= 0)
        {
            if (d == stage.shardTail)
            {
                stage.shardTail = prev;
            }
            prev->next = d->next;
            free(d);
            d = prev;
        }
        prev = d;
    }
}