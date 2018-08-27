#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>
#include <utility>
#include <deque>
#include <set>

//this is the kiss sdl library that is used to setup most menus in the game, it is written in C
extern "C" {
#include "kiss_sdl.h"
}
//----------------------------------constants-------------------------------//

namespace fs = std::experimental::filesystem;

//Screen dimension constants
const int g_SCREEN_WIDTH = 1040;
const int g_SCREEN_HEIGHT = 710;

//The dimensions of the level
const int g_LEVEL_WIDTH = 1280;
const int g_LEVEL_HEIGHT = 960;

//Tile constants
const int g_TILE_WIDTH = 80;
const int g_TILE_HEIGHT = 80;
const int g_TOTAL_TILES = 192;
const int g_TOTAL_TILE_SPRITES = 12;

//The different tile settings, tiles 0->2 do not block movement, the rest do
//all blocking tiles (except water) block line of sight/ranged attacks
const int g_TILE_GRASS = 0;
const int g_TILE_DIRT = 1;
const int g_TILE_STONE = 2;
const int g_TILE_CENTER = 3;
const int g_TILE_TOP = 4;
const int g_TILE_TOPRIGHT = 5;
const int g_TILE_RIGHT = 6;
const int g_TILE_WATER = 7;
const int g_TILE_BOTTOM = 8;
const int g_TILE_BOTTOMLEFT = 9;
const int g_TILE_LEFT = 10;
const int g_TILE_TOPLEFT = 11;