#include "game.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "raylib.h"

Sound crearSonido(int frecuencia, int duracion) {
    int samples = 44100 * duracion / 1000;
    short data[44100];
    for (int i = 0; i < samples; i++) {
        if (i % (44100 / frecuencia) < (44100 / frecuencia / 2)) {
            data[i] = 5000;
        } else {
            data[i] = -5000;
        }
    }
    Wave wave;
    wave.frameCount = samples;
    wave.sampleRate = 44100;
    wave.sampleSize = 16;
    wave.channels = 1;
    wave.data = data;
    return LoadSoundFromWave(wave);
}

void initGame(Room rooms[], Player* player, Enemy enemies[], int totalEnemies, Item items[], int totalItems) {
    initRooms(rooms);
    initEnemies(enemies, totalEnemies);

    items[0].x = 10;
    items[0].y = 5;
    items[0].roomId = 2;
    items[0].symbol = 'K';
    items[0].active = true;

    items[1].x = 8;
    items[1].y = 10;
    items[1].roomId = 4;
    items[1].symbol = 'G';
    items[1].active = true;

    items[2].x = 5;
    items[2].y = 7;
    items[2].roomId = 1;
    items[2].symbol = 'C';
    items[2].active = true;

    for (int i = 3; i < totalItems; i++) {
        items[i].active = false;
    }

    player->x = MAP_WIDTH / 2;
    player->y = MAP_HEIGHT / 2;
    player->roomId = 0;
    player->health = 3;
    player->hasItem = false;
    player->item = ' ';
}

bool checkVictory(Item items[]) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (items[i].active && items[i].roomId == 5) {
            count = count + 1;
        }
    }
    if (count == 3) {
        return true;
    }
    return false;
}

void showIntro() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){10, 10, 20, 255});

        DrawText("DUNGEON CRAWLER", 100, 60, 36, (Color){196, 155, 32, 255});

        DrawText("OBJETIVO:", 60, 140, 16, (Color){51, 204, 51, 255});
        DrawText("Encuentra los 3 objetos y llevalos a la Sala 5", 60, 170, 14, (Color){160, 150, 180, 255});

        DrawText("OBJETOS:", 60, 210, 16, (Color){51, 204, 51, 255});
        DrawRectangle(60, 235, 16, 16, (Color){255, 215, 0, 255});
        DrawText("K - Llave  (Sala 2)", 85, 237, 14, (Color){160, 150, 180, 255});
        DrawRectangle(60, 260, 16, 16, (Color){0, 180, 220, 255});
        DrawText("G - Gema   (Sala 4)", 85, 262, 14, (Color){160, 150, 180, 255});
        DrawRectangle(60, 285, 16, 16, (Color){180, 0, 180, 255});
        DrawText("C - Corona (Sala 1)", 85, 287, 14, (Color){160, 150, 180, 255});

        DrawText("CONTROLES:", 60, 325, 16, (Color){51, 204, 51, 255});
        DrawText("W,A,S,D - Moverse", 60, 355, 14, (Color){160, 150, 180, 255});
        DrawText("E - Recoger / Soltar objeto", 60, 375, 14, (Color){160, 150, 180, 255});
        DrawText("ESC - Salir", 60, 395, 14, (Color){160, 150, 180, 255});

        DrawText("ENEMIGOS:", 300, 210, 16, (Color){51, 204, 51, 255});
        DrawRectangle(300, 235, 16, 16, (Color){204, 34, 34, 255});
        DrawText("E - Dragon lento", 325, 237, 14, (Color){160, 150, 180, 255});
        DrawRectangle(300, 260, 16, 16, (Color){204, 119, 0, 255});
        DrawText("F - Dragon rapido", 325, 262, 14, (Color){160, 150, 180, 255});
        DrawRectangle(300, 285, 16, 16, (Color){150, 0, 150, 255});
        DrawText("R - Dragon muy rapido", 325, 287, 14, (Color){160, 150, 180, 255});
        DrawRectangle(300, 310, 16, 16, (Color){200, 200, 200, 255});
        DrawText("X - Dragon diagonal", 325, 312, 14, (Color){160, 150, 180, 255});

        DrawText("Tienes 3 vidas. Cuidado con los dragones!", 60, 430, 14, (Color){204, 34, 34, 255});

        DrawText("Presiona ENTER para comenzar", 120, 480, 16, (Color){106, 90, 140, 255});

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) {
            return;
        }
    }
}

