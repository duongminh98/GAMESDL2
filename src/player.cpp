#include "common.h"
extern Entity      *player;
extern Stage      stage;
extern SDL_Texture *playerTexture;
extern Game game;
void initPlayer()
{
	player =new Entity;
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;
	player->health = 1;
	player->x = 100;
	player->y = 100;
	player->side = SIDE_PLAYER;
	player->texture = playerTexture;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}
void doPlayer()
{
	if(player!=NULL)
	{
		player->dx = player->dy = 0;
		if (player->reload > 0)
		{
			player->reload--;
		}
	
		if (game.keyboard[SDL_SCANCODE_W])
		{
			if(player->y<0) player->dy=0;
			else player->dy = -PLAYER_SPEED;
		}
	
		if (game.keyboard[SDL_SCANCODE_S])
		{
			if(player->y>SCREEN_HEIGHT-player->h) player->dy=0;
			else player->dy = PLAYER_SPEED;
		}
	
		if (game.keyboard[SDL_SCANCODE_A])
		{
			if(player->x<0) player->dx=0;
			else player->dx = -PLAYER_SPEED;
		}
	
		if (game.keyboard[SDL_SCANCODE_D])
		{
			if(player->x>SCREEN_WIDTH-player->w) player->dx=0;
			else player->dx = PLAYER_SPEED;
		}
	
		if (game.keyboard[SDL_SCANCODE_SPACE] and player->reload == 0)
		{	
			playSound(SND_PLAYER_FIRE, CH_PLAYER);
			fireBullet();
		}
	
		player->x += player->dx;
		player->y += player->dy;
	}
}
