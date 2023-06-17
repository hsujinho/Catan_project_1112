#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>
#include "linuxlist.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define PIECE_SIZE 100
#define VIC_LEN (PIECE_SIZE / 4 + PIECE_SIZE / 20)
#define NUM_SIZE (PIECE_SIZE / 4 + PIECE_SIZE / 10)
#define LAND_SIZE (PIECE_SIZE / 4 + PIECE_SIZE / 10)
#define NUM_OFFSET ((PIECE_SIZE - NUM_SIZE) / 2)
#define Y_OFFSET 80
#define NUMBER_PIXEL 35

#define ARR_NUM(arr, type) (sizeof(arr) / sizeof(type))
#define POINT_AROUND_PIECE(name, x, y, d) point name[6] = {{x, y-2*d}, {x-d, y}, {x+d, y}, {x-d, y-d}, {x+d, y-d}, {x, y+d}}
#define EPOINT_AROUND_PIECE(name, x, y, d) point name[6] = {{x, y-2*d}, {x-2*d, y-d}, {x-2*d, y+d}, {x, y+2*d}, {x+2*d, y+d}, {x+2*d, y-d}}
#define PRESS_ENTER printf("Press Enter to continue...\n"); \
                    char c = 0;\
                    scanf("%c", &c);

// randomize times
#define TIMES 100

// map size
#define X_LONG 11
#define Y_LONG 12

// building type
#define ROAD 0
#define SETTLEMENT 1
#define CITY 2

// dev card type
#define KNIGHT 0
#define MONOPOLY 1
#define FREE_ROAD_BUILDING 2
#define YEAR_OF_PLENTY 3
#define VICTORY_POINT 4

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

// piece type  0: brick, 1: lumber, 2: wool, 3: grain, 4: ore
#define HILL 0
#define FOREST 1
#define MOUNTAIN 4
#define FIELD 3
#define PASTURE 2
#define DESERT 5

#define PIECE_POINT 1
#define LANDBETWEEN_POINT 2

#define NOBODY -1
#define PLAYER1 1
#define PLAYER2 2
#define PLAYER3 3
#define PLAYER4 4

#define LD 0
#define RD 1
#define D  2

// number of element 
#define PIECE_NUM 19
#define LAND_NUM 54
#define PLAYER_NUM 4
#define ROAD_NUM 72
#define RESOURCE_NUM 19
#define KNIGHT_NUM 14
#define MONOPOLY_NUM 2
#define FREE_ROAD_BUILDING_NUM 2
#define YEAR_OF_PLENTY_NUM 2
#define VICTORY_POINT_NUM 5
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
    int number_of_building[3];
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
    int dir;
}road;

typedef struct DevCard{
    int type;
    bool used;
    struct list_head node;
}devcard;

typedef struct mapInfo{
    player **players;
    piece **pieces;
    landbetween **lands;
    road **roads;
    struct list_head *devcards;
}mapInfo;

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
const point three_pieces_lands_pos[24] = {
    {4, 2}, {6, 2}, 
    {3, 3}, {5, 3}, {7, 3},
    {3, 4}, {5, 4}, {7, 4},
    {2, 5}, {4, 5}, {6, 5}, {8, 5},
    {2, 6}, {4, 6}, {6, 6}, {8, 6},
    {3, 7}, {5, 7}, {7, 7},
    {3, 8}, {5, 8}, {7, 8},
    {4, 9}, {6, 9},
};

// function declaration

// relate SDL
void render_pieces(SDL_Renderer *renderer, mapInfo *map);
void render_lands(SDL_Renderer *renderer, mapInfo *map);
void render_roads(SDL_Renderer *renderer, mapInfo *map);
void render_map(SDL_Renderer *renderer, mapInfo *map);

// some tool
void randomize(void **array, size_t n, size_t size);
int list_head_length(struct list_head *head);
struct list_head *list_head_at(struct list_head *head, int index);
void init_game(piece ***pieces, landbetween ***lands, road ***roads, player ***players, struct list_head **devcards);
player **init_player();
void init_map(piece **pieces, landbetween **lands, road **roads);
piece **init_piece();
int piece_index(int x, int y, piece **pieces);
landbetween **init_landbetween();
road **init_road();
struct list_head *init_devcard();
void player_round(const int player_id, landbetween **lands, player **players, piece **pieces, road **roads);
int roll_dice();
int take_resource(int DP, mapInfo *map, int *resource, int first_id);
void robber_situation(mapInfo *map, int id, SDL_Renderer *renderer);
int discard_resource(player **players, int player_id);
void resource_to_discard(player *player, int **decide_resource);
point move_robber(mapInfo *map, const int id);
point pick_land();
void trade_action( mapInfo *info, int32_t id );
void trade_with_bank( player *player_A, landbetween **maps );
void trade_with_player( player *candidate, player *player_A );
int32_t trade_with_port( player *player_A, landbetween **maps, int32_t get_choice );
void knight_action();
void monopoly_action();
void year_of_plenty_action();
bool is_in_three_pieces_lands_pos(const int x, const int y);
bool is_land_occupied(mapInfo *map, const int x, const int y, const int id);
bool is_land_connect_other_building(mapInfo *map, const int x, const int y);
bool is_robber_on_piece(mapInfo *map, const int x, const int y);

