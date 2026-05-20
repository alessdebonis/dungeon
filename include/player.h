#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

void movePlayer(Player* player, Room* room, char key);
void checkDoor(Player* player, Room rooms[]);
void handleItem(Player* player, Item items[], int totalItems);

#endif