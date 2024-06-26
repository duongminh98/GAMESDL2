typedef struct {
    void (*logic)();
    void (*draw)();
} Delegate;
typedef struct {
    int x;
    int y;
    int speed;
} Star;
typedef struct {
    int recent;
    int score;
    char name[MAX_SCORE_NAME_LENGTH];
} Highscore;
typedef struct {
    Highscore highscore[NUM_HIGHSCORES];
} Highscores;
struct Entity {
    float x;float y;int w;int h;//toạ độ
    int side;//phe
    float dx;float dy;//tốc độ
    int alive;
    int life;
    int r, g, b, a;
    int reload;//thời gian sau mỗi lần bắn
    SDL_Texture *texture;
    SDL_Rect rect;
    Entity *next;
};
typedef struct {
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
    Entity explosionHead, *explosionTail;
    Entity shardHead, *shardTail;
    Entity pointsHead, *pointsTail;
    Entity meteorHead, *meteorTail;
    Entity missileHead, *missileTail;
    int score;
} Stage;