#include "common.h"
extern Game game;
extern Stage stage;
extern Highscores highscores;
extern SDL_Texture *fontTexture;
extern SDL_Texture *bronzeTexture;
extern SDL_Texture *silverTexture;     
extern SDL_Texture *goldTexture;   
extern SDL_Texture *platinumTexture; 
extern SDL_Texture *diamondTexture;    
extern SDL_Texture *masterTexture;     
extern SDL_Texture *challengerTexture;
char drawTextBuffer[MAX_LINE_LENGTH];
extern TTF_Font 	*ourFont;
extern Highscore *newHighscore;
using namespace std;
extern int cursorBlink;
void drawText(int x, int y, int r, int g, int b, int align, const char *format, ...)
{
	va_list  args;
	memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));
	va_start(args, format);
	vsprintf(drawTextBuffer, format, args);
	va_end(args);
	int len = strlen(drawTextBuffer);
	switch (align)
	{
		case TEXT_RIGHT:
			x -= (len * GLYPH_WIDTH);
			break;

		case TEXT_CENTER:
			x -= (len * GLYPH_WIDTH) / 2;
			break;
	}
	SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont,drawTextBuffer,{r,g,b});
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(game.renderer,surfaceText);
    SDL_FreeSurface(surfaceText); 
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = len * GLYPH_WIDTH;
    rectangle.h = GLYPH_HEIGHT;
    SDL_RenderCopy(game.renderer,textureText,NULL,&rectangle);
    SDL_DestroyTexture(textureText);
	
}
void drawNameInput(int score)
{
    SDL_Rect r;
    if(score<=10)
    {
    	drawText(SCREEN_WIDTH / 2,70,255,0,0,TEXT_CENTER,"CONGRATULATIONS, YOU'VE REACHED BRONZE!");
    	drawText(SCREEN_WIDTH / 2,120,255,0,0,TEXT_CENTER,"ENTER YOUR NAME BELOW:");
    	drawText(SCREEN_WIDTH / 2,250,128,255,128,TEXT_CENTER,newHighscore->name);
    	blit(bronzeTexture,SCREEN_WIDTH / 2+200,250);
    }   
    else if(score<=20)
    {
    	drawText(SCREEN_WIDTH / 2,70,255,0,0,TEXT_CENTER,"CONGRATULATIONS, YOU'VE REACHED SILVER!");
    	drawText(SCREEN_WIDTH / 2,120,255,0,0,TEXT_CENTER,"ENTER YOUR NAME BELOW:");
    	drawText(SCREEN_WIDTH / 2,250,128,255,128,TEXT_CENTER,newHighscore->name);
    	blit(silverTexture,SCREEN_WIDTH / 2+200,250);
    }
    else if(score<=30)
    {
    	drawText(SCREEN_WIDTH / 2,70,255,0,0,TEXT_CENTER,"CONGRATULATIONS, YOU'VE REACHED GOLD!");
    	drawText(SCREEN_WIDTH / 2,120,255,0,0,TEXT_CENTER,"ENTER YOUR NAME BELOW:");
    	drawText(SCREEN_WIDTH / 2,250,128,255,128,TEXT_CENTER,newHighscore->name);
    	blit(goldTexture,SCREEN_WIDTH / 2+200,250);
    }
    else if(score<=40)
    {
   		drawText(SCREEN_WIDTH / 2,70,255,0,0,TEXT_CENTER,"CONGRATULATIONS, YOU'VE REACHED PLATINUM!");
   		drawText(SCREEN_WIDTH / 2,120,255,0,0,TEXT_CENTER,"ENTER YOUR NAME BELOW:");
   		drawText(SCREEN_WIDTH / 2,250,128,255,128,TEXT_CENTER,newHighscore->name);
   		blit(platinumTexture,SCREEN_WIDTH / 2+200,250);
    }
    else if(score<=50)
    {
    	drawText(SCREEN_WIDTH / 2,70,255,0,0,TEXT_CENTER,"CONGRATULATIONS, YOU'VE REACHED DIAMOND!");
    	drawText(SCREEN_WIDTH / 2,120,255,0,0,TEXT_CENTER,"ENTER YOUR NAME BELOW:");
    	drawText(SCREEN_WIDTH / 2,250,128,255,128,TEXT_CENTER,newHighscore->name);
    	blit(diamondTexture,SCREEN_WIDTH / 2+200,250);
    }
    else if(score<=60)
    {
    	drawText(SCREEN_WIDTH / 2,70,255,0,0,TEXT_CENTER,"CONGRATULATIONS, YOU'VE REACHED MASTER!");
    	drawText(SCREEN_WIDTH / 2,120,255,0,0,TEXT_CENTER,"ENTER YOUR NAME BELOW:");
    	drawText(SCREEN_WIDTH / 2,250,128,255,128,TEXT_CENTER,newHighscore->name);
    	blit(masterTexture,SCREEN_WIDTH / 2+200,250);
    }
    else 
    {
    	drawText(SCREEN_WIDTH / 2,70,255,0,0,TEXT_CENTER,"CONGRATULATIONS, YOU'VE REACHED CHALLENGER!");
    	drawText(SCREEN_WIDTH / 2,120,255,0,0,TEXT_CENTER,"ENTER YOUR NAME BELOW:");
    	drawText(SCREEN_WIDTH / 2,250,128,255,128,TEXT_CENTER,newHighscore->name);
    	blit(challengerTexture,SCREEN_WIDTH / 2+200,250);
    }
    if (cursorBlink < FPS / 2)
    {
        r.x = ((SCREEN_WIDTH / 2) + (strlen(newHighscore->name) * GLYPH_WIDTH)/2);
        r.y = 250;
        r.w = GLYPH_WIDTH;
        r.h = GLYPH_HEIGHT;
        SDL_SetRenderDrawColor(game.renderer,0,255,0,255);
        SDL_RenderFillRect(game.renderer, &r);
    }
    drawText(SCREEN_WIDTH / 2,625,255,0,0, TEXT_CENTER, "PRESS RETURN WHEN FINISHED");
}
void drawHighscores()
{
	int y,r,g,b;
	y = 150;
	drawText(SCREEN_WIDTH / 2-5*GLYPH_WIDTH, 70, 255, 0, 0,TEXT_LEFT, "HIGHSCORES");
	for (int i = 0; i < NUM_HIGHSCORES; i++)
	{
		r = 255;
        g = 0;
        b = 0;
        if (highscores.highscore[i].recent)
        {   
            r = 100;
            g = 250;
            b = 100;
        }
        drawText(SCREEN_WIDTH / 2,y,r,g,b,TEXT_CENTER,"#%d. %-15s ...... %03d",i + 1,highscores.highscore[i].name,highscores.highscore[i].score);
        y += 50;
	}
    drawText(SCREEN_WIDTH / 2,y,0,255,0,TEXT_CENTER,"PRESS SPACE TO RETURN TO THE MENU");
	
}
void drawHud()
{	
	if(stage.score>=10)
    {   
        int r=rand()%255;
        int g=rand()%255;
        int b=rand()%255;
        drawText(10, 46, r, g, b, TEXT_LEFT,"BECAREFUL OF MISSILE!!!!");
    }
    if(stage.score>=5)
    {   
        int r=rand()%255;
        int g=rand()%255;
        int b=rand()%255;
        drawText(10, 10, r, g, b, TEXT_LEFT,"BECAREFUL OF METEORS!!!!");
    }
	drawText(SCREEN_WIDTH - 10, 10, 255, 255, 255, TEXT_RIGHT,"SCORE: %03d", stage.score);
	if (stage.score < highscores.highscore[0].score)
	{
		drawText(SCREEN_WIDTH - 10, 46, 255, 255, 255,TEXT_RIGHT, "HIGHSCORE: %03d", highscores.highscore[0].score);
	}
	else
	{
		drawText(SCREEN_WIDTH - 10, 46, 0, 255, 0,TEXT_RIGHT, "HIGHSCORE: %03d", stage.score);
	}
}