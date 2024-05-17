#include "common.h"
extern Game game;
extern Highscores highscores;
extern Stage stage;
Entity *player;
int enemySpawnTimer;
int meteorsSpawnTimer;
int missileSpawnTimer;
int enemySpawnTimerC=120;
static int stageResetTimer;
using namespace std;
static void logic();
static void draw();
static void resetStage();
void resetStage()
{
    Entity *e;
    while (stage.fighterHead.next)
    {
        e = stage.fighterHead.next;
        stage.fighterHead.next = e->next;
        free(e);
    }
    stage.fighterTail = &stage.fighterHead;
    while (stage.bulletHead.next)
    {
        e = stage.bulletHead.next;
        stage.bulletHead.next = e->next;
        free(e);
    }
    stage.bulletTail = &stage.bulletHead;
    while (stage.explosionHead.next)
	{
		e = stage.explosionHead.next;
		stage.explosionHead.next = e->next;
		free(e);
	}
    stage.explosionTail = &stage.explosionHead;
	while (stage.pointsHead.next)
    {
        e = stage.pointsHead.next;
        stage.pointsHead.next = e->next;
        free(e);
    }
    stage.pointsTail = &stage.pointsHead;
	while (stage.shardHead.next)
	{
		e = stage.shardHead.next;
		stage.shardHead.next = e->next;
		free(e);
	}
    stage.shardTail = &stage.shardHead;
    while (stage.meteorHead.next)
    {
        e = stage.meteorHead.next;
        stage.meteorHead.next = e->next;
        free(e);
    }
    stage.meteorTail = &stage.meteorHead;
    while (stage.missileHead.next)
    {
        e = stage.missileHead.next;
        stage.missileHead.next = e->next;
        free(e);
    }
    stage.missileTail= &stage.missileHead;
}
void initStage()
{
	game.delegate.logic = logic;
	game.delegate.draw = draw;
	memset(&stage, 0, sizeof(Stage));
	memset(game.keyboard, 0, sizeof(int) * KEYBOARD);
	resetStage();
	stage.score = 0;
	initPlayer();
	enemySpawnTimer = 0;
    meteorsSpawnTimer = 0;
    missileSpawnTimer = 0;
	stageResetTimer = FPS * 3;
    enemySpawnTimerC = 120;
}
static void logic()
{	
	game.MainLogic();
    if(stage.score>=10)
    {   
        spawnMissile();
    }
    if(stage.score>=5)
    {   
        spawnMeteors();
    }
    if (player == NULL and --stageResetTimer <= 0)
    {
        addHighscore(stage.score);
        initHighscores();
    }
    
}
static void draw()
{	
	game.MainDraw();
}