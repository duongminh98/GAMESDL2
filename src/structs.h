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
    int health;
    int reload;//thời gian sau mỗi lần bắn
    SDL_Texture *texture;
    Entity *next;
};
struct Explosion {
    float x;float y;//toạ độ
    float dx;float dy;//tốc độ
    int r, g, b, a;//màu
    Explosion *next;
};
struct Shard {
    float x;float y;//toạ độ
    float dx;float dy;//tốc độ
    SDL_Rect rect;
    SDL_Texture *texture;
    int life;//tồn tại
    Shard *next;
};
typedef struct {
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
    Explosion explosionHead, *explosionTail;
    Shard shardHead, *shardTail;
    Entity pointsHead, *pointsTail;
    Entity meteorHead, *meteorTail;
    Entity missileHead, *missileTail;
    int score;
} Stage;