void free_player(player **players);
void free_piece(piece **pieces);
void free_landbetween(landbetween **lands);
void free_road(road **roads);
void free_devcard(struct list_head *devcards);

void print_player(mapInfo *map);
void print_player(mapInfo *map){
    player **p = map->players;
    for(int i = 0; i < PLAYER_NUM; i++){
        printf("player %d: (VP: %d)\n", p[i]->id, p[i]->VP);
        printf("resource: brick: %d, lumber: %d, wool: %d, grain: %d, ore: %d\n", p[i]->resource[0], p[i]->resource[1], p[i]->resource[2], p[i]->resource[3], p[i]->resource[4]);
        printf("number of knights: %d\n", p[i]->number_of_knights);
        printf("length of road: %d\n", p[i]->length_of_road);
        printf("number of building: %d, %d, %d\n", p[i]->number_of_building[0], p[i]->number_of_building[1], p[i]->number_of_building[2]);
        printf("number of dev card: %d\n", p[i]->number_of_dev_card);
    }
}

// SDL implement
void render_pieces(SDL_Renderer *renderer, mapInfo *map){
    //set background color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    piece **pieces = map->pieces;

    for(int i = 0; i < PIECE_NUM; i++){
        int x = pieces[i]->p.x;
        int y = pieces[i]->p.y;
        x *= 2;
        y = y + y / 2 - 1;
        x *= 20;
        y *= 20; 

        SDL_Surface *piece_surface = NULL;
        if(pieces[i]->eco_type == HILL)
            piece_surface = IMG_Load("picture/hill.png");
        else if(pieces[i]->eco_type == MOUNTAIN)
            piece_surface = IMG_Load("picture/mountain.png");
        else if(pieces[i]->eco_type == FIELD)
            piece_surface = IMG_Load("picture/field.png");
        else if(pieces[i]->eco_type == FOREST)
            piece_surface = IMG_Load("picture/forest.png");
        else if(pieces[i]->eco_type == PASTURE)
            piece_surface = IMG_Load("picture/pasture.png");
        else if(pieces[i]->eco_type == DESERT)
            piece_surface = IMG_Load("picture/desert.png");
        else
            continue;
        SDL_Texture *piece_texture = SDL_CreateTextureFromSurface(renderer, piece_surface);
        SDL_Rect piece_rect = {x, y, PIECE_SIZE, PIECE_SIZE};
        SDL_RenderCopy(renderer, piece_texture, NULL, &piece_rect);
        SDL_DestroyTexture(piece_texture);
        SDL_FreeSurface(piece_surface);

        SDL_Surface *num_surface = NULL;
        if(pieces[i]->number == 2)
            num_surface = IMG_Load("picture/2.png");
        else if(pieces[i]->number == 3)
            num_surface = IMG_Load("picture/3.png");
        else if(pieces[i]->number == 4)
            num_surface = IMG_Load("picture/4.png");
        else if(pieces[i]->number == 5)
            num_surface = IMG_Load("picture/5.png");
        else if(pieces[i]->number == 6)
            num_surface = IMG_Load("picture/6.png");
        else if(pieces[i]->number == 8)
            num_surface = IMG_Load("picture/8.png");
        else if(pieces[i]->number == 9)
            num_surface = IMG_Load("picture/9.png");
        else if(pieces[i]->number == 10)
            num_surface = IMG_Load("picture/10.png");
        else if(pieces[i]->number == 11)
            num_surface = IMG_Load("picture/11.png");
        else if(pieces[i]->number == 12)
            num_surface = IMG_Load("picture/12.png");

        SDL_Texture *num_texture = SDL_CreateTextureFromSurface(renderer, num_surface);
        SDL_Rect num_rect = {x + NUM_OFFSET, y + NUM_OFFSET, NUM_SIZE, NUM_SIZE};
        SDL_RenderCopy(renderer, num_texture, NULL, &num_rect);
        SDL_DestroyTexture(num_texture);
        SDL_FreeSurface(num_surface);   
    }

    SDL_RenderPresent(renderer);
}

