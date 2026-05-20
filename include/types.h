#ifndef TYPES_H
#define TYPES_H

const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;
const int MAX_ROOMS = 6;
const int MAX_ENEMIES = 10;
const int MAX_ITEMS = 10;
const int TILE_SIZE = 32;
const int MENU_HEIGHT= 60;

const int NORTH = 0;
const int SOUTH = 1;
const int EAST = 2;
const int WEST = 3;

struct Player {
    int x = 0;
    int y = 0;
    int roomId = 0;
    int health = 3;
    char symbol = '@';
    char item = ' ';
    bool hasItem = false;
};

struct Enemy {
    int x = 0;
    int y = 0;
    int roomId = 0;
    int type = 0;
    char symbol = 'E';
    bool active = true;
};

struct Item {
    int x = 0;
    int y = 0;
    int roomId = 0;
    int type = 0;
    char symbol = '?';
    bool active = true;
};

struct Room {
    char layout[MAP_HEIGHT][MAP_WIDTH];
    int connections[4] = {-1, -1, -1, -1};
};

#endif