#include "player.h"
#include "map.h"

void movePlayer(Player* player, Room* room, char key) {
    int newX = player->x;
    int newY = player->y;

    if (key == 'w') {
        newY = player->y - 1;
    }
    if (key == 's') {
        newY = player->y + 1;
    }
    if (key == 'a') {
        newX = player->x - 1;
    }
    if (key == 'd') {
        newX = player->x + 1;
    }

    if (!isWall(room, newX, newY)) {
        player->x = newX;
        player->y = newY;
    }
}

void checkDoor(Player* player, Room rooms[]) {
    Room* room = &rooms[player->roomId];

    if (room->layout[player->y][player->x] != 'D') {
        return;
    }

    if (player->y == 0 && room->connections[NORTH] != -1) {
        player->roomId = room->connections[NORTH];
        player->y = MAP_HEIGHT - 2;
    }
    if (player->y == MAP_HEIGHT - 1 && room->connections[SOUTH] != -1) {
        player->roomId = room->connections[SOUTH];
        player->y = 1;
    }
    if (player->x == MAP_WIDTH - 1 && room->connections[EAST] != -1) {
        player->roomId = room->connections[EAST];
        player->x = 1;
    }
    if (player->x == 0 && room->connections[WEST] != -1) {
        player->roomId = room->connections[WEST];
        player->x = MAP_WIDTH - 2;
    }
}

void handleItem(Player* player, Item items[], int totalItems) {
    if (player->hasItem) {
        for (int i = 0; i < totalItems; i++) {
            if (!items[i].active && items[i].symbol == player->item) {
                items[i].x = player->x;
                items[i].y = player->y;
                items[i].roomId = player->roomId;
                items[i].active = true;
                break;
            }
        }
        player->hasItem = false;
        player->item = ' ';
        return;
    }

    for (int i = 0; i < totalItems; i++) {
        if (!items[i].active) {
            continue;
        }
        if (items[i].roomId != player->roomId) {
            continue;
        }
        if (items[i].x == player->x && items[i].y == player->y) {
            player->hasItem = true;
            player->item = items[i].symbol;
            items[i].active = false;
            return;
        }
    }
}