#include "common.h"
SDL_Texture *mouseTexture;
SDL_Rect mouse;
SDL_Rect point;
extern Game game;
static SDL_Rect dest;
void initMouse()
{
	mouseTexture=IMG_LoadTexture(game.renderer, "res/pointerLOL.WEBP");
	SDL_QueryTexture(mouseTexture, NULL, NULL, &dest.w, &dest.h);
	SDL_ShowCursor(0);
	mouse.w=dest.w;
	mouse.h=dest.h;
}
void updateMouse()
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
}
void drawMouse()
{	
	blitRect(mouseTexture, &dest, mouse.x, mouse.y);
}