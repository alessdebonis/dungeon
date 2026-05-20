#include "map.h"
#include "raylib.h"

void initRooms(Room rooms[]) {
    for (int r = 0; r < MAX_ROOMS; r++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1) {
                    rooms[r].layout[y][x] = '#';
                } else {
                    rooms[r].layout[y][x] = '.';
                }
            }
        }
        rooms[r].connections[NORTH] = -1;
        rooms[r].connections[SOUTH] = -1;
        rooms[r].connections[EAST] = -1;
        rooms[r].connections[WEST] = -1;
    }

    rooms[0].connections[NORTH] = 1;
    rooms[0].connections[SOUTH] = 4;
    rooms[0].connections[EAST] = 2;
    rooms[0].connections[WEST] = 3;
    rooms[1].connections[SOUTH] = 0;
    rooms[2].connections[WEST] = 0;
    rooms[3].connections[EAST] = 0;
    rooms[4].connections[NORTH] = 0;
    rooms[4].connections[SOUTH] = 5;
    rooms[5].connections[NORTH] = 4;

    for (int r = 0; r < MAX_ROOMS; r++) {
        if (rooms[r].connections[NORTH] != -1) {
            rooms[r].layout[0][MAP_WIDTH / 2] = 'D';
        }
        if (rooms[r].connections[SOUTH] != -1) {
            rooms[r].layout[MAP_HEIGHT - 1][MAP_WIDTH / 2] = 'D';
        }
        if (rooms[r].connections[EAST] != -1) {
            rooms[r].layout[MAP_HEIGHT / 2][MAP_WIDTH - 1] = 'D';
        }
        if (rooms[r].connections[WEST] != -1) {
            rooms[r].layout[MAP_HEIGHT / 2][0] = 'D';
        }
    }

    for (int y = 3; y <= 5; y++) {
        rooms[0].layout[y][4] = '#';
        rooms[0].layout[y][11] = '#';
    }
    for (int y = 10; y <= 12; y++) {
        rooms[0].layout[y][4] = '#';
        rooms[0].layout[y][11] = '#';
    }

    for (int x = 1; x <= 6; x++) {
        rooms[1].layout[5][x] = '#';
    }
    for (int x = 9; x <= 14; x++) {
        rooms[1].layout[5][x] = '#';
    }
    for (int x = 1; x <= 5; x++) {
        rooms[1].layout[10][x] = '#';
    }

    for (int y = 1; y <= 6; y++) {
        rooms[2].layout[y][6] = '#';
    }
    for (int y = 9; y <= 14; y++) {
        rooms[2].layout[y][6] = '#';
    }
    for (int y = 4; y <= 11; y++) {
        rooms[2].layout[y][11] = '#';
    }

    for (int y = 1; y <= 6; y++) {
        rooms[3].layout[y][4] = '#';
    }
    for (int y = 5; y <= 14; y++) {
        rooms[3].layout[y][8] = '#';
    }
    for (int y = 1; y <= 10; y++) {
        rooms[3].layout[y][12] = '#';
    }

    for (int x = 4; x <= 7; x++) {
        rooms[4].layout[4][x] = '#';
        rooms[4].layout[5][x] = '#';
    }
    for (int x = 9; x <= 12; x++) {
        rooms[4].layout[10][x] = '#';
        rooms[4].layout[11][x] = '#';
    }

    rooms[5].layout[4][4] = '#';
    rooms[5].layout[4][11] = '#';
    rooms[5].layout[11][4] = '#';
    rooms[5].layout[11][11] = '#';
}

