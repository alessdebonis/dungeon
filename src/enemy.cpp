#include "enemy.h"
#include "map.h"

void initEnemies(Enemy enemies[], int totalEnemies) {
    enemies[0].x = 13;
    enemies[0].y = 13;
    enemies[0].roomId = 2;
    enemies[0].type = 0;
    enemies[0].symbol = 'E';
    enemies[0].active = true;

    enemies[1].x = 13;
    enemies[1].y = 2;
    enemies[1].roomId = 1;
    enemies[1].type = 0;
    enemies[1].symbol = 'E';
    enemies[1].active = true;

    enemies[2].x = 13;
    enemies[2].y = 13;
    enemies[2].roomId = 4;
    enemies[2].type = 1;
    enemies[2].symbol = 'F';
    enemies[2].active = true;

    enemies[3].x = 2;
    enemies[3].y = 2;
    enemies[3].roomId = 0;
    enemies[3].type = 2;
    enemies[3].symbol = 'R';
    enemies[3].active = true;

    enemies[4].x = 13;
    enemies[4].y = 13;
    enemies[4].roomId = 3;
    enemies[4].type = 3;
    enemies[4].symbol = 'X';
    enemies[4].active = true;

    for (int i = 5; i < totalEnemies; i++) {
        enemies[i].active = false;
    }
}

void moveEnemies(Enemy enemies[], int totalEnemies, Player* player, Room* room, int turnCount) {
    for (int i = 0; i < totalEnemies; i++) {
        if (!enemies[i].active) {
            continue;
        }
        if (enemies[i].roomId != player->roomId) {
            continue;
        }

        if (enemies[i].type == 0 && turnCount % 3 != 0) {
            continue;
        }

        if (enemies[i].type == 1 && turnCount % 2 != 0) {
            continue;
        }

        if (enemies[i].type == 3) {
            int newX = enemies[i].x;
            int newY = enemies[i].y;

            if (enemies[i].x < player->x) {
                newX = enemies[i].x + 1;
            } else if (enemies[i].x > player->x) {
                newX = enemies[i].x - 1;
            }

            if (enemies[i].y < player->y) {
                newY = enemies[i].y + 1;
            } else if (enemies[i].y > player->y) {
                newY = enemies[i].y - 1;
            }

            if (!isWall(room, newX, enemies[i].y)) {
                enemies[i].x = newX;
            }
            if (!isWall(room, enemies[i].x, newY)) {
                enemies[i].y = newY;
            }
            continue;
        }

        int diffX = player->x - enemies[i].x;
        int diffY = player->y - enemies[i].y;

        if (diffX < 0) diffX = -diffX;
        if (diffY < 0) diffY = -diffY;

        if (diffX >= diffY) {
            int newX = enemies[i].x;
            if (enemies[i].x < player->x) {
                newX = enemies[i].x + 1;
            } else if (enemies[i].x > player->x) {
                newX = enemies[i].x - 1;
            }
            if (!isWall(room, newX, enemies[i].y)) {
                enemies[i].x = newX;
            }
        } else {
            int newY = enemies[i].y;
            if (enemies[i].y < player->y) {
                newY = enemies[i].y + 1;
            } else if (enemies[i].y > player->y) {
                newY = enemies[i].y - 1;
            }
            if (!isWall(room, enemies[i].x, newY)) {
                enemies[i].y = newY;
            }
        }
    }
}

bool checkEnemyCollision(Enemy enemies[], int totalEnemies, Player* player) {
    for (int i = 0; i < totalEnemies; i++) {
        if (!enemies[i].active) {
            continue;
        }
        if (enemies[i].roomId != player->roomId) {
            continue;
        }
        if (enemies[i].x == player->x && enemies[i].y == player->y) {
            player->health = player->health - 1;
            return true;
        }
    }
    return false;
}