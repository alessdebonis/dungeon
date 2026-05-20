#ifndef MAP_H
#define MAP_H

#include "types.h"

void initRooms(Room rooms[]);
void drawRoom(Room* room, Player* player, Enemy enemies[], int totalEnemies, Item items[], int totalItems);
bool isWall(Room* room, int x, int y);

#endif