void render_map(SDL_Renderer *renderer, mapInfo *map){
    //set background color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    piece **pieces = map->pieces;
    landbetween **lands = map->lands;
    road **roads = map->roads;

    for(int i = 0; i < PIECE_NUM; i++){
        int x = pieces[i]->p.x;
        int y = pieces[i]->p.y;
        x *= 2;
        y = y + y / 2 - 1;
        x *= VIC_LEN;
        y *= VIC_LEN; 

        SDL_Surface *piece_surface = NULL;
        if(pieces[i]->eco_type == HILL)
            piece_surface = IMG_Load("picture/hill.png");
        else if(pieces[i]->eco_type == MOUNTAIN)
            piece_surface = IMG_Load("picture/mountain.png");
        else if(pieces[i]->eco_type == FIELD)
            piece_surface = IMG_Load("picture/field.png");
        else if(pieces[i]->eco_type == FOREST)
            piece_surface = IMG_Load("picture/forest.png");
        else if(pieces[i]->eco_type == PASTURE)
            piece_surface = IMG_Load("picture/pasture.png");
        else if(pieces[i]->eco_type == DESERT)
            piece_surface = IMG_Load("picture/desert.png");
        else
            continue;
        SDL_Texture *piece_texture = SDL_CreateTextureFromSurface(renderer, piece_surface);
        SDL_Rect piece_rect = {x, y, PIECE_SIZE, PIECE_SIZE};
        SDL_RenderCopy(renderer, piece_texture, NULL, &piece_rect);
        SDL_DestroyTexture(piece_texture);
        SDL_FreeSurface(piece_surface);

        SDL_Surface *num_surface = NULL;
        SDL_Surface *rob_surface = NULL;
        if(pieces[i]->number == 2)
            num_surface = IMG_Load("picture/2.png");
        else if(pieces[i]->number == 3)
            num_surface = IMG_Load("picture/3.png");
        else if(pieces[i]->number == 4)
            num_surface = IMG_Load("picture/4.png");
        else if(pieces[i]->number == 5)
            num_surface = IMG_Load("picture/5.png");
        else if(pieces[i]->number == 6)
            num_surface = IMG_Load("picture/6.png");
        else if(pieces[i]->number == 8)
            num_surface = IMG_Load("picture/8.png");
        else if(pieces[i]->number == 9)
            num_surface = IMG_Load("picture/9.png");
        else if(pieces[i]->number == 10)
            num_surface = IMG_Load("picture/10.png");
        else if(pieces[i]->number == 11)
            num_surface = IMG_Load("picture/11.png");
        else if(pieces[i]->number == 12)
            num_surface = IMG_Load("picture/12.png");
        
        SDL_Texture *num_texture = SDL_CreateTextureFromSurface(renderer, num_surface);
        SDL_Rect num_rect = {x + NUM_OFFSET, y + NUM_OFFSET, NUM_SIZE, NUM_SIZE};
        SDL_RenderCopy(renderer, num_texture, NULL, &num_rect);
        SDL_DestroyTexture(num_texture);

        
        if(pieces[i]->robberFlag == true){
            rob_surface = IMG_Load("picture/grain.png");
            SDL_Texture *rob_texture = SDL_CreateTextureFromSurface(renderer, rob_surface);
            SDL_Rect rob_rect = {x + NUM_OFFSET + 10, y + NUM_OFFSET + 10, NUM_SIZE, NUM_SIZE};
            SDL_RenderCopy(renderer, rob_texture, NULL, &rob_rect);
            SDL_DestroyTexture(rob_texture);
            SDL_FreeSurface(rob_surface);
        }   
        

        SDL_FreeSurface(num_surface);   
    }

    for(int i = 0; i < ROAD_NUM; i++){
        int x1 = map->roads[i]->start.x;
        int y1 = map->roads[i]->start.y;
        int x2 = map->roads[i]->end.x;
        int y2 = map->roads[i]->end.y;
        int x = (x1 + x2) / 2;
        int y = (y1 + y2) / 2;
        x *= PIECE_SIZE / 2;
        y *= PIECE_SIZE / 2;

        SDL_Surface *road_surface = NULL;
        if(roads[i]->dir == LD){
            if(roads[i]->owner == NOBODY)
                road_surface = IMG_Load("picture/LD_black.png");
            else if(roads[i]->owner == PLAYER1)
                road_surface = IMG_Load("picture/LD_red.png");
            else if(roads[i]->owner == PLAYER2)
                road_surface = IMG_Load("picture/LD_white.png");
            else if(roads[i]->owner == PLAYER3)
                road_surface = IMG_Load("picture/LD_orange.png");
            else if(roads[i]->owner == PLAYER4)
                road_surface = IMG_Load("picture/LD_blue.png");

            x = roads[i]->start.x;
            x = x * 2 * VIC_LEN;
            y = roads[i]->start.y;
            y = y + y / 2;
            y = y * VIC_LEN;
            y = y + PIECE_SIZE / 2 - PIECE_SIZE / 40;

            double angle = 45 - 26.5650511770;
            SDL_Point center = {PIECE_SIZE / 2, 0};            
            SDL_Rect dstRect = {x, y, PIECE_SIZE / 2, PIECE_SIZE / 2};

            SDL_Texture *road_texture = SDL_CreateTextureFromSurface(renderer, road_surface);
            // SDL_Rect road_rect = {x, y, PIECE_SIZE / 2, PIECE_SIZE / 2};
            // SDL_RenderCopy(renderer, road_texture, NULL, &road_rect);
            SDL_RenderCopyEx(renderer, road_texture, NULL, &dstRect, angle, &center, SDL_FLIP_NONE);
            SDL_DestroyTexture(road_texture);
        }
        else if(roads[i]->dir == RD){
            if(roads[i]->owner == NOBODY)
                road_surface = IMG_Load("picture/RD_black.png");
            else if(roads[i]->owner == PLAYER1)
                road_surface = IMG_Load("picture/RD_red.png");
            else if(roads[i]->owner == PLAYER2)
                road_surface = IMG_Load("picture/RD_white.png");
            else if(roads[i]->owner == PLAYER3)
                road_surface = IMG_Load("picture/RD_orange.png");
            else if(roads[i]->owner == PLAYER4)
                road_surface = IMG_Load("picture/RD_blue.png");

            x = roads[i]->start.x;
            x = x * 2 * VIC_LEN;
            x += PIECE_SIZE / 2 + PIECE_SIZE / 10 + PIECE_SIZE / 40;
            y = roads[i]->start.y;
            y = y + y / 2;
            y = y * VIC_LEN;
            y = y + PIECE_SIZE / 2 - PIECE_SIZE / 40;

            double angle = -1 * (45 - 26.5650511770);
            SDL_Point center = {0, PIECE_SIZE / 2};            
            SDL_Rect dstRect = {x, y, PIECE_SIZE / 2, PIECE_SIZE / 2};

            SDL_Texture *road_texture = SDL_CreateTextureFromSurface(renderer, road_surface);
            // SDL_Rect road_rect = {x, y, PIECE_SIZE / 2, PIECE_SIZE / 2};
            // SDL_RenderCopy(renderer, road_texture, NULL, &road_rect);
            SDL_RenderCopyEx(renderer, road_texture, NULL, &dstRect, angle, &center, SDL_FLIP_NONE);
            SDL_DestroyTexture(road_texture);
        }
        else if(roads[i]->dir == D){
            if(roads[i]->owner == NOBODY)
                road_surface = IMG_Load("picture/D_black.png");
            else if(roads[i]->owner == PLAYER1)
                road_surface = IMG_Load("picture/D_red.png");
            else if(roads[i]->owner == PLAYER2)
                road_surface = IMG_Load("picture/D_white.png");
            else if(roads[i]->owner == PLAYER3)
                road_surface = IMG_Load("picture/D_orange.png");
            else if(roads[i]->owner == PLAYER4)
                road_surface = IMG_Load("picture/D_blue.png");

            x = roads[i]->start.x;
            x = x * 2 * VIC_LEN;
            x += PIECE_SIZE / 4;
            y = roads[i]->start.y;
            y = y + y / 2;
            y = y * VIC_LEN;
            y = y + PIECE_SIZE / 2 + PIECE_SIZE / 20;


            SDL_Texture *land_texture = SDL_CreateTextureFromSurface(renderer, road_surface);
            SDL_Rect land_rect = {x, y, PIECE_SIZE / 2, PIECE_SIZE / 2};
            SDL_RenderCopy(renderer, land_texture, NULL, &land_rect);
            SDL_DestroyTexture(land_texture);
        }
        SDL_FreeSurface(road_surface);
    }

    for(int i = 0; i < LAND_NUM; i++){
        int x = lands[i]->p.x;
        int y = lands[i]->p.y;
        x *= 2;
        y = y + y / 2;
        x *= VIC_LEN;
        y *= VIC_LEN; 

        SDL_Surface *land_surface = NULL;
        if(lands[i]->has_building){
            int own = lands[i]->owner;
            int b= lands[i]->building;

            if(own == PLAYER1){
                if(b == SETTLEMENT)
                    land_surface = IMG_Load("picture/red_settlement.png");
                else if(b == CITY)
                    land_surface = IMG_Load("picture/red_city.png");
            }
            else if(own == PLAYER2){
                if(b == SETTLEMENT)
                    land_surface = IMG_Load("picture/white_settlement.png");
                else if(b == CITY)
                    land_surface = IMG_Load("picture/white_city.png");
            }
            else if(own == PLAYER3){
                if(b == SETTLEMENT)
                    land_surface = IMG_Load("picture/orange_settlement.png");
                else if(b == CITY)
                    land_surface = IMG_Load("picture/orange_city.png");
            }
            else if(own == PLAYER4){
                if(b == SETTLEMENT)
                    land_surface = IMG_Load("picture/blue_settlement.png");
                else if(b == CITY)
                    land_surface = IMG_Load("picture/blue_city.png");
            }
        }

        x = x + PIECE_SIZE / 2 - LAND_SIZE / 2;
        y = y + PIECE_SIZE / 2 - LAND_SIZE / 2;
        SDL_Texture *land_texture = SDL_CreateTextureFromSurface(renderer, land_surface);
        SDL_Rect land_rect = {x, y, LAND_SIZE, LAND_SIZE};
        SDL_RenderCopy(renderer, land_texture, NULL, &land_rect);
        SDL_DestroyTexture(land_texture);
        SDL_FreeSurface(land_surface);
    }   

    SDL_RenderPresent(renderer);
}

