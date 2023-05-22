#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "linuxlist.h"

#define ARR_NUM(arr, type) (sizeof(arr) / sizeof(type))
#define POINT_AROUND_PIECE(name, x, y) point name[6] = {{x, y-1}, {x-1, y}, {x+1, y}, {x-1, y+1}, {x+1, y+1}, {x, y+2}}

// randomize times
#define TIMES 100

// map size
#define X_LONG 11
#define Y_LONG 12

// building type
#define SETTLEMENT 1
#define CITY 2

#define TYPE_LANDBETWEEN 1
#define TYPE_PIECE 2
#define TYPE_PORT_ANY 3
#define TYPE_PORT_BRICK 4
#define TYPE_PORT_LUMBER 5
#define TYPE_PORT_WOOL 6
#define TYPE_PORT_GRAIN 7
#define TYPE_PORT_ORE 8

// resource type
#define BRICK 0
#define LUMBER 1
#define WOOL 2
#define GRAIN 3
#define ORE 4

// piece type
#define HILL 0
#define FOREST 1
#define MOUNTAIN 2
#define FIELD 3
#define PASTURE 4
#define DESERT 5

#define PIECE_POINT 1
#define LANDBETWEEN_POINT 2

#define NOBODY 0
#define PLAYER1 1
#define PLAYER2 2
#define PLAYER3 3
#define PLAYER4 4

// number of element 
#define PIECE_NUM 19
#define LAND_NUM 54
#define PLAYER_NUM 4
#define ROAD_NUM 72
#define RESOURCE_NUM 19

typedef struct Point{
    int x;
    int y;
}point;

typedef struct Player{
    int id;
    int VP;
    int resource[5]; // 0: brick, 1: lumber, 2: wool, 3: grain, 4: ore
    int number_of_knights;
    int length_of_road;
    int number_of_dev_card;
    bool has_longest_road;
    bool has_most_knights;
    struct list_head *devcard_list;
}player;

typedef struct Piece{
    point p;
    int eco_type;
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
int eco_num[6] = {3, 4, 3, 4, 4, 1};

void randomize(void **array, size_t n, size_t size);
void init_game(piece ***pieces, landbetween ***lands, road ***roads, player ***players);
player **init_player();
void init_map(piece **pieces, landbetween **lands, road **roads);
piece **init_piece();
int piece_index(int x, int y, piece **pieces);
landbetween **init_landbetween();
road **init_road();
int build_road(road **roads, player **players, int player_id, point start, point end);
int build_building(landbetween **lands, player **players, int player_id, point p, int building);
void take_initial_resource(landbetween **lands, player **players, int player_id, int dice);
void player_round(const int player_id, landbetween **lands, player **players, piece **pieces, road **roads);
int roll_dice();
int take_resource(int DP, piece **pieces, player **players, landbetween **lands, int *resource, int first_id);
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

void free_player(player **players);
void free_piece(piece **pieces);
void free_landbetween(landbetween **lands);
void free_road(road **roads);

void free_player(player **players){
    for(int i = 0; i < PLAYER_NUM; i++){
        free(players[i]->devcard_list);
        free(players[i]);
    }
    free(players);
}

void free_piece(piece **pieces){
    for(int i = 0; i < PIECE_NUM; i++)
        free(pieces[i]);
    free(pieces);
}

void free_landbetween(landbetween **lands){
    for(int i = 0; i < LAND_NUM; i++)
        free(lands[i]);
    free(lands);
}

void free_road(road **roads){
    for(int i = 0; i < ROAD_NUM; i++)
        free(roads[i]);
    free(roads);
}

void randomize(void **array, size_t n, size_t size){
    srand(time(NULL));
    if(n > 1){
        for(int i = 0; i < TIMES; i++){
            int a = rand() % n;
            int b = rand() % n;
            if(a == b)
                continue;

            void *temp = malloc(size);
            memcpy(temp, array[a], size);
            memcpy(array[a], array[b], size);
            memcpy(array[b], temp, size);
            free(temp);
        }
    }
}

void init_game(piece ***pieces, landbetween ***lands, road ***roads, player ***players){
    *pieces = init_piece();
    *players = init_player();
    *lands = init_landbetween();
    *roads = init_road();   
}

player **init_player(){
    player **players = (player **)malloc(sizeof(player *) * PLAYER_NUM);
    for(int i = 0; i < PLAYER_NUM; i++){
        players[i] = (player *)malloc(sizeof(player));
        players[i]->id = i + 1;
        players[i]->VP = 0;
        for(int j = 0; j < 5; j++)
            players[i]->resource[j] = 0;
        players[i]->number_of_knights = 0;
        players[i]->length_of_road = 0;
        players[i]->number_of_dev_card = 0;
        players[i]->has_longest_road = false;
        players[i]->has_most_knights = false;
        struct list_head *devcard_list = (struct list_head *)malloc(sizeof(struct list_head));
        devcard_list->next = devcard_list;
        devcard_list->prev = devcard_list;
        players[i]->devcard_list = devcard_list;
    }

    randomize((void **)players, PLAYER_NUM, sizeof(player *));
    return players;
}

piece **init_piece(){
    srand(time(NULL));
    piece **pieces = (piece **)malloc(sizeof(piece *) * PIECE_NUM);
    int p = 0;
    for(int i = 0; i < Y_LONG; i++){
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == TYPE_PIECE){
                pieces[p] = (piece *)malloc(sizeof(piece));
                pieces[p]->p.x = j;
                pieces[p]->p.y = i;
                while(1){
                    int eco_type = rand() % 6;
                    if(eco_num[eco_type] > 0){
                        if(eco_type == DESERT)
                            pieces[p]->robberFlag = true;
                        else
                            pieces[p]->robberFlag = false;
                        pieces[p]->eco_type = eco_type;
                        eco_num[eco_type]--;
                        break;
                    }
                }
                p++;
            }
        }
    }

    const point pos[PIECE_NUM] = {
        {1, 6}, {2, 8}, {3, 10}, {5, 10}, {7, 10}, {8, 8},
        {9, 6}, {8, 4}, {7, 2}, {5, 2}, {3, 2}, {2, 4},
        {3, 6}, {4, 8}, {6, 8}, {7, 6}, {6, 4}, {4, 4}, {5, 6},
    };

    const int val[PIECE_NUM-1] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};

    for(int i = 0; i < PIECE_NUM - 1; i++){
        for(int j = 0; j < PIECE_NUM; j++){
            if(pieces[j]->p.x == pos[i].x && pieces[j]->p.y == pos[i].y){
                if(pieces[j]->eco_type != DESERT){
                    pieces[j]->number = val[i];
                    pieces[j]->robberFlag = false;
                }
                else{
                    pieces[j]->number = 0;
                }
                break;
            }
        }
    }

    eco_num[DESERT] = 1;
    eco_num[HILL] = 3;
    eco_num[FOREST] = 4;
    eco_num[MOUNTAIN] = 3;
    eco_num[FIELD] = 4;
    eco_num[PASTURE] = 4;

    randomize((void **)pieces, PIECE_NUM, sizeof(piece *));
    return pieces;
}

