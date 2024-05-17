#include "common.h"
using namespace std;
extern Game game;
extern Highscores highscores;
extern SDL_Texture *rankTexture;
static void logic();
static void draw();
void doNameInput();
Highscore *newHighscore;
int cursorBlink;
bool cmp(Highscore& a,Highscore& b)
{
	return a.score>b.score;
}
void initHighscoreTable()
{
    ifstream in;
    in.open("High_Score/High_Score.txt");
	memset(&highscores, 0, sizeof(Highscores));
	for (int i = 0; i < NUM_HIGHSCORES; i++)
	{
        in>>highscores.highscore[i].name>>highscores.highscore[i].score;
	}
    in.close();
	newHighscore = NULL;
	cursorBlink = 0;
}

void initHighscores()
{
	game.delegate.logic = logic;
	game.delegate.draw = draw;
	memset(game.keyboard, 0, sizeof(int) * KEYBOARD);
}
void doNameInput()
{
    int n = strlen(newHighscore->name);
    for (size_t i = 0 ; i < strlen(game.inputText) ; i++)
    {
        char c = toupper(game.inputText[i]);
        if (n < MAX_SCORE_NAME_LENGTH - 1 and c >= ' ' and c <= 'Z')
        {
            newHighscore->name[n++] = c;
        }
    }
    if (n > 0 and game.keyboard[SDL_SCANCODE_BACKSPACE])
    {
        newHighscore->name[--n] = '\0';
        game.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
    }
    if (game.keyboard[SDL_SCANCODE_RETURN])
    {
        if (strlen(newHighscore->name) == 0)
        {
            STRNCPY(newHighscore->name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);
        }
        newHighscore = NULL;
    }
    
    ofstream out;
    out.open("High_Score/High_Score.txt");
    for (int i = 0 ; i < NUM_HIGHSCORES ; i++)
    {
        if(highscores.highscore[i].score!=0)
        out<<highscores.highscore[i].name<<" "<<highscores.highscore[i].score<<"\n";
    }
    out.close();
}
static void logic()
{
	doStarfield();
	if (newHighscore != NULL)
    {
        doNameInput();
    }
    else 
    {
    	if(game.keyboard[SDL_SCANCODE_SPACE])
		{
		  initButton();
		}
	}
	if (++cursorBlink >= FPS)
    {
        cursorBlink = 0;
    }
}
static void draw()
{
	drawBackground();
	drawStarfield();
	if (newHighscore != NULL)
    {
        drawNameInput(newHighscore->score);
    }
    else drawHighscores();
}
void addHighscore(int score)
{
	Highscore newHighscores[NUM_HIGHSCORES + 1];
	for (int i = 0; i < NUM_HIGHSCORES; i++)
	{
		newHighscores[i] = highscores.highscore[i];
		newHighscores[i].recent = 0;
	}
	newHighscores[NUM_HIGHSCORES].score = score;
	newHighscores[NUM_HIGHSCORES].recent = 1;
	sort(newHighscores, newHighscores+NUM_HIGHSCORES+1,cmp);
	newHighscore = NULL;
    for (int i = 0 ; i < NUM_HIGHSCORES ; i++)
    {
        highscores.highscore[i] = newHighscores[i];

        if (highscores.highscore[i].recent)
        {
            newHighscore = &highscores.highscore[i];
        }
    }
}
