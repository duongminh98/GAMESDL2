#include "common.h"
extern Game game;
using namespace std;
SDL_Texture *bulletTexture;
SDL_Texture *enemyTexture;
SDL_Texture *alienBulletTexture;
SDL_Texture *playerTexture;
SDL_Texture *explosionTexture;
SDL_Texture *pointsTexture;
SDL_Texture *bronzeTexture;
SDL_Texture *silverTexture; 	
SDL_Texture *goldTexture; 	
SDL_Texture *platinumTexture; 
SDL_Texture *diamondTexture; 	
SDL_Texture *masterTexture; 	
SDL_Texture *challengerTexture;
SDL_Texture *playTexture1;
SDL_Texture *highscoreTexture1;
SDL_Texture *exitTexture1;
SDL_Texture *playTexture2;
SDL_Texture *highscoreTexture2;
SDL_Texture *exitTexture2;
SDL_Texture *menuBackground;
SDL_Texture *meteoriteTexture;
SDL_Texture *missileTexture;
SDL_Texture *background;
SDL_Texture *fontTexture;
SDL_Texture *missileFlame;
SDL_Texture *enginePlayer;
SDL_Texture *engineEnemy;
SDL_Texture *flamePlayer;
SDL_Texture *flameEnemy;
SDL_Texture *soundOnTexture;
SDL_Texture *soundOffTexture;
TTF_Font 	*ourFont;
int public_key;
int private_key;
int n;
void initSDL()
{
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;
	SDL_Init(SDL_INIT_VIDEO);
	game.window = SDL_CreateWindow("SPACEWAR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	game.renderer = SDL_CreateRenderer(game.window, -1, rendererFlags);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(MAX_SND_CHANNELS);
    TTF_Init();
    bulletTexture 		= IMG_LoadTexture(game.renderer,"res/bullet.png");
	enemyTexture 		= IMG_LoadTexture(game.renderer,"res/drone_1_red (1).png");
    alienBulletTexture 	= IMG_LoadTexture(game.renderer,"res/bulletenemy.png");
	playerTexture 		= IMG_LoadTexture(game.renderer,"res/drone_1_blue.png");
	explosionTexture 	= IMG_LoadTexture(game.renderer,"res/explosion_01_strip13.png");
	pointsTexture 		= IMG_LoadTexture(game.renderer,"res/points.png");
	bronzeTexture 		= IMG_LoadTexture(game.renderer,"res/bronze.png");
	silverTexture	 	= IMG_LoadTexture(game.renderer,"res/silver.png");
	goldTexture 		= IMG_LoadTexture(game.renderer,"res/gold.png");
	platinumTexture 	= IMG_LoadTexture(game.renderer,"res/platinum.png");
	diamondTexture 		= IMG_LoadTexture(game.renderer,"res/diamond.png");
	masterTexture 		= IMG_LoadTexture(game.renderer,"res/master.png");
	challengerTexture 	= IMG_LoadTexture(game.renderer,"res/challenger.png");
	menuBackground		= IMG_LoadTexture(game.renderer,"res/BeFunky-design.png");
	playTexture1		= IMG_LoadTexture(game.renderer,"res/play (1).png");
	highscoreTexture1	= IMG_LoadTexture(game.renderer,"res/highscore (1).png");
	exitTexture1		= IMG_LoadTexture(game.renderer,"res/exit (1).png");
	playTexture2      	= IMG_LoadTexture(game.renderer,"res/play (2).png");
	highscoreTexture2	= IMG_LoadTexture(game.renderer,"res/highscore (2).png");
	exitTexture2		= IMG_LoadTexture(game.renderer,"res/exit (2).png");
	meteoriteTexture	= IMG_LoadTexture(game.renderer,"res/asteroid.png");
	missileTexture		= IMG_LoadTexture(game.renderer,"res/02.png");
	background 			= IMG_LoadTexture(game.renderer,"res/bg5.jpg");
	fontTexture 		= IMG_LoadTexture(game.renderer,"res/font.png");
	missileFlame 		= IMG_LoadTexture(game.renderer,"res/missileflame.png");
	enginePlayer		= IMG_LoadTexture(game.renderer,"res/01.png");
	engineEnemy			= IMG_LoadTexture(game.renderer,"res/01 (1).png");
	flamePlayer			= IMG_LoadTexture(game.renderer,"res/flameengine.png");
	flameEnemy			= IMG_LoadTexture(game.renderer,"res/08.png");
	soundOnTexture		= IMG_LoadTexture(game.renderer,"res/soundOnBlack.png");
	soundOffTexture		= IMG_LoadTexture(game.renderer,"res/soundOffBlack.png");
	ourFont 			= TTF_OpenFont("res/ariblk.ttf",72);
	int prime1 = 463;
    int prime2 = 71;
    n = prime1 * prime2;
    int fi = (prime1 - 1) * (prime2 - 1);
    int e = 2;
    while (1) 
    {
        if (__gcd(e, fi) == 1)
            break;
        e++;
    }
    public_key = e;
    int d = 2;
    while (1) {
        if ((d * e) % fi == 1)
            break;
        d++;
    }
    private_key = d;
}
void cleanup()
{	
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	SDL_Quit();
	TTF_Quit();
	TTF_CloseFont(ourFont);
}
void initGame()
{	
    initStarfield();
    initSounds();
    initHighscoreTable();
    initButton();
    loadMusic("res/pacman background music.ogg");
   	playMusic(1);
}