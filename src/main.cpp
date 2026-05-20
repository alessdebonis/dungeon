#include "types.h"
#include "game.h"
#include "raylib.h"

int main() {
    InitWindow(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE + MENU_HEIGHT, "Dungeon Crawler");
    SetTargetFPS(60);
    InitAudioDevice();

    Room rooms[MAX_ROOMS];
    Player player;
    Enemy enemies[MAX_ENEMIES];
    Item items[MAX_ITEMS];

    initGame(rooms, &player, enemies, MAX_ENEMIES, items, MAX_ITEMS);
    gameLoop(rooms, &player, enemies, MAX_ENEMIES, items, MAX_ITEMS);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}