int piece_index(int x, int y, piece **pieces){
    for(int i = 0; i < PIECE_NUM; i++){
        if(pieces[i]->p.x == x && pieces[i]->p.y == y)
            return i;
    }
    return -1;
}

int land_index(const int x, const int y, landbetween **lands){
    for(int i = 0; i < LAND_NUM; i++){
        if(lands[i]->p.x == x && lands[i]->p.y == y)
            return i;
    }
    return -1;
}

int player_index(const int id, player **players){
    for(int i = 0; i < PLAYER_NUM; i++){
        if(players[i]->id == id)
            return i;
    }
    return -1;
}

landbetween **init_landbetween(){
    landbetween **lands = (landbetween **)malloc(sizeof(landbetween *) * LAND_NUM);
    for(int i = 0; i < LAND_NUM; i++){
        lands[i] = (landbetween *)malloc(sizeof(landbetween));
        lands[i]->has_building = false;
        lands[i]->owner = -1;
        lands[i]->building = -1;
    }

    int p = 0;
    for(int i = 0; i < Y_LONG; i++){
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] != TYPE_PIECE && valid_point_mat[i][j] != 0){
                lands[p]->p.x = j;
                lands[p]->p.y = i;
                lands[p]->type = valid_point_mat[i][j];
                p++;
            }
        }
    }

    return lands;
}

