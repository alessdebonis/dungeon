#ifndef GAME_H
#define GAME_H

#include "types.h"

void initGame(Room rooms[], Player* player, Enemy enemies[], int totalEnemies, Item items[], int totalItems);
void gameLoop(Room rooms[], Player* player, Enemy enemies[], int totalEnemies, Item items[], int totalItems);
bool checkVictory(Item items[]);
void showIntro();

#endif