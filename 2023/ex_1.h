#define FAILED_TO_ALLOCATE_GAME 10
#define FAILED_TO_ALLOCATE_PLAYER 11
#define FAILED_TO_ALLOCATE_PLAYER_NAME 12
#define FAILED_TO_ALLOCATE_NEW_PLAYER 13
#define FAILED_TO_ALLOCATE_BALLS 14
#define FAILED_TO_REALLOCATE_BALLS 15
#define FAILED_TO_REALLOCATE_PLAYER_BALLS 16
#define FAILED_TO_REALLOCATE_GAME_BALLS 17

typedef enum {red, orange, yellow, green, blue} Ball;
typedef int(*comp)(Player*, Player*);

typedef struct Player{
  char *name;
  int ID;
  Ball *myBalls;
  int numBalls;
} Player;
typedef struct PItem{
  Player *myP;
  PItem *next;
  PItem *prev;
} PItem;
typedef struct Game{
  Pltem *players;
  PItem *endplay;
  Ball *balls;
  int numBalls;
} Game;

Game *initGame();
Player * newPlayer(const char *name, int id, Ball ball[], int numballs);
int addPlayer(Game *game, Player *player);
int moveBalls(Game* game, Player *player, int x);
int removePlayer(Game *game, Player *player);
int compRed(Player *first, Player *second);
int compID(Player *first, Player *second);
void sortPlayers(PItem *list, comp compare);
void endGame(Game *game);
