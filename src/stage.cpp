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
    Explosion *ex;
	Shard    *d;
    while (stage.fighterHead.next)
    {
        e = stage.fighterHead.next;
        stage.fighterHead.next = e->next;
        free(e);
    }
    while (stage.bulletHead.next)
    {
        e = stage.bulletHead.next;
        stage.bulletHead.next = e->next;
        free(e);
    }
    while (stage.explosionHead.next)
	{
		ex = stage.explosionHead.next;
		stage.explosionHead.next = ex->next;
		free(ex);
	}
	while (stage.pointsHead.next)
    {
        e = stage.pointsHead.next;
        stage.pointsHead.next = e->next;
        free(e);
    }
	while (stage.shardHead.next)
	{
		d = stage.shardHead.next;
		stage.shardHead.next = d->next;
		free(d);
	}
    while (stage.meteorHead.next)
    {
        e = stage.meteorHead.next;
        stage.meteorHead.next = e->next;
        free(e);
    }
    while (stage.missileHead.next)
    {
        e = stage.missileHead.next;
        stage.missileHead.next = e->next;
        free(e);
    }
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
	stage.shardTail = &stage.shardHead;
	stage.pointsTail = &stage.pointsHead;
    stage.meteorTail = &stage.meteorHead;
    stage.missileTail= &stage.missileHead;
}
void initStage()
{
	game.delegate.logic = logic;
	game.delegate.draw = draw;
	memset(&stage, 0, sizeof(Stage));
	memset(game.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
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