road **init_road(){
    road **roads = (road **)malloc(sizeof(road *) * ROAD_NUM);
    for(int i = 0; i < ROAD_NUM; i++){
        roads[i] = (road *)malloc(sizeof(road));
        roads[i]->owner = -1;
    }

    int p = 0;
    /*      /\/\/\      */
    for(int i = 0; i < 3; i++){
        roads[p]->start.x = 3 + i * 2;
        roads[p]->start.y = 0;
        roads[p+1]->start = roads[p]->start;
        roads[p]->end.x = 2 + i * 2;
        roads[p]->end.y = 1;
        roads[p+1]->end.x = 4 + i * 2;
        roads[p+1]->end.y = 1;
        p += 2;
    }

    /*      | | | |        */
    for(int i = 0; i < 4; i++){
        roads[p]->start.x = 2 + i * 2;
        roads[p]->start.y = 1;
        roads[p]->end.x = 2 + i * 2;
        roads[p]->end.y = 2;
        p++;
    }

    /*      /\/\/\/\        */
    for(int i = 0; i < 4; i++){
        roads[p]->start.x = 2 + i * 2;
        roads[p]->start.y = 2;
        roads[p+1]->start = roads[p]->start;
        roads[p]->end.x = 1 + i * 2;
        roads[p]->end.y = 3;
        roads[p+1]->end.x = 3 + i * 2;
        roads[p+1]->end.y = 3;
        p += 2;
    }

    /*      | | | | |       */
    for(int i = 0; i < 5; i++){
        roads[p]->start.x = 1 + i * 2;
        roads[p]->start.y = 3;
        roads[p]->end.x = 1 + i * 2;
        roads[p]->end.y = 4;
        p++;
    }

    /*      /\/\/\/\/\      */
    for(int i = 0; i < 5; i++){
        roads[p]->start.x = 1 + i * 2;
        roads[p]->start.y = 4;
        roads[p+1]->start = roads[p]->start;
        roads[p]->end.x = 0 + i * 2;
        roads[p]->end.y = 5;
        roads[p+1]->end.x = 2 + i * 2;
        roads[p+1]->end.y = 5;
        p += 2;
    }

    /*      | | | | | |     */
    for(int i = 0; i < 6; i++){
        roads[p]->start.x = i * 2;
        roads[p]->start.y = 5;
        roads[p]->end.x = i * 2;
        roads[p]->end.y = 6;
        p++;
    }

    /*      \/\/\/\/\/      */
    for(int i = 0; i < 5; i++){
        roads[p]->end.x = 1 + i * 2;
        roads[p]->end.y = 7;
        roads[p+1]->end = roads[p]->end;
        roads[p]->start.x = i * 2;
        roads[p]->start.y = 6;
        roads[p+1]->start.x = 2 + i * 2;
        roads[p+1]->start.y = 6;
        p += 2;
    }

    /*      | | | | |       */
    for(int i = 0; i < 5; i++){
        roads[p]->start.x = 1 + i * 2;
        roads[p]->start.y = 7;
        roads[p]->end.x = 1 + i * 2;
        roads[p]->end.y = 8;
        p++;
    }

    /*      \/\/\/\/        */
    for(int i = 0; i < 4; i++){
        roads[p]->end.x = 2 + i * 2;
        roads[p]->end.y = 9;
        roads[p+1]->end = roads[p]->end;
        roads[p]->start.x = 1 + i * 2;
        roads[p]->start.y = 8;
        roads[p+1]->start.x = 3 + i * 2;
        roads[p+1]->start.y = 8;
        p += 2;
    }

    /*      | | | |     */
    for(int i = 0; i < 4; i++){
        roads[p]->start.x = 2 + i * 2;
        roads[p]->start.y = 9;
        roads[p]->end.x = 2 + i * 2;
        roads[p]->end.y = 10;
        p++;
    }

    /*      \/\/\/      */
    for(int i = 0; i < 3; i++){
        roads[p]->end.x = 3 + i * 2;
        roads[p]->end.y = 11;
        roads[p+1]->end = roads[p]->end;
        roads[p]->start.x = 2 + i * 2;
        roads[p]->start.y = 10;
        roads[p+1]->start.x = 4 + i * 2;
        roads[p+1]->start.y = 10;
        p += 2;
    }

    return roads;
}

int roll_dice(){
    srand(time(NULL));
    return rand() % 6 + rand() % 6 + 2;
}

int take_resource(int DP, piece **pieces, player **players, landbetween **lands, int *resource, int first_id){
    int turn[4] = {0};
    for(int i = 0; i < 4; i++){
        int idx = (player_index(first_id, players) + i) % 4;
        turn[i] = players[idx]->id;
    }

    // for each player in order
    for(int k = 0; k < 4; k++){
        // for each piece with same dice point && doesn't have robber
        for(int i = 0; i < PIECE_NUM; i++){
            if(DP == pieces[i]->number && pieces[i]->robberFlag == false){
                const int x = pieces[i]->p.x;
                const int y = pieces[i]->p.y;
                // for each land between around the piece
                POINT_AROUND_PIECE(pos, x, y);
                for(int j = 0; j < 6; j++){
                    // if the land between has building && the owner is the player
                    if(lands[land_index(pos[j].x, pos[j].y, lands)]->has_building && lands[land_index(pos[j].x, pos[j].y, lands)]->owner == turn[k]){
                        const int point = lands[land_index(pos[j].x, pos[j].y, lands)]->building;
                        // if the resource is not enough
                        if(resource[pieces[i]->eco_type] < point){
                            players[player_index(turn[k], players)]->resource[pieces[i]->eco_type] += resource[pieces[i]->eco_type];
                            resource[pieces[i]->eco_type] = 0;
                        }
                        else{
                            players[player_index(turn[k], players)]->resource[pieces[i]->eco_type] += point;
                            resource[pieces[i]->eco_type] -= point;
                        }
                    }
                }
            }
        }
    }
    
    return 1;
}