// return the length of a list, excluding the head
int list_head_length(struct list_head *head){
    int length = 0;
    struct list_head *pos = head->next;
    while(pos != head){
        length++;
        pos = pos->next;
    }
    return length;
}

// return the pointer of the node at th position, excluding the head
struct list_head *list_head_at(struct list_head *head, int th){
    if(th <= 0 || th > list_head_length(head))
        return NULL;
    
    struct list_head *pos = head;
    for(int i = 0; i < th; i++)
        pos = pos->next;
    return pos;
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

void init_game(piece ***pieces, landbetween ***lands, road ***roads, player ***players, struct list_head **devcards){
    // init item
    *pieces = init_piece();
    *players = init_player();
    *lands = init_landbetween();
    *roads = init_road();   
    *devcards = init_devcard();
}

player **init_player(){
    player **players = (player **)malloc(sizeof(player *) * PLAYER_NUM);
    for(int i = 0; i < PLAYER_NUM; i++){
        players[i] = (player *)malloc(sizeof(player));
        players[i]->id = i + 1;
        players[i]->VP = 0;
        for(int j = 0; j < 5; j++)
            players[i]->resource[j] = 0;
        for(int j = 0; j < 3; j++)
            players[i]->number_of_building[j] = 0;
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
    point desert = {0, 0};
    for(int i = 0; i < Y_LONG; i++){
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == TYPE_PIECE){
                pieces[p] = (piece *)malloc(sizeof(piece));
                pieces[p]->p.x = j;
                pieces[p]->p.y = i;
                while(1){
                    int eco_type = rand() % 6;
                    if(eco_num[eco_type] > 0){
                        if(eco_type == DESERT){
                            pieces[p]->robberFlag = true;
                            pieces[p]->number = 0;
                        }
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

    randomize((void **)pieces, PIECE_NUM, sizeof(piece *));

    for(int i = 0; i < PIECE_NUM; i++){
        if(pieces[i]->eco_type == DESERT){
            desert.x = pieces[i]->p.x;
            desert.y = pieces[i]->p.y;
            pieces[i]->number = 7;
            break;
        }
    }

    const point pos[PIECE_NUM] = {
        {1, 6}, {2, 8}, {3, 10}, {5, 10}, {7, 10}, {8, 8},
        {9, 6}, {8, 4}, {7, 2}, {5, 2}, {3, 2}, {2, 4},
        {3, 6}, {4, 8}, {6, 8}, {7, 6}, {6, 4}, {4, 4}, {5, 6},
    };

    const int val[PIECE_NUM-1] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};

    bool desertFlag = false;
    for(int i = 0; i < PIECE_NUM; i++){
        if(pos[i].x == desert.x && pos[i].y == desert.y){
            desertFlag = true;
            continue;
        }
        for(int j = 0; j < PIECE_NUM; j++){
            if(pieces[j]->p.x == pos[i].x && pieces[j]->p.y == pos[i].y){
                if(desertFlag)
                    pieces[j]->number = val[i-1];
                else
                    pieces[j]->number = val[i];
                pieces[j]->robberFlag = false;
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

int point_type(const int x, const int y){
    for(int i = 0; i < Y_LONG; i++){
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == TYPE_PIECE && x == j && y == i)
                return TYPE_PIECE;
            else if(valid_point_mat[i][j] == TYPE_LANDBETWEEN && x == j && y == i)
                return TYPE_LANDBETWEEN;
            else if(valid_point_mat[i][j] == TYPE_PORT_ANY && x == j && y == i)
                return TYPE_PORT_ANY;
            else if(valid_point_mat[i][j] == TYPE_PORT_BRICK && x == j && y == i)
                return TYPE_PORT_BRICK;
            else if(valid_point_mat[i][j] == TYPE_PORT_LUMBER && x == j && y == i)
                return TYPE_PORT_LUMBER;
            else if(valid_point_mat[i][j] == TYPE_PORT_WOOL && x == j && y == i)
                return TYPE_PORT_WOOL;
            else if(valid_point_mat[i][j] == TYPE_PORT_GRAIN && x == j && y == i)
                return TYPE_PORT_GRAIN;
            else if(valid_point_mat[i][j] == TYPE_PORT_ORE && x == j && y == i)
                return TYPE_PORT_ORE;
        }
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
        roads[i]->owner = NOBODY;
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
        roads[p]->dir = LD;
        roads[p+1]->dir = RD;
        p += 2;
    }

    /*      | | | |        */
    for(int i = 0; i < 4; i++){
        roads[p]->start.x = 2 + i * 2;
        roads[p]->start.y = 1;
        roads[p]->end.x = 2 + i * 2;
        roads[p]->end.y = 2;
        roads[p]->dir = D;
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
        roads[p]->dir = LD;
        roads[p+1]->dir = RD;
        p += 2;
    }

    /*      | | | | |       */
    for(int i = 0; i < 5; i++){
        roads[p]->start.x = 1 + i * 2;
        roads[p]->start.y = 3;
        roads[p]->end.x = 1 + i * 2;
        roads[p]->end.y = 4;
        roads[p]->dir = D;
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
        roads[p]->dir = LD;
        roads[p+1]->dir = RD;
        p += 2;
    }

    /*      | | | | | |     */
    for(int i = 0; i < 6; i++){
        roads[p]->start.x = i * 2;
        roads[p]->start.y = 5;
        roads[p]->end.x = i * 2;
        roads[p]->end.y = 6;
        roads[p]->dir = D;
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
        roads[p]->dir = RD;
        roads[p+1]->dir = LD;
        p += 2;
    }

    /*      | | | | |       */
    for(int i = 0; i < 5; i++){
        roads[p]->start.x = 1 + i * 2;
        roads[p]->start.y = 7;
        roads[p]->end.x = 1 + i * 2;
        roads[p]->end.y = 8;
        roads[p]->dir = D;
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
        roads[p]->dir = RD;
        roads[p+1]->dir = LD;
        p += 2;
    }

    /*      | | | |     */
    for(int i = 0; i < 4; i++){
        roads[p]->start.x = 2 + i * 2;
        roads[p]->start.y = 9;
        roads[p]->end.x = 2 + i * 2;
        roads[p]->end.y = 10;
        roads[p]->dir = D;
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
        roads[p]->dir = RD;
        roads[p+1]->dir = LD;
        p += 2;
    }

    return roads;
}

struct list_head *init_devcard(){
    struct list_head *devcard_list = (struct list_head *)malloc(sizeof(struct list_head));
    devcard_list->next = devcard_list;
    devcard_list->prev = devcard_list;

    for(int i = 0; i < KNIGHT_NUM + MONOPOLY_NUM + FREE_ROAD_BUILDING_NUM + YEAR_OF_PLENTY_NUM + VICTORY_POINT_NUM; i++){
        devcard *card = (devcard *)malloc(sizeof(devcard));
        if(i < KNIGHT_NUM)
            card->type = KNIGHT;
        else if(i < KNIGHT_NUM + MONOPOLY_NUM)
            card->type = MONOPOLY;
        else if(i < KNIGHT_NUM + MONOPOLY_NUM + FREE_ROAD_BUILDING_NUM)
            card->type = FREE_ROAD_BUILDING;
        else if(i < KNIGHT_NUM + MONOPOLY_NUM + FREE_ROAD_BUILDING_NUM + YEAR_OF_PLENTY_NUM)
            card->type = YEAR_OF_PLENTY;
        else
            card->type = VICTORY_POINT;
        card->used = false;
        list_add_tail(&card->node, devcard_list);
    }

    srand(time(NULL));
    for(int i = 0; i < TIMES; i++){
        int th = rand() % list_head_length(devcard_list) + 1;
        struct list_head *pos = list_head_at(devcard_list, th);
        list_move_tail(pos, devcard_list);
    }

    return devcard_list;
}

int roll_dice(){
    srand(time(NULL));
    return rand() % 6 + rand() % 6 + 2;
}

int take_resource(int DP, mapInfo *map, int *resource, int first_id){
    player **players = map->players;
    piece **pieces = map->pieces;
    landbetween **lands = map->lands;
    int turn[4] = {0};
    int playIdx = player_index(first_id, players);

    for(int i = 0; i < 4; i++){
        int idx = (playIdx + i) % 4;
        turn[i] = players[idx]->id;
    }

    // for each player in order
    for(int k = 0; k < PLAYER_NUM; k++){
        // for each piece with same dice point && doesn't have robber
        for(int i = 0; i < PIECE_NUM; i++){
            if(DP == pieces[i]->number && pieces[i]->robberFlag == false){
                const int x = pieces[i]->p.x;
                const int y = pieces[i]->p.y;
                // for each land between around the piece
                POINT_AROUND_PIECE(pos, x, y, 1);
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

bool is_in_three_pieces_lands_pos(const int x, const int y){
    for(int i = 0; i < (int)ARR_NUM(three_pieces_lands_pos, point); i++){
        if(three_pieces_lands_pos[i].x == x && three_pieces_lands_pos[i].y == y)
            return true;
    }
    return false;
}

bool is_land_occupied(mapInfo *map, const int x, const int y, const int id){
    landbetween **lands = map->lands;
    for(int i = 0; i < LAND_NUM; i++){
        if(lands[i]->p.x == x && lands[i]->p.y == y && lands[i]->has_building && lands[i]->owner != id)
            return true;
    }
    return false;
}

bool is_land_connect_other_building(mapInfo *map, const int x, const int y){
    landbetween **lands = map->lands;
    road **roads = map->roads;
    for(int i = 0; i < ROAD_NUM; i++){
        if(x == roads[i]->start.x && y == roads[i]->start.y){
            for(int j = 0; j < LAND_NUM; j++){
                if(lands[j]->p.x == roads[i]->end.x && lands[j]->p.y == roads[i]->end.y && lands[j]->has_building)
                    return true;
            }
        }
        else if(x == roads[i]->end.x && y == roads[i]->end.y){
            for(int j = 0; j < LAND_NUM; j++){
                if(lands[j]->p.x == roads[i]->start.x && lands[j]->p.y == roads[i]->start.y && lands[j]->has_building)
                    return true;
            }
        }
    }
    return false;
}

bool is_robber_on_piece(mapInfo *map, const int x, const int y){
    piece **pieces = map->pieces;
    for(int i = 0; i < PIECE_NUM; i++){
        if(pieces[i]->p.x == x && pieces[i]->p.y == y && pieces[i]->robberFlag == true)
            return true;
    }
    return false;
}

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

void free_devcard(struct list_head *devcards){
    struct list_head *pos = devcards->next;
    while(pos != devcards){
        struct list_head *temp = pos->next;
        free(list_entry(pos, devcard, node));
        pos = temp;
    }
}

void robber_situation(mapInfo *map, int id, SDL_Renderer *renderer){
    player **players = map->players;
    piece **pieces = map->pieces;
    // let all players discard resource
    for(int i = 0; i < PLAYER_NUM; i++)
        discard_resource(players, players[i]->id);
    
    // move the robber
    if(id == 1)
        printf("choose a piece to move the robber\n");

    point p = move_robber(map, id);
    printf("Player %d move the robber to (%d, %d)\n", id, p.x, p.y);
    render_map(renderer, map);

    // let the player who roll the dice to choose a player to steal resource
    // int target_id = steal_resource(id, players);
    // steal resource
    // steal_resource_action(id, target_id, players);
}

int discard_resource(player **players, int player_id){
    player *p = players[player_index(player_id, players)];
    // get the total resource num and decide whether to discard
    int total = 0;
    for(int i = 0; i < 5; i++)
        total += p->resource[i];
    // if the total resource num is less than 7, no need to discard
    if(total <= 7)
        return 0;
    else{
        // get the player's dicision of resource to discard
        int decide[5] = {0};
        // resource_to_discard(p, &decide);
        // discard the resource and add to the bank
        for(int i = 0; i < 5; i++){
            p->resource[i] -= decide[i];
            resource[i] += decide[i];   
        }
    }
}

point move_robber(mapInfo *map, const int id){
    piece **pieces = map->pieces;
    // get the player's dicision of piece to move the robber
    point p;
    if(id == 1){
        int c1 = 0, c2 = 0, c3 = 0;
        while((c1 = scanf("%d %d", &(p.x), &(p.y))) != 2 || (c2 = point_type(p.x, p.y)) != TYPE_PIECE || (c3 = is_robber_on_piece(map, p.x, p.y) == true)){
            if(c1 != 2){
                printf("Please enter two numbers\n");
                while(getchar() != '\n');
            }
            else if(c2 != TYPE_PIECE)
                printf("Please enter a valid piece\n");
            else if(c3 != false)
                printf("Please enter a piece without robber\n");
        }
        printf("1: (%d, %d)\n", p.x, p.y);
    }
    // ai player
    else{
        // random pick : level 1
        int th = rand() % PIECE_NUM;
        p.x = pieces[th]->p.x;
        p.y = pieces[th]->p.y;
        while(is_robber_on_piece(map, p.x, p.y) == true){
            th = rand() % PIECE_NUM;
            p.x = pieces[th]->p.x;
            p.y = pieces[th]->p.y;
        }
        printf("2: (%d, %d)\n", p.x, p.y);
    }

    // move the robber
    for(int i = 0; i < PIECE_NUM; i++){
        if(pieces[i]->robberFlag == true){
            pieces[i]->robberFlag = false;
            break;
        }
    }
    printf("piece_index(p.x, p.y, pieces): %d\n", piece_index(p.x, p.y, pieces));
    pieces[piece_index(p.x, p.y, pieces)]->robberFlag = true;
    return p;
}



bool is_resource_enough( int32_t *standard, int32_t *input )
{
    if( standard[BRICK] >= input[BRICK] && standard[LUMBER] >= input[LUMBER] &&
	standard[WOOL]  >= input[WOOL]  && standard[GRAIN]  >= input[GRAIN]  && standard[ORE] >= input[ORE] )
    {
	return true;
    }

    return false;
}

void trade_action( mapInfo *info, int32_t id )
{
    /* Select trade action: 1. with bank, 2. with player */
    printf("Who do you want to trade with?\n");
    if( id != 1 )	printf("1. Player1\n");
    if( id != 2 )	printf("2. Player2\n");
    if( id != 3 )	printf("3. Player3\n");
    if( id != 4 )	printf("4. Player4\n");
			printf("5. Bank\n");
    int32_t choice = 0;
    scanf("Your choice: %d", &choice );
	if( choice < 1 || choice > 5 )
	{
	    printf("Your choice must be 1 - 5\n");
	    return;
	}

    if( choice == 5 )
    {
	if( id == 1 )	trade_with_bank( info->players[ PLAYER1 ], info->lands );
	if( id == 2 )	trade_with_bank( info->players[ PLAYER2 ], info->lands );
	if( id == 3 )	trade_with_bank( info->players[ PLAYER3 ], info->lands );
	if( id == 4 )	trade_with_bank( info->players[ PLAYER4 ], info->lands );
    }
    else if( choice == 4 )
    {
	if( id == 1 )	trade_with_player( info->players[ PLAYER4 ], info->players[ PLAYER1 ] );
	if( id == 2 )	trade_with_player( info->players[ PLAYER4 ], info->players[ PLAYER2 ] );
	if( id == 3 )	trade_with_player( info->players[ PLAYER4 ], info->players[ PLAYER3 ] );
    }
    else if( choice == 3 )
    {
	if( id == 1 )	trade_with_player( info->players[ PLAYER3 ], info->players[ PLAYER1 ] );
	if( id == 2 )	trade_with_player( info->players[ PLAYER3 ], info->players[ PLAYER2 ] );
	if( id == 4 )	trade_with_player( info->players[ PLAYER3 ], info->players[ PLAYER4 ] );
    }
    else if( choice == 2 )
    {
	if( id == 1 )	trade_with_player( info->players[ PLAYER2 ], info->players[ PLAYER1 ] );
	if( id == 3 )	trade_with_player( info->players[ PLAYER2 ], info->players[ PLAYER3 ] );
	if( id == 4 )	trade_with_player( info->players[ PLAYER2 ], info->players[ PLAYER4 ] );
    }
    else if( choice == 1 )
    {
	if( id == 2 )	trade_with_player( info->players[ PLAYER1 ], info->players[ PLAYER2 ] );
	if( id == 3 )	trade_with_player( info->players[ PLAYER1 ], info->players[ PLAYER3 ] );
	if( id == 4 )	trade_with_player( info->players[ PLAYER1 ], info->players[ PLAYER4 ] );
    }

    return;
}

void trade_with_bank( player *player_A, landbetween **maps )
{
    /* Get input */
    int32_t get_choice = 0;
    printf("What do you want to get ( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE): ");
    scanf("%d", &get_choice );
	if( get_choice < 0 || get_choice > 4 )
	{
	    printf("You can only type 0 - 4!\n");
	    return;
	}

    int32_t discard_choice = 0;
    printf("What do you want to discard ( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE): ");
    scanf("%d", &discard_choice );
	if( discard_choice < 0 || discard_choice > 4 )
	{
	    printf("You can only type 0 - 4!\n");
	    return;
	}
	if( discard_choice == get_choice )
	{
	    printf("CONFLICT: What you want to get is the same as what you want to discard!\n");
	    return;
	}

    /* Trading */
    int32_t credit = trade_with_port( player_A, maps, get_choice );

    int32_t resources_discard[5]  = {0};
    int32_t resources_get[5] = {0};
    resources_discard[ discard_choice ]  = credit;
    resources_get[ get_choice ] = 1;

    if( is_resource_enough( player_A->resource, resources_discard ) && is_resource_enough( resource, resources_get ) )
    {
	player_A->resource[ discard_choice ] -= credit;
	player_A->resource[ get_choice ] += 1;
	resource[ discard_choice ] += credit;
	resource[ get_choice ] -= 1;
	printf("You have traded with bank!\n");
    }
    else if( !is_resource_enough( player_A->resource, resources_discard ) )
    {
	printf("You don't have enough resource!\n");
    }
    else if( !is_resource_enough( resource, resources_get ) )
    {
	printf("The bank doesn't have enough resource!\n");
    }
    
    return;
}

void trade_with_player( player *candidate, player *player_A )
{
    // Resources
    int32_t resource_discard[5]  = {0};
    printf("What do you want to discard ( Format: BRICK LUMBER WOOL GRAIN ORE ): ");
    scanf("%d %d %d %d %d", &resource_discard[0], &resource_discard[1], &resource_discard[2], &resource_discard[3], &resource_discard[4] );

    int32_t resource_get[5]  = {0};
    printf("What do you want to get ( Format: BRICK LUMBER WOOL GRAIN ORE ): ");
    scanf("%d %d %d %d %d", &resource_get[0], &resource_get[1], &resource_get[2], &resource_get[3], &resource_get[4] );

    // candidate decision
    int32_t candidate_decision = 0;
    printf("@Player%d, do you want to trade with player%d ( 1 for Yes, 2 for No ): ", candidate->id, player_A->id );
    scanf("%d", &candidate_decision );
	if( candidate_decision != 1 && candidate_decision != 2 )
	{
	    printf("You can only type 1 or 2!\n");
	    return;
	}

    /* Trading */
    if( candidate_decision == 2 )
    {
	printf("Player%d doesn't want to trade with you...\n", candidate->id );
	return;
    }

    if( is_resource_enough( player_A->resource, resource_discard ) && is_resource_enough( candidate->resource, resource_get ) )
    {
	if( candidate_decision )
	{
	    for( int32_t i = 0; i < 5; i++ )
	    {
		player_A->resource [i]  -= resource_discard[i];
		player_A->resource [i]  += resource_get    [i];
		candidate->resource[i]  -= resource_get    [i];
		candidate->resource[i]  += resource_discard[i];
	    }
	    printf("You have traded with player%d!\n", candidate->id );
	}
	else
	{
	    printf("Sorry! Player%d doesn't want to trade with you!\n", candidate->id );
	}
    }
    else if( !is_resource_enough( player_A->resource, resource_discard ) )
    {
	printf("You don't have enough resource!\n");
    }
    else if( !is_resource_enough( candidate->resource, resource_get ) )
    {
	printf("Player%d does't have enough resource! Sorry!\n", candidate->id );
    }
    
    return;
}

int32_t trade_with_port( player *player_A, landbetween **maps, int32_t get_choice )
{
    int32_t credit = 4;
    for( int32_t i = 0; i < LAND_NUM; i++ )
    {
	if( maps[i]->type == get_choice + 4 && maps[i]->owner == player_A->id )
	{
	    credit = 2;
	    break;
	}
	else if ( maps[i]->type == TYPE_PORT_ANY && maps[i]->owner == player_A->id )
	{
	    credit = 3;
	}
    }

    return credit;
}