void drawRoom(Room* room, Player* player, Enemy enemies[], int totalEnemies, Item items[], int totalItems) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int px = x * TILE_SIZE;
            int py = y * TILE_SIZE;

            if (room->layout[y][x] == '#') {
                DrawRectangle(px, py, TILE_SIZE, TILE_SIZE, (Color){58, 49, 80, 255});
                DrawRectangle(px + 2, py + 2, TILE_SIZE - 4, TILE_SIZE - 4, (Color){68, 57, 96, 255});
                DrawRectangle(px, py, TILE_SIZE, 2, (Color){90, 74, 124, 255});
                DrawRectangle(px, py, 2, TILE_SIZE, (Color){90, 74, 124, 255});
            } else if (room->layout[y][x] == 'D') {
                DrawRectangle(px, py, TILE_SIZE, TILE_SIZE, (Color){26, 20, 40, 255});
                DrawRectangle(px + 4, py + 4, TILE_SIZE - 8, TILE_SIZE - 8, (Color){61, 42, 22, 255});
                DrawRectangle(px + 6, py + 6, TILE_SIZE - 12, TILE_SIZE - 12, (Color){80, 55, 30, 255});
                DrawRectangle(px + TILE_SIZE/2 - 2, py + TILE_SIZE/2, 4, 8, (Color){196, 155, 32, 255});
            } else {
                DrawRectangle(px, py, TILE_SIZE, TILE_SIZE, (Color){26, 20, 40, 255});
                DrawRectangle(px, py, TILE_SIZE, 1, (Color){22, 16, 36, 255});
                DrawRectangle(px, py, 1, TILE_SIZE, (Color){22, 16, 36, 255});
            }
        }
    }

    for (int i = 0; i < totalItems; i++) {
        if (items[i].active && items[i].roomId == player->roomId) {
            int px = items[i].x * TILE_SIZE + 4;
            int py = items[i].y * TILE_SIZE + 4;

            if (items[i].symbol == 'K') {
                DrawRectangle(px, py, TILE_SIZE - 8, TILE_SIZE - 8, (Color){255, 215, 0, 255});
                DrawRectangle(px + 3, py + 3, TILE_SIZE - 14, TILE_SIZE - 14, (Color){255, 192, 0, 255});
            }
            if (items[i].symbol == 'G') {
                DrawRectangle(px, py, TILE_SIZE - 8, TILE_SIZE - 8, (Color){0, 180, 220, 255});
                DrawRectangle(px + 3, py + 3, TILE_SIZE - 14, TILE_SIZE - 14, (Color){0, 210, 255, 255});
            }
            if (items[i].symbol == 'C') {
                DrawRectangle(px, py, TILE_SIZE - 8, TILE_SIZE - 8, (Color){180, 0, 180, 255});
                DrawRectangle(px + 3, py + 3, TILE_SIZE - 14, TILE_SIZE - 14, (Color){220, 50, 220, 255});
            }
        }
    }

    for (int i = 0; i < totalEnemies; i++) {
        if (enemies[i].active && enemies[i].roomId == player->roomId) {
            int px = enemies[i].x * TILE_SIZE + 2;
            int py = enemies[i].y * TILE_SIZE + 2;

            if (enemies[i].type == 0) {
                DrawRectangle(px, py, TILE_SIZE - 4, TILE_SIZE - 4, (Color){204, 34, 34, 255});
                DrawRectangle(px + 3, py + 3, TILE_SIZE - 10, TILE_SIZE - 10, (Color){221, 51, 51, 255});
                DrawRectangle(px + 6, py + 6, 5, 5, (Color){255, 170, 170, 255});
                DrawRectangle(px + 17, py + 6, 5, 5, (Color){255, 170, 170, 255});
                DrawRectangle(px + 8, py + 18, 10, 3, (Color){136, 17, 17, 255});
            } else if (enemies[i].type == 1) {
                DrawRectangle(px, py, TILE_SIZE - 4, TILE_SIZE - 4, (Color){204, 119, 0, 255});
                DrawRectangle(px + 3, py + 3, TILE_SIZE - 10, TILE_SIZE - 10, (Color){238, 153, 34, 255});
                DrawRectangle(px + 6, py + 6, 5, 5, (Color){255, 221, 170, 255});
                DrawRectangle(px + 17, py + 6, 5, 5, (Color){255, 221, 170, 255});
                DrawRectangle(px + 8, py + 18, 10, 3, (Color){136, 68, 0, 255});
            } else if (enemies[i].type == 2) {
                DrawRectangle(px, py, TILE_SIZE - 4, TILE_SIZE - 4, (Color){150, 0, 150, 255});
                DrawRectangle(px + 3, py + 3, TILE_SIZE - 10, TILE_SIZE - 10, (Color){180, 30, 180, 255});
                DrawRectangle(px + 6, py + 6, 5, 5, (Color){255, 170, 255, 255});
                DrawRectangle(px + 17, py + 6, 5, 5, (Color){255, 170, 255, 255});
                DrawRectangle(px + 8, py + 18, 10, 3, (Color){100, 0, 100, 255});
            } else if (enemies[i].type == 3) {
                DrawRectangle(px, py, TILE_SIZE - 4, TILE_SIZE - 4, (Color){200, 200, 200, 255});
                DrawRectangle(px + 3, py + 3, TILE_SIZE - 10, TILE_SIZE - 10, (Color){240, 240, 240, 255});
                DrawRectangle(px + 6, py + 6, 5, 5, (Color){255, 0, 0, 255});
                DrawRectangle(px + 17, py + 6, 5, 5, (Color){255, 0, 0, 255});
                DrawRectangle(px + 8, py + 18, 10, 3, (Color){100, 100, 100, 255});
            }
        }
    }

    int playerPx = player->x * TILE_SIZE + 2;
    int playerPy = player->y * TILE_SIZE + 2;
    DrawRectangle(playerPx, playerPy, TILE_SIZE - 4, TILE_SIZE - 4, (Color){34, 170, 34, 255});
    DrawRectangle(playerPx + 3, playerPy + 3, TILE_SIZE - 10, TILE_SIZE - 10, (Color){51, 204, 51, 255});
    DrawRectangle(playerPx + 7, playerPy + 7, 5, 5, (Color){17, 85, 17, 255});
    DrawRectangle(playerPx + 17, playerPy + 7, 5, 5, (Color){17, 85, 17, 255});
    DrawRectangle(playerPx + 9, playerPy + 18, 8, 3, (Color){17, 85, 17, 255});

    int menu = MAP_HEIGHT * TILE_SIZE;
    DrawRectangle(0, menu, MAP_WIDTH * TILE_SIZE, MENU_HEIGHT, (Color){15, 14, 26, 255});
    DrawRectangle(0, menu, MAP_WIDTH * TILE_SIZE, 2, (Color){58, 49, 80, 255});

    DrawText("VIDA", 16, menu + 8, 10, (Color){106, 90, 140, 255});
    for (int i = 0; i < 3; i++) {
        if (i < player->health) {
            DrawRectangle(16 + i * 26, menu + 22, 20, 18, (Color){204, 34, 34, 255});
        } else {
            DrawRectangle(16 + i * 26, menu + 22, 20, 18, (Color){51, 34, 51, 255});
        }
    }

    DrawText("HABITACION", 110, menu + 8, 10, (Color){106, 90, 140, 255});
    if (player->roomId == 0) DrawText("Sala 0", 110, menu + 24, 16, (Color){196, 155, 32, 255});
    if (player->roomId == 1) DrawText("Sala 1", 110, menu + 24, 16, (Color){196, 155, 32, 255});
    if (player->roomId == 2) DrawText("Sala 2", 110, menu + 24, 16, (Color){196, 155, 32, 255});
    if (player->roomId == 3) DrawText("Sala 3", 110, menu + 24, 16, (Color){196, 155, 32, 255});
    if (player->roomId == 4) DrawText("Sala 4", 110, menu + 24, 16, (Color){196, 155, 32, 255});
    if (player->roomId == 5) DrawText("Sala 5", 110, menu + 24, 16, (Color){196, 155, 32, 255});

    DrawText("INVENTARIO", 280, menu + 8, 10, (Color){106, 90, 140, 255});
    DrawRectangle(280, menu + 22, 24, 24, (Color){26, 20, 40, 255});
    if (player->hasItem) {
        if (player->item == 'K') {
            DrawRectangle(284, menu + 26, 16, 16, (Color){255, 215, 0, 255});
        }
        if (player->item == 'G') {
            DrawRectangle(284, menu + 26, 16, 16, (Color){0, 180, 220, 255});
        }
        if (player->item == 'C') {
            DrawRectangle(284, menu + 26, 16, 16, (Color){180, 0, 180, 255});
        }
    }

    DrawText("W,A,S,D moverse - E recoger objeto - ESC salir", 16, menu + 48, 10, (Color){58, 49, 80, 255});
}

bool isWall(Room* room, int x, int y) {
    return room->layout[y][x] == '#';
}