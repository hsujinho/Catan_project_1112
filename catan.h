#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "linuxlist.h"

#define X_LONG 11
#define Y_LONG 12

#define TYPE_LANDBETWEEN 1
#define TYPE_PIECE 2
#define TYPE_PORT_ANY 3
#define TYPE_PORT_BRICK 4
#define TYPE_PORT_LUMBER 5
#define TYPE_PORT_WOOL 6
#define TYPE_PORT_GRAIN 7
#define TYPE_PORT_ORE 8

#define BRICK 0
#define LUMBER 1
#define WOOL 2
#define GRAIN 3
#define ORE 4

#define RESOURCE_NUM 19

#define ECOSYSTEM 0
#define MINE 1
#define FOREST 2
#define PASTURE 3
#define FIELD 4
#define DESERT 5

#define PIECE_POINT 1
#define LANDBETWEEN_POINT 2

#define NOBODY 0
#define PLAYER1 1
#define PLAYER2 2
#define PLAYER3 3
#define PLAYER4 4

#define PIECE_NUM 19
#define LAND_NUM 54

typedef struct Point{
    const int x;
    const int y;
}point;

typedef struct Player{
    const int id;
    int VP;
    int resource[5]; // 0: brick, 1: lumber, 2: wool, 3: grain, 4: ore
    int number_of_knights;
    int length_of_road;
    int number_of_dev_card;
    bool has_longest_road;
    bool has_most_knights;
}player;

typedef struct Piece{
    point p;
    const int eco_type;
    int number;
    bool robberFlag;
}piece;

typedef struct LandBetween{
    point p;
    int type;
    bool has_building;
    int owner;
    int building;
}landbetween;

typedef struct Road{
    point start;
    point end;
    int owner;
}road;

typedef struct DevCard{
    int type;
    bool used;
    struct list_head node;
}devcard;

// record the valid point to hold data and the type of the point
const int valid_point_mat[Y_LONG][X_LONG] = {
    {0, 0, 0, TYPE_PORT_ANY, 0, TYPE_PORT_WOOL, 0, TYPE_LANDBETWEEN, 0, 0, 0},
    {0, 0, TYPE_PORT_ANY, 0, TYPE_LANDBETWEEN, 0, TYPE_PORT_WOOL, 0, TYPE_LANDBETWEEN, 0, 0},
    {0, 0, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_PORT_ANY, 0, 0},
    {0, TYPE_PORT_ORE, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_PORT_ANY, 0},
    {0, TYPE_PORT_ORE, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, 0},
    {TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_PORT_ANY},
    {TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_PORT_ANY},
    {0, TYPE_PORT_GRAIN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0},
    {0, TYPE_PORT_GRAIN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_PORT_BRICK, 0},
    {0, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_LANDBETWEEN, 0, TYPE_PORT_BRICK, 0, 0},
    {0, 0, TYPE_PORT_ANY, TYPE_PIECE, TYPE_LANDBETWEEN, TYPE_PIECE, TYPE_PORT_LUMBER, TYPE_PIECE, TYPE_LANDBETWEEN, 0, 0},
    {0, 0, 0, TYPE_PORT_ANY, 0, TYPE_PORT_LUMBER, 0, TYPE_LANDBETWEEN, 0, 0, 0},
};

int resource[5] = {RESOURCE_NUM, RESOURCE_NUM, RESOURCE_NUM, RESOURCE_NUM, RESOURCE_NUM};

void init_game();
player **init_player();
void init_map(piece **pieces, landbetween **lands, road **roads);
piece **init_piece();
landbetween **init_landbetween();
road **init_road();
int build_road(road **roads, player **players, int player_id, point start, point end);
int build_building(landbetween **lands, player **players, int player_id, point p, int building);
void take_initial_resource(landbetween **lands, player **players, int player_id, int dice);
void player_round(const int player_id, landbetween **lands, player **players, piece **pieces, road **roads);
int roll_dice();
int take_resource();
void robber_situation();
int discard_resource();
int build_action();
bool is_resource_enough();
point pick_land();
void trade_action();
void trade_with_bank();
void trade_with_player();
void trade_with_port();
void knight_action();
void monopoly_action();
void free_road_building_action();
void year_of_plenty_action();