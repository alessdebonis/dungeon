cmake_minimum_required(VERSION 3.14)
project(dungeon)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

include_directories(include)

add_executable(dungeon
    src/main.cpp
    src/map.cpp
    src/player.cpp
    src/game.cpp
    src/enemy.cpp
)

target_link_libraries(dungeon raylib)