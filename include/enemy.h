#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

void initEnemies(Enemy enemies[], int totalEnemies);
void moveEnemies(Enemy enemies[], int totalEnemies, Player* player, Room* room, int turnCount);
bool checkEnemyCollision(Enemy enemies[], int totalEnemies, Player* player);

#endif