void gameLoop(Room rooms[], Player* player, Enemy enemies[], int totalEnemies, Item items[], int totalItems) {
    showIntro();

    Sound sonidoMover = crearSonido(400, 50);
    Sound sonidoRecoger = crearSonido(800, 100);
    Sound sonidoDano = crearSonido(200, 200);
    Sound sonidoGanar = crearSonido(600, 300);

    int turno = 0;
    bool perdi = false;
    bool gane = false;

    while (!WindowShouldClose() && !perdi && !gane) {
        char key = 0;

        if (IsKeyPressed(KEY_W)) key = 'w';
        if (IsKeyPressed(KEY_A)) key = 'a';
        if (IsKeyPressed(KEY_S)) key = 's';
        if (IsKeyPressed(KEY_D)) key = 'd';
        if (IsKeyPressed(KEY_E)) key = 'e';
        if (IsKeyPressed(KEY_ESCAPE)) break;

        if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
            movePlayer(player, &rooms[player->roomId], key);
            PlaySound(sonidoMover);
            checkDoor(player, rooms);

            turno = turno + 1;
            moveEnemies(enemies, totalEnemies, player, &rooms[player->roomId], turno);

            if (checkEnemyCollision(enemies, totalEnemies, player)) {
                PlaySound(sonidoDano);
                player->x = MAP_WIDTH / 2;
                player->y = MAP_HEIGHT / 2;
                player->roomId = 0;
                initEnemies(enemies, totalEnemies);
                if (player->health <= 0) {
                    perdi = true;
                }
            }
        }

        if (key == 'e') {
            handleItem(player, items, totalItems);
            PlaySound(sonidoRecoger);
            if (checkVictory(items)) {
                PlaySound(sonidoGanar);
                gane = true;
            }
        }

        BeginDrawing();
        ClearBackground((Color){10, 10, 20, 255});
        drawRoom(&rooms[player->roomId], player, enemies, totalEnemies, items, totalItems);

        int menuY = MAP_HEIGHT * TILE_SIZE;
        int count = 0;
        for (int i = 0; i < 3; i++) {
            if (items[i].active && items[i].roomId == 5) {
                count = count + 1;
            }
        }
        if (count == 0) DrawText("Objetos en Sala 5: 0 / 3", 350, menuY + 24, 12, (Color){196, 155, 32, 255});
        if (count == 1) DrawText("Objetos en Sala 5: 1 / 3", 350, menuY + 24, 12, (Color){196, 155, 32, 255});
        if (count == 2) DrawText("Objetos en Sala 5: 2 / 3", 350, menuY + 24, 12, (Color){196, 155, 32, 255});
        if (count == 3) DrawText("Objetos en Sala 5: 3 / 3", 350, menuY + 24, 12, (Color){196, 155, 32, 255});

        EndDrawing();
    }

    UnloadSound(sonidoMover);
    UnloadSound(sonidoRecoger);
    UnloadSound(sonidoDano);
    UnloadSound(sonidoGanar);

    if (perdi || gane) {
        bool waiting = true;
        while (!WindowShouldClose() && waiting) {
            BeginDrawing();
            ClearBackground((Color){10, 10, 20, 255});
            if (gane) {
                DrawText("GANASTE!", 160, 180, 40, (Color){51, 204, 51, 255});
                DrawText("Llevaste los 3 objetos a la sala final", 70, 240, 16, (Color){196, 155, 32, 255});
            } else {
                DrawText("GAME OVER", 140, 180, 40, (Color){204, 34, 34, 255});
                DrawText("Los dragones te derrotaron", 120, 240, 16, (Color){106, 90, 140, 255});
            }
            DrawText("Presiona R para reiniciar", 140, 300, 16, (Color){106, 90, 140, 255});
            DrawText("Presiona ESC para salir", 148, 330, 16, (Color){58, 49, 80, 255});
            EndDrawing();

            if (IsKeyPressed(KEY_R)) {
                initGame(rooms, player, enemies, totalEnemies, items, totalItems);
                gameLoop(rooms, player, enemies, totalEnemies, items, totalItems);
                waiting = false;
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                waiting = false;
            }
        }
    }
}