#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ex_1.h"

Game *initGame() {
  Game *game = (Game*)malloc(sizeof(Game));
  if (game == NULL) exit(FAILED_TO_ALLOCATE_GAME);
  game->players = NULL;
  game->endplay = NULL;
  game->balls = NULL;
  game->numBalls = 0;

  return game;
}

Player *newPlayer(const char *name, int id, Ball ball[], int numballs) {
  Player *player = (Player*)malloc(sizeof(Player));
  if (player == NULL) exit(FAILED_TO_ALLOCATE_PLAYER);

  player->name = strdup(name);
  if (player->name == NULL) exit(FAILED_TO_ALLOCATE_PLAYER_NAME);

  player->ID = id;

  player->myBalls = (Ball*)malloc(numballs * sizeof(Ball));
  if (player->myBalls == NULL) exit(FAILED_TO_ALLOCATE_BALLS);
  for (int i = 0; i < numballs; i++) {
    player->myBalls[i] = ball[i];
  }
  player->numBalls = numballs;

  return player;
}

int addPlayer(Game *game, Player *player) {
  PItem *newPlayer;
  PItem *temp = game->players;
  int firstPlayerID = game->players->myP->ID;


  while (temp->next->myP->ID != firstPlayerID)
    temp = temp->next;
   
  newPlayer = (PItem*)malloc(sizeof(PItem));
  if (newPlayer == NULL) exit(FAILED_TO_ALLOCATE_NEW_PLAYER);

  newPlayer->myP = player;
  newPlayer->next = game->players->myP;
  newPlayer->myP = player->prev = temp;
  temp->next = newPlayer;
  game->players->prev = newPlayer;

  game->balls = (Ball*)realloc(
    game->balls,
    (game->numBalls + player->numBalls) * sizeof(Ball)
  );

  if (game->balls == NULL) exit(FAILED_TO_REALLOCATE_BALLS);
  for (int i = 0; i < player->numBalls; i++) {
    game->balls[game->numBalls + i] = player->myBalls[i];
  }
  game->numBalls += player->numBalls;

  return player->numBalls;
}

int moveBalls(Game* game, Player *player, int x) {
  int currentIdx = player->numBalls;
  Ball *newBalls;
  if (game->numBalls < x) return -1;
  player->myBalls = (Ball*)realloc(
    player->myBalls,
    (player->numBalls + x) * sizeof(Ball)
  );
  if (player->myBalls == NULL) exit(FAILED_TO_REALLOCATE_PLAYER_BALLS);

  for (int i = game->numBalls - x - 1; i < game->numBalls; i++) {
    player->myBalls[currentIdx] = game->balls[i];
    currentIdx++;
  }
  newBalls = (Ball*)malloc((game->numBalls - x) * sizeof(Ball));
  if (newBalls == NULL) exit(FAILED_TO_REALLOCATE_GAME_BALLS);

  for (int i = 0; i < game->numBalls - x; i++) {
    newBalls[i] = game->balls[i];
  }
  game->balls = newBalls;
  game->numBalls = game->numBalls - x;

  return game->numBalls;
}

int removePlayer(Game *game, Player *player) {
  PItem *temp = game->players;
  PItem *playerToRemove = NULL;
  int firstPlayerID game->players->myP->ID;
  if (game->players == NULL) return -1;
  int playerCount = 1;
  while (temp->next->myP->ID != firstPlayerID) {
    temp = temp->next;
    playerCount++;
  }
  while (temp->next->myP->ID != player->ID) {
    if (temp->next->ID == firstPlayerID && firstPlayerID != player->ID) return -1;
    temp = temp->next;
  }

  playerToRemove = temp->next;
  temp->next = playerToRemove->next;
  playerToRemove->next->prev = temp;
  playerToRemove->prev = NULL;
  playerToRemove->next = NULL;

  game->endplay->prev->next = playerToRemove;
  playerToRemove->prev = game->endplay->prev;
  game->endplay->prev = playerToRemove;
  playerToRemove->next = game->endplay;

  return playerCount;
}

int startPlay(Game *game) {
  PItem *temp = game->players;
  int amountOfBalls;

  while (temp != NULL && game->numBalls > 0) {
    scanf("%d", &amountOfBalls);
    if (amountOfBalls > game->numBalls) removePlayer(game, temp->myP);
    else moveBalls(game, temp->myP, amountOfBalls); 
  }

  return game->numBAlls;
}
int compRed(Player *first, Player *second) {
  int redBallBalance = 0;
  for (int i = 0; i < first->numBalls; i++) {
    if (first->balls[i] == red) redBallBalance++;
  }
  for (int i = 0; i < second->numBalls; i++) {
    if (second->balls[i] == red) redBallBalance--;
  }

  return redBallBalance;
}
int compID(Player *first, Player *second) {
  return first->id - second->id;
}
void sortPlayers(PItem *list, comp compare) {
  PItem *temp = list;
  PItem *next = NULL;
  PItem *prev = NULL;
  int firstPlayerID = temp->myP->ID;

  while (temp->next->myP->ID != firstPlayerID) {
    if (compare(temp->myP, temp->next->myP) < 0) {
      next = temp->next;
      prev = temp->prev;
      prev->next = next;
      next->prev = prev;
      temp->next = next->next;
      temp->prev = next;
    }
    temp = list;
  }
}

void endGame(Game *game) {
  PItem *firstPlayer = game->players;
  PItem *firstEndPlayer = game->players;
  int firstPlayerID = firstPlayer->myP->ID;
  int firstEndPlayerID;

  if (firstPlayer != NULL) {
    while (firstPlayer->next->myP != firstPlayerID) {
      removePlayer(game, firstPlayer->myP);
    }    
    removePlayer(game, firstPlayer->myP);
  }

  sortPlayers(firstEndPlayer, compRed);
  firstEndPlayerID = firstEndPlayer->myP->ID;
  while (firstEndPlayer->next->myP != firstEndPlayerID) {
    printf("%s\n", firstEndPlayer->myP->name);
  }
  firstEndPlayer = game->endplay;
  while (firstEndPlayer->myP->ID != firstEndPlayerID) {
    Player *player = firstEndPlayer->myP;
    firstEndPlayer = player->next;
    free(player->name);
    free(player->myBalls);
    free(player);
  }
  Player *player = firstEndPlayer->myP;
  free(player->name);
  free(player->myBalls);
  free(player);
  free(game->endplay);
  free(game->players);
  free(game->balls);
  free(game);
}
