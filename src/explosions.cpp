#include "common.h"
extern SDL_Texture *explosionTexture;
extern Stage stage;
extern Game game;
void addExplosions(int x, int y, int num)
{
    Explosion *e;
    for (int i = 0 ; i < num ; i++)
    {
        e = new Explosion;
        memset(e, 0, sizeof(Explosion));
        stage.explosionTail->next = e;
        stage.explosionTail = e;
        e->x = x + (rand() % 32) - (rand() % 32);
        e->y = y + (rand() % 32) - (rand() % 32);
        e->dx = ((rand() % 10) - (rand() % 10))/10;
        e->dy = ((rand() % 10) - (rand() % 10))/10;
        switch (rand() % 4)
        {
            case 0:
                e->r = 255;
                break;
            case 1:
                e->r = 255;
                e->g = 128;
                break;
            case 2:
                e->r = 255;
                e->g = 255;
                break;
            default:
                e->r = 255;
                e->g = 255;
                e->b = 255;
                break;
        }
        e->a = rand() % FPS * 3;
    }
}
void addShard(Entity *e)
{
    Shard *d;
    int w, h;
    w = e->w / 2;
    h = e->h / 2;
    for (int y = 0 ; y <= h ; y += h)
    {
        for (int x = 0 ; x <= w ; x += w)
        {
            d = new Shard;
            memset(d, 0, sizeof(Shard));
            stage.shardTail->next = d;
            stage.shardTail = d;
            d->dx = (rand() % 5) - (rand() % 5);
            d->dy = -(5 + (rand() % 12));
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
    Explosion *e, *prev;
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
    Shard *d, *prev;
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