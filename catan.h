#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <getopt.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>
#include "linuxlist.h"
#include "color.h"
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
#define CIRCLE_RAD 15

#define ARR_NUM(arr, type) (sizeof(arr) / sizeof(type))
#define POINT_AROUND_PIECE(name, x, y, d) point name[6] = {{x, y-2*d}, {x-d, y}, {x+d, y}, {x-d, y-d}, {x+d, y-d}, {x, y+d}}
#define EPOINT_AROUND_PIECE(name, x, y, d) point name[6] = {{x, y-2*d}, {x-2*d, y-d}, {x-2*d, y+d}, {x, y+2*d}, {x+2*d, y+d}, {x+2*d, y-d}}
#define PRESS_ENTER printf("Press Enter to continue...\n"); \
                    char c = 0;\
                    scanf("%c", &c);

#define ALPHA 25

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

const char *card_name[] = {
    "knight",
    "monopoly", 
    "free road building", 
    "year of plenty", 
    "victory point" 
};

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
    int32_t used; // -1: cannot use, 0-> not used, 1-> used
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

//option

struct option long_options[] = 
{  
     { "help",  0, NULL, 'h' },    
     { "auto",  0, NULL, 'a' },    
     { "season",  0, NULL, 's' },    
     {  0, 0, 0, 0},  
}; 

void print_help(){
    printf("Options:\n");
    printf("\t-a --auto\tAuto battle.\n");
    printf("\t-s, --season\tOpen the season mod.\n");
    printf("\t-h, --help\tDisplay this description.\n");
    return;
}

int season_flag = 0;
int season_turn = 0;
int pirate = 0;
int diastrophism = 0;

#define SPRING 0
#define SUMMER 1
#define AUTUMN 2
#define WINTER 3

void print_season(){
    printf("\033[1m" "\033[7m");
    if(season_turn == SPRING){
        printf("\033[35m""*\\ Spring Is Coming /*\n"WHITE);
        printf("\033[1;35m""Fields will produce more grain.\n"WHITE);
	if( season_flag == 1 && season_turn != WINTER && pirate == 1 )
	{
	    printf("\033[1;35m""* Pirate appears\n"WHITE);
	}
	if( season_flag == 1 && diastrophism == 1 )
	{
	    printf("\033[1;35m""* Diastrophism appears\n"WHITE);
	}
    }
    else if(season_turn == SUMMER){
        printf("\033[36m""*\\ Summer Is Coming /*\n"WHITE);
        printf("\033[1;36m""Forest will produce more lumber.\n"WHITE);
	if( season_flag == 1 && season_turn != WINTER && pirate == 1 )
	{
	    printf("\033[1;36m""* Pirate appears\n"WHITE);
	}
	if( season_flag == 1 && diastrophism == 1 )
	{
	    printf("\033[1;36m""* Diastrophism appears\n"WHITE);
	}
    }
    else if(season_turn == AUTUMN){
        printf("\033[32m""*\\ Autumn Is Coming /*\n"WHITE);
        printf("\033[1;32m""Year of plenty card will take more resource.\n"WHITE);
	if( season_flag == 1 && season_turn != WINTER && pirate == 1 )
	{
	    printf("\033[1;32m""* Pirate appears\n"WHITE);
	}
	if( season_flag == 1 && diastrophism == 1 )
	{
	    printf("\033[1;32m""* Diastrophism appears\n"WHITE);
	}
    }
    else if(season_turn == WINTER){
        printf("\033[37m""*\\ Winter Is Coming /*\n"WHITE);
        printf("\033[1;37m""Player can take the resource even though the robber is on the piece.\n"WHITE);
	if( season_flag == 1 && season_turn != WINTER && pirate == 1 )
	{
	    printf("\033[1;37m""* Pirate appears\n"WHITE);
	}
	if( season_flag == 1 && diastrophism == 1 )
	{
	    printf("\033[1;37m""* Diastrophism appears\n"WHITE);
	}
    }



    PRINT_WHITE;
    sleep(1);
}

int auto_battle_flag = 0;

// function declaration

// relate SDL
void render_pieces(SDL_Renderer *renderer, mapInfo *map);
void render_lands(SDL_Renderer *renderer, mapInfo *map);
void render_roads(SDL_Renderer *renderer, mapInfo *map);
void render_map(SDL_Renderer *renderer, mapInfo *map);
void render_circle(SDL_Renderer *renderer, int x, int y, int rad, int r, int g, int b, int a);

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
int knight_action(SDL_Renderer *renderer, mapInfo *map, const int id);
point from_screen_to_coor_piece(int x1, int y1);
point from_coor_to_screen_piece(int x1, int y1);
void monopoly_action( mapInfo *info, int id );
//void free_road_building_action();
int32_t year_of_plenty_action( mapInfo *info, int id );
void dev_point_action( mapInfo *info, int id );
void dev_card_action( SDL_Renderer *renderer, mapInfo *info, int id );
void reset_dev_card_status( mapInfo *map, int32_t id );
bool is_in_three_pieces_lands_pos(const int x, const int y);
bool is_land_occupied(mapInfo *map, const int x, const int y, const int id);
bool is_land_connect_other_building(mapInfo *map, const int x, const int y);
bool is_robber_on_piece(mapInfo *map, const int x, const int y);
void free_player(player **players);
void free_piece(piece **pieces);
void free_landbetween(landbetween **lands);
void free_road(road **roads);
void free_devcard(struct list_head *devcards);

int get_road_2p(mapInfo *map, const point p1, const point p2);
int get_land_p(mapInfo *map, const point point);
int get_player_index(mapInfo *map, const int player_id);
void print_test_building(mapInfo *map, const int ab[LAND_NUM]);
void print_test_road(mapInfo *map, const int ab[ROAD_NUM]);
void render_map_build(SDL_Renderer *renderer, mapInfo *map, const int ab[LAND_NUM]);
void render_map_road(SDL_Renderer *renderer, mapInfo *map, const int ab[LAND_NUM], const point p);
int build_road(mapInfo *map, const int player_id, const int index);
int build_building(mapInfo *map, const int player_id, const int index);
point from_screen_to_coor(const int x1, const int y1);
int take_initial_resource(mapInfo *map, const int player_id, const point p);
road *ai_choose_road(mapInfo *map, const int ab[ROAD_NUM], const int player_id);
landbetween *ai_choose_building(mapInfo *map, const int ab[LAND_NUM]);
int start_build(mapInfo *map, const int player_id, SDL_Renderer *renderer);
int free_road_building_action(SDL_Renderer *renderer, mapInfo *map, const int player_id); //return 0 if build success; -1 if condition error; -2 if exit with no buinding; -3 if unknow error
bool is_resource_enough_b(mapInfo *map, const int player_id, const int resource_need[5]);
int build_action(SDL_Renderer *renderer, mapInfo *map, const int player_id);


void render_map_piece_num(SDL_Renderer *renderer, mapInfo *map);
int most_knight_check(SDL_Renderer *renderer, mapInfo *map);
int take_graph_array(mapInfo *map, const int id, int a[ROAD_NUM][ROAD_NUM]);
int count_graph_road(mapInfo *map, const int graph[ROAD_NUM][ROAD_NUM]);
void dfs(mapInfo *map, const int enter, const int graph[ROAD_NUM][ROAD_NUM], int got_road[ROAD_NUM], int got_land[LAND_NUM], const int level, int *max);

void print_player(mapInfo *map);

void print_player(mapInfo *map){


    player **p = map->players;
    for(int i = 0; i < PLAYER_NUM; i++){
	/* VP_print = VP_total - VP_dev_card_point */
	int VP_print = p[i]->VP;
	struct list_head *pos = NULL;
	list_for_each( pos, p[i]->devcard_list )
	{
	    devcard *card = list_entry( pos, devcard, node );
	    if( card->type == VICTORY_POINT && (card->used == -1 || card->used == 0) )	VP_print -= 1;
	}
        printf(YELLOW"\nplayer %d: (VP: %d)\n"WHITE, p[i]->id, VP_print );
        printf("resource: brick: %d, lumber: %d, wool: %d, grain: %d, ore: %d\n", p[i]->resource[0], p[i]->resource[1], p[i]->resource[2], p[i]->resource[3], p[i]->resource[4]);
        printf("number of knights: %d\n", p[i]->number_of_knights);
        printf("length of road: %d\n", p[i]->length_of_road);
        printf("number of building: %d, %d, %d\n", p[i]->number_of_building[0], p[i]->number_of_building[1], p[i]->number_of_building[2]);
        printf("number of dev card: %d\n", p[i]->number_of_dev_card);
        if(p[i]->has_longest_road) printf("has the LONGEST ROAD\n");
        if(p[i]->has_most_knights) printf("has the MOST KINGHT\n");
    }
    printf("\n");
    sleep(2);
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
            if(DP == pieces[i]->number && pieces[i]->robberFlag == true && (season_flag == 1 && season_turn == WINTER))printf("\033[1;37m""Robber can't prevent player taking resource."WHITE);
            if(DP == pieces[i]->number && (pieces[i]->robberFlag == false || (season_flag == 1 && season_turn == WINTER))){
                const int x = pieces[i]->p.x;
                const int y = pieces[i]->p.y;
                // for each land between around the piece
                POINT_AROUND_PIECE(pos, x, y, 1);
                for(int j = 0; j < 6; j++){
                    // if the land between has building && the owner is the player
                    if(lands[land_index(pos[j].x, pos[j].y, lands)]->has_building && lands[land_index(pos[j].x, pos[j].y, lands)]->owner == turn[k]){
                        int point = lands[land_index(pos[j].x, pos[j].y, lands)]->building;
                        if(season_flag && season_turn == SPRING && pieces[i]->eco_type == GRAIN){
                            printf("\033[1;35m""Player %d get more grain because of spring\n"WHITE, players[player_index(turn[k], players)]->id);
                            point ++;
                        }
                        if(season_flag && season_turn == SUMMER && pieces[i]->eco_type == LUMBER){
                            printf("\033[1;36m""Player %d get more lumber because of summer\n"WHITE, players[player_index(turn[k], players)]->id);
                            point ++;
                        }
			if( season_flag && pieces[i]->eco_type == ORE && diastrophism )
			{
                if(season_turn == SPRING)printf("\033[1;35m");
                if(season_turn == SUMMER)printf("\033[1;36m");
                if(season_turn == AUTUMN)printf("\033[1;32m");
                if(season_turn == WINTER)printf("\033[1;37m");

                            printf("Player %d get more ore because of diastrophism\n"WHITE, players[player_index(turn[k], players)]->id);
                            point ++;
			}
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
    printf("Enter robber situation.\n");

    // let all players discard resource
    for(int i = 0; i < PLAYER_NUM; i++)
        discard_resource(players, players[i]->id);
    
    // move the robber
    if(auto_battle_flag == 0 && id == 1) render_map_piece_num(renderer, map);
    point p = move_robber(map, id);
    printf("Player %d move the robber to (%d, %d)\n", id, p.y, p.x);
    render_map(renderer, map);

    // let the player who roll the dice to choose a player to steal resource
    p = from_screen_to_coor_piece(p.x, p.y);

    POINT_AROUND_PIECE(neighbor, p.x, p.y, 1);
    int neighbor_player[5] = {0};
    for(int i = 0; i < 6; i++){
        if(map->lands[get_land_p(map, neighbor[i])]->owner != -1 && map->lands[get_land_p(map, neighbor[i])]->owner != id){
            neighbor_player[map->lands[get_land_p(map, neighbor[i])]->owner] = 1;
            neighbor_player[0] = 1;
        }
    }

    bool cannot_steal = true;
    for(int i = 0; i < PLAYER_NUM; i++){
        if(players[i]->id != id && resource_num(players[i]->id, map) > 0){
            cannot_steal = false;
            break;
        }
    }
    if(cannot_steal){
        printf(RED"Player %d cannot steal resources from other because no has resources\n"WHITE, id);
        return;
    }
    if(neighbor_player[0] == 0){
        if(auto_battle_flag == 0 && id == 1)printf(RED"\nYou can steal from no one.\n\n"WHITE);
        return;
    }
    else{
        int target_id = 0;
        if(auto_battle_flag == 0 && id == 1){
            while(1){
                printf("\tChoose a player to steal resource (enter 0 to give up): ");
                if(scanf("%d", &target_id) != 1){
                    while(getchar() != '\n');
                    continue;
                }
                if(target_id == 0){
                    printf("exit.\n\n");
                    return;
                }
                if(target_id < 1 || target_id > 4){
                    printf(RED"\nInput error.\n\n"WHITE);
                    continue;
                }
                if(resource_num(target_id, map) == 0){
                    printf(RED"\nPlayer %d has no resources, Please enter again\n\n"WHITE, target_id);
                    continue;
                }
                if(neighbor_player[target_id] == 0){
                    if(neighbor_player[0] == 0) printf(RED"\nYou can steal from no one.\n\n"WHITE);
                    else{
                        printf(RED"\nYou can only steal from ");
                        for(int i = 1; i < 5; i++) if(neighbor_player[i] == 1) printf("Player %d ", i);
                        printf("\n\n"WHITE);
                    }
                    continue;
                }
                break;
            }
        }
        else{
            target_id = rand() % 4 + 1;
            while(target_id == id || resource_num(target_id, map) == 0 || neighbor_player[target_id] == 0){
                target_id = rand() % 4 + 1;
                if(random()%10000 < 1) return;
            }
        }

        int resource_type = rand() % 5;
        while(players[player_index(target_id, players)]->resource[resource_type] == 0)
            resource_type = rand() % 5;
        
        players[player_index(id, players)]->resource[resource_type]++;
        players[player_index(target_id, players)]->resource[resource_type]--;

        printf("Player %d steal resource from Player %d\n", id, target_id);
    }
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
        int decide_num = (total + (total%2)) / 2;
        if(auto_battle_flag == 0 && player_id == 1) printf("Enter the resource to throw away: ");
        if(auto_battle_flag == 0 && player_id == 1) printf("\n\tYou have %d brick, %d lumber, %d wool, %d grain, %d ore \n\t( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE)\n", players[player_index(player_id, players)]->resource[0], players[player_index(player_id, players)]->resource[1], players[player_index(player_id, players)]->resource[2], players[player_index(player_id, players)]->resource[3], players[player_index(player_id, players)]->resource[4]);

        for(int i = 0; i < decide_num; i++){
            if(auto_battle_flag == 0 && player_id == 1){
                int decide_type = -1;
                while(1){
                    printf("Resource: ");
                    if(scanf("%d", &decide_type) != 1)continue;
                    if(decide_type > 4 || decide_type < 0) continue;
                    if(players[player_index(player_id, players)]->resource[decide_type] > decide[decide_type]) break;
                    else printf(RED"\nResource is not enough.\n\n"WHITE);
                }
                decide[decide_type] ++;
                printf("The resource you throw away: \n\t%d brick, %d lumber, %d wool, %d grain, %d ore\n", decide[0], decide[1], decide[2], decide[3], decide[4]);
            }
            else{
                int resource_type = rand() % 5;
                for(int j = 0; j < 5; j++){
                    if(players[player_index(player_id, players)]->resource[j]-decide[j] > players[player_index(player_id, players)]->resource[resource_type]-decide[resource_type]) resource_type = j;
                }
                while(players[player_index(player_id, players)]->resource[resource_type] <= decide[resource_type])
                    resource_type = rand() % 5;
                decide[resource_type] ++;
            }
            if(auto_battle_flag == 0 && player_id == 1) printf("\n");
        }

        for(int i = 0; i < 5; i++){
            p->resource[i] -= decide[i];
            resource[i] += decide[i];   
        }
    }
    return 0;
}

void render_map_piece_num(SDL_Renderer *renderer, mapInfo *map){
    render_map(renderer, map);
    for(int i = 0; i < 5; i++){
        int x = 0;
        int y = i*2 + 1;
        y = y + y / 2;
        y *= VIC_LEN; 
        y *= 1.1;

        SDL_Surface *land_surface = NULL;
        if(i == 0)
            land_surface = IMG_Load("picture/row_number/01_row.png");
        else if(i == 1)
            land_surface = IMG_Load("picture/row_number/02_row.png");
        else if(i == 2)
            land_surface = IMG_Load("picture/row_number/03_row.png");
        else if(i == 3)
            land_surface = IMG_Load("picture/row_number/04_row.png");
        else if(i == 4)
            land_surface = IMG_Load("picture/row_number/05_row.png");

        y = y + PIECE_SIZE / 2 - LAND_SIZE / 2;

        SDL_Texture *land_texture = SDL_CreateTextureFromSurface(renderer, land_surface);
        SDL_Rect land_rect = {x, y, LAND_SIZE, LAND_SIZE};
        SDL_RenderCopy(renderer, land_texture, NULL, &land_rect);
        SDL_DestroyTexture(land_texture);
        SDL_FreeSurface(land_surface);
    }   
    SDL_RenderPresent(renderer);
}

point move_robber(mapInfo *map, const int id){
    piece **pieces = map->pieces;
    // get the player's dicision of piece to move the robber
    point p = {0, 0};
    if(auto_battle_flag == 0 && id == 1){
        int c1 = 0, c2 = 0, c3 = 0, x = 0, y = 0;
        printf("Please enter a coordinate to move robber(row colume):\n");
        while((c2 = point_type(p.x, p.y)) != TYPE_PIECE || (c3 = is_robber_on_piece(map, p.x, p.y) == true)){
            printf("\tpiece location: ");
            x = 0;
            y = 0;
            if((c1 = scanf("%d %d", &y, &x)) != 2){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                continue;
            }
            p = from_screen_to_coor_piece(x, y);
            
            if((c2 = point_type(p.x, p.y)) != TYPE_PIECE)
                printf(RED"\tPlease enter a valid piece\n"WHITE);
            else if((c3 = is_robber_on_piece(map, p.x, p.y) == true))
                printf(RED"\tPlease enter a piece without robber\n"WHITE);
            else if(map->pieces[piece_index(p.x, p.y, map->pieces)]->eco_type == DESERT){
                printf(RED"\tPlease enter a piece except for desert\n"WHITE);
                continue;
            }
        }
        //printf("1: (%d, %d)\n", p.x, p.y);
    }
    // ai player
    else{
        // random pick : level 1
        int th = rand() % PIECE_NUM;
        p.x = pieces[th]->p.x;
        p.y = pieces[th]->p.y;
        while(is_robber_on_piece(map, p.x, p.y) == true || map->pieces[piece_index(p.x, p.y, map->pieces)]->eco_type == DESERT){
            th = rand() % PIECE_NUM;
            p.x = pieces[th]->p.x;
            p.y = pieces[th]->p.y;
        }
        // printf("2: (%d, %d)\n", p.x, p.y);
    }

    // move the robber
    for(int i = 0; i < PIECE_NUM; i++){
        if(pieces[i]->robberFlag == true){
            pieces[i]->robberFlag = false;
            break;
        }
    }
    // printf("piece_index(p.x, p.y, pieces): %d\n", piece_index(p.x, p.y, pieces));
    pieces[piece_index(p.x, p.y, pieces)]->robberFlag = true;
    return from_coor_to_screen_piece(p.x, p.y);
}

/*
 * is_resource_enough - to detect is standard is suffucient for input
 * @standard:	resources now someone has
 * @input:	resources now someone wants
 * Note: For each element, standard must be not less than input
 */
bool is_resource_enough( int32_t *standard, int32_t *input )
{
    if( standard[BRICK] >= input[BRICK] && standard[LUMBER] >= input[LUMBER] &&
	standard[WOOL]  >= input[WOOL]  && standard[GRAIN]  >= input[GRAIN]  && standard[ORE] >= input[ORE] )
    {
	return true;
    }

    return false;
}

/*
 * trade_action - selection list for trade action
 * @info:   access of other game information
 * @id:	    player who is trading
 * AI version: testing
 * [ Compile: not yet, Run: Noy yet ]
 */
void trade_action( mapInfo *info, int32_t id )
{
    player *player_A = info->players[ player_index( id, info->players ) ];
    int32_t choice = 0;

    if( auto_battle_flag == 0 && id == 1 ) // Player version
    {
	while( 1 )
	{
	    /* Select trade action */
	    printf("Welcome to trade action, who do you want to trade with?\n");
	    printf("\t1 Player 2\n");
	    printf("\t2 Player 3\n");
	    printf("\t3 Player 4\n");
	    printf("\t4 Bank\n");
        printf("\t5 Exit\n");
	    printf("action:\t");
	
	    if( scanf("%d", &choice ) != 1 )
	    {
		printf(RED"\nPlease enter one integers\n\n"WHITE);
		while(getchar() != '\n');
	    }
	    if( choice < 1 || choice > 5 )
	    {
		printf(RED"\nour choice must be 1 - 5 and cannot be yourself\n\n"WHITE);
		continue;
	    }
	    else    break;
	}
    }
    else // AI version
    {
	int flag = -1;
	int max = 0;
	for( int i = 0; i < 5; i++ ) // check if lack of any resource
	{
	    if( player_A->resource[i] == 0 )
	    {
		flag = i;
	    }
	    else if( player_A->resource[i] > max )
	    {
		max = player_A->resource[i];
	    }
	}

	if( flag == -1 )    choice = 5;
	else
	{
	    choice = 5;
	    for( int i = 0; i < 4; i++ )
	    {
		if( info->players[i]->id == player_A->id )	continue;
		else
		{
		    if( info->players[i]->resource[flag] != 0 )
		    {
			choice = info->players[i]->id - 1;
			break;
		    }
		}
	    }
	    if( choice == 5 )
	    {
		if( resource[flag] != 0 && max >= 4 )   choice = 4;
	    }
	}
    }
    
    if( choice == 5 )
    {
	if( auto_battle_flag == 0 && player_A->id == 1 )	    printf("Exit trading\n\n");
	return;
    }
    else if( choice == 4 )
    {
	trade_with_bank( player_A, info->lands );
    }
    else
    {
	trade_with_player( info->players[ player_index( choice+1, info->players ) ], player_A );
    }

    return;
}

/*
 * trade_with_bank - simply trade action with bank
 * @player_A:	player who is trading
 * @maps:	for trade_with_port() needed
 * AI version: testing
 * [ Compile: not yet, Run: Not yet ]
 */
void trade_with_bank( player *player_A, landbetween **maps )
{
    /* Get input */
    int32_t get_choice = 0;
    int32_t discard_choice = 0;

    if( auto_battle_flag == 0 && player_A->id == 1 )
    {
	printf("What do you want to get ( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE): ");
	if( scanf("%d", &get_choice ) != 1 )
	{
	    printf(RED"\nPlease enter one integers\n\n"WHITE);
	    while(getchar() != '\n');
	}
	    if( get_choice < 0 || get_choice > 4 )
	    {
		printf(RED"\nYou can only type 0 - 4\n\n"WHITE);
		return;
	    }

	printf("What do you want to discard ( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE): ");
	if( scanf("%d", &discard_choice ) != 1 )
	{
	    printf(RED"\nPlease enter one integers\n\n"WHITE);
	    while(getchar() != '\n');
	}
	    if( discard_choice < 0 || discard_choice > 4 )
	    {
		printf(RED"\nYou can only type 0 - 4\n\n"WHITE);
		return;
	    }
	    if( discard_choice == get_choice )
	    {
		printf(RED"\nCONFLICT: What you want to get is the same as what you want to discard!\n\n"WHITE);
		return;
	    }
    }
    else
    {
	int max = 0;
	for( int i = 0; i < 5; i++ )
	{
	    if( player_A->resource[i] == 0  )	get_choice = i;
	    else if( player_A->resource[i] > max )	{   max = player_A->resource[i];	    discard_choice = i;	}
	}
    }

    /* Trading */
    int32_t credit = trade_with_port( player_A, maps, get_choice );

    int32_t resources_discard[5]  = {0};
    int32_t resources_get[5] = {0};
    resources_discard[ discard_choice ] = credit;
    resources_get[ get_choice ] = 1;

    if( is_resource_enough( player_A->resource, resources_discard ) && is_resource_enough( resource, resources_get ) )
    {
	player_A->resource[ discard_choice ] -= credit;
	player_A->resource[ get_choice ] += 1;
	resource[ discard_choice ] += credit;
	resource[ get_choice ] -= 1;
	printf("Player %d has traded with bank!\n", player_A->id );
    }
    else if( !is_resource_enough( player_A->resource, resources_discard ) )
    {
	if(auto_battle_flag == 0 && player_A->id == 1) printf(RED"\nYou don't have enough resource!\n\n"WHITE);
    }
    else if( !is_resource_enough( resource, resources_get ) )
    {
	if(auto_battle_flag == 0 && player_A->id == 1) printf(RED"\nThe bank doesn't have enough resource!\n\n"WHITE);
    }
    
    return;
}

/*
 * trade_with_player - trade action from player_A to candidate
 * @candidate:	player who plaayer_A wants to trade with
 * @player_A:	player who is trading
 * AI version: testing
 * [ Compile: not yet, Run: not yet ]
 */
void trade_with_player( player *candidate, player *player_A )
{
    // Resources
    int32_t resource_discard[5]  = {0};
    int32_t resource_get[5]  = {0};
    int get_choice = 0;
    int discard_choice = 0;
    
    if( auto_battle_flag == 0 && player_A->id == 1 )
    {
	printf("Please type number of resources you want to discard ( Format: BRICK LUMBER WOOL GRAIN ORE ): ");
	if( scanf("%d %d %d %d %d", &resource_discard[0], &resource_discard[1], &resource_discard[2], &resource_discard[3], &resource_discard[4] ) != 5 )
	{
	    printf(RED"\nPlease enter five integers\n\n"WHITE);
	    while(getchar() != '\n');
	}

	printf("What do you want to get ( Format: BRICK LUMBER WOOL GRAIN ORE ): ");
	if( scanf("%d %d %d %d %d", &resource_get[0], &resource_get[1], &resource_get[2], &resource_get[3], &resource_get[4] ) != 5 )
	{
	    printf(RED"\nPlease enter five integers\n\n"WHITE);
	    while(getchar() != '\n');
	}
    }
    else
    {
	int max = 0;
	for( int i = 0; i < 5; i++ )
	{
	    if( player_A->resource[i] == 0  )	get_choice = i;
	    if( player_A->resource[i] > max )	{   max = player_A->resource[i];	    discard_choice = i;	}
	}
	resource_discard[ discard_choice ] = 1;
	resource_get[ get_choice ] = 1;
    }

    // candidate decision
    int32_t candidate_decision = 1;
    
    if( auto_battle_flag == 0 && candidate->id == 1 )
    {
	printf(GREEN"@Player1, do you want to trade with player %d with giving one ", player_A->id );

	switch( get_choice )
	{
	    case BRICK:
		printf("brick");
		break;
	    case LUMBER:
		printf("lumber");
		break;
	    case WOOL:
		printf("wool");
		break;
	    case GRAIN:
		printf("grain");
		break;
	    case ORE:
		printf("ore");
		break;
	}

	printf(" and getting one " );

	switch( discard_choice )
	{
	    case BRICK:
		printf("brick");
		break;
	    case LUMBER:
		printf("lumber");
		break;
	    case WOOL:
		printf("wool");
		break;
	    case GRAIN:
		printf("grain");
		break;
	    case ORE:
		printf("ore");
		break;
	}

	printf( " ( 1 for Yes, 2 for No ): "WHITE );
	if( scanf("%d", &candidate_decision ) != 1 )
	{
	    printf(RED"\nPlease enter one integers\n\n"WHITE);
	    while(getchar() != '\n');
	}
	if( candidate_decision != 1 && candidate_decision != 2 )
	{
	    printf(RED"\nYou can only type 1 or 2!\n\n"WHITE);
	    return;
	}
    }
    else
    {
	int sum = 0;
	for( int i = 0; i < 5; i++ )	sum += player_A->resource[i];
	if( !is_resource_enough( candidate->resource, resource_get ) || sum > 7 )
	{
	    candidate_decision = 2;
	}
	else
	{
	    candidate_decision = 1;
	}
    }

    /* Trading */
    if( candidate_decision == 2 )
    {
	printf("Player %d rejects to trade with Player %d!\n", candidate->id, player_A->id );
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
	    printf("Player %d has traded with player %d\n", player_A->id, candidate->id );
	}
	else
	{
	    printf("Player %d rejects to trade with Player %d!\n", candidate->id, player_A->id );
	}
    }
    else if( !is_resource_enough( player_A->resource, resource_discard ) )
    {
		if(auto_battle_flag == 0 && player_A->id == 1) printf(RED"\nYou don't have enough resource!\n\n"WHITE);
    }
    else if( !is_resource_enough( candidate->resource, resource_get ) )
    {
		if(auto_battle_flag == 0 && player_A->id == 1) printf(RED"\nPlayer %d does't have enough resource!\n\n"WHITE, candidate->id );
    }
    
    return;
}

/*
 * trade_with_port - to detect if player_A can trade with the bank with a cheaper credit
 * @player_A:	player who trade with the bank
 * @maps:	Access the port information
 * @get_choice:	resource that player_A wants to get
 * AI version: not related
 * Note: this function is embeded in trade_with_bank()
 */
int32_t trade_with_port( player *player_A, landbetween **maps, int32_t get_choice )
{
    int32_t credit = 4;

    if( season_flag == 1 && pirate == 1 && season_turn != WINTER )
    {
	return 4;
    }

    for( int32_t i = 0; i < LAND_NUM; i++ )
    {
	if( maps[i]->type == get_choice + 4 && maps[i]->owner == player_A->id )
	{
	    printf("You can trade with port in credit of 2\n");
	    credit = 2;
	    break;
	}
	else if ( maps[i]->type == TYPE_PORT_ANY && maps[i]->owner == player_A->id )
	{
	    printf("You can trade with port in credit of 3\n");
	    credit = 3;
	}
    }

    return credit;
}

int knight_action(SDL_Renderer *renderer, mapInfo *map, const int id){
    render_map(renderer, map);
    player **players = map->players;
    printf("Player %d use the knight card\n", id);
    
    // move the robber
    if(auto_battle_flag == 0 && id == 1) render_map_piece_num(renderer, map);
    point p = move_robber(map, id);
    printf("Player %d move the robber to (%d, %d)\n", id, p.y, p.x);
    render_map(renderer, map);

    // let the player who roll the dice to choose a player to steal resource
    p = from_screen_to_coor_piece(p.x, p.y);

    map->players[get_player_index(map, id)]->number_of_dev_card -= 1;
    struct list_head *pos = NULL;
    list_for_each( pos,  map->players[ player_index( id, map->players ) ]->devcard_list)
    {
	devcard *card = list_entry( pos, devcard, node );
	if( card->type == KNIGHT && card->used == 0 )
	{
	    card->used = 1;
	    break;
	}
    }

    most_knight_check(renderer, map);
    render_map(renderer, map);

    POINT_AROUND_PIECE(neighbor, p.x, p.y, 1);
    int neighbor_player[5] = {0};
    for(int i = 0; i < 6; i++){
        if(map->lands[get_land_p(map, neighbor[i])]->owner != -1 && map->lands[get_land_p(map, neighbor[i])]->owner != id){
            neighbor_player[map->lands[get_land_p(map, neighbor[i])]->owner] = 1;
            neighbor_player[0] = 1;
        }
    }

    bool cannot_steal = true;
    for(int i = 0; i < PLAYER_NUM; i++){
        if(players[i]->id != id && resource_num(players[i]->id, map) > 0){
            cannot_steal = false;
            break;
        }
    }
    if(cannot_steal){
        printf(RED"Player %d cannot steal resources from other because no has resources\n"WHITE, id);
        return 0;
    }
    if(neighbor_player[0] == 0){
        if(auto_battle_flag == 0 && id == 1)printf(RED"\nYou can steal from no one.\n\n"WHITE);
        return 0;
    }
    else{
        int target_id = 0;
        if(auto_battle_flag == 0 && id == 1){
            while(1){
                printf("\tChoose a player to steal resource(enter 0 to give up): ");
                if(scanf("%d", &target_id) != 1){
                    while(getchar() != '\n');
                    continue;
                }
                if(target_id == 0){
                    printf("exit.\n\n");
                    return 0;
                }
                if(target_id < 1 || target_id > 4){
                    printf(RED"\nInput error.\n\n"WHITE);
                    continue;
                }
                if(resource_num(target_id, map) == 0){
                    printf(RED"\nPlayer %d has no resources, Please enter again\n\n"WHITE, target_id);
                    continue;
                }
                if(neighbor_player[target_id] == 0){
                    printf(RED"\nYou can only steal from ");
                    for(int i = 1; i < 5; i++) if(neighbor_player[i] == 1) printf("Player %d ", i);
                    printf("\n\n"WHITE);
                    continue;
                }
                break;
            }
        }
        else{
            target_id = rand() % 4 + 1;
            while(target_id == id || resource_num(target_id, map) == 0 || neighbor_player[target_id] == 0){
                target_id = rand() % 4 + 1;
                if(random()%10000 < 1) return 0;
            }
        }

        int resource_type = rand() % 5;
        while(players[player_index(target_id, players)]->resource[resource_type] == 0)
            resource_type = rand() % 5;
        
        players[player_index(id, players)]->resource[resource_type]++;
        players[player_index(target_id, players)]->resource[resource_type]--;

        printf("Player %d steal resource from Player %d\n", id, target_id);
    }
    players[player_index(id, players)]->number_of_knights ++;
    return 0;
}

int most_knight_check(SDL_Renderer *renderer, mapInfo *map){
    render_map(renderer, map);
    int index = 5;
    for(int i = 0; i < PLAYER_NUM; i++){
        if(map->players[i]->has_most_knights) index = i;
    }
    if(index == 5){
        for(int i = 0; i < PLAYER_NUM; i++){
            if(map->players[i]->number_of_knights >= 3) index = i;
        }
        if(index == 5) return -1;
    }
    for(int i = 0; i < PLAYER_NUM; i++){
        if(map->players[i]->number_of_knights > map->players[index]->number_of_knights) index = i;
    }
    for(int i = 0; i < PLAYER_NUM; i++){
        if(i == index){
            if(map->players[i]->has_most_knights != 1) map->players[i]->VP += 2;
            map->players[i]->has_most_knights = 1;
        }
        else{
            if(map->players[i]->has_most_knights == 1) map->players[i]->VP -= 2;
            map->players[i]->has_most_knights = 0;
        }
    }
    
    render_map(renderer, map);
    return map->players[index]->id;
}

int longest_road_check(SDL_Renderer *renderer, mapInfo *map){
    render_map(renderer, map);
    for(int i = 0; i < PLAYER_NUM; i++){
        int a[ROAD_NUM][ROAD_NUM] = {0};
        take_graph_array(map, map->players[i]->id, a);
        map->players[i]->length_of_road = count_graph_road(map, a);
    }

    int index = 5;
    for(int i = 0; i < PLAYER_NUM; i++){
        if(map->players[i]->has_longest_road) index = i;
    }
    if(index == 5){
        for(int i = 0; i < PLAYER_NUM; i++){
            if(map->players[i]->length_of_road >= 5) index = i;
        }
        if(index == 5) return -1;
    }
    for(int i = 0; i < PLAYER_NUM; i++){
        if(map->players[i]->length_of_road > map->players[index]->length_of_road) index = i;
    }
    for(int i = 0; i < PLAYER_NUM; i++){
        if(i == index){
            if(map->players[i]->has_longest_road != 1) map->players[i]->VP += 2;
            map->players[i]->has_longest_road = 1;
        }
        else{
            if(map->players[i]->has_longest_road == 1) map->players[i]->VP -= 2;
            map->players[i]->has_longest_road = 0;
        }
    }
    render_map(renderer, map);
    return map->players[index]->id;
}

int take_graph_array(mapInfo *map, const int id, int a[ROAD_NUM][ROAD_NUM]){
    for(int i = 0; i < ROAD_NUM; i++){
        if(map->roads[i]->owner != id) continue;
        for(int j = 0; j < ROAD_NUM; j++){
            if((map->roads[j]->start.x == map->roads[i]->end.x && map->roads[j]->start.y == map->roads[i]->end.y) || (map->roads[j]->end.x == map->roads[i]->end.x && map->roads[j]->end.y == map->roads[i]->end.y)){
                if(map->roads[j]->owner == id && (map->lands[get_land_p(map, map->roads[i]->end)]->owner == -1 || map->lands[get_land_p(map, map->roads[i]->end)]->owner == id)){
                    a[i][j] = 1;
                }
            }
            if((map->roads[j]->end.x == map->roads[i]->start.x && map->roads[j]->end.y == map->roads[i]->start.y) || (map->roads[j]->start.x == map->roads[i]->start.x && map->roads[j]->start.y == map->roads[i]->start.y)){
                if(map->roads[j]->owner == id && (map->lands[get_land_p(map, map->roads[i]->start)]->owner == -1 || map->lands[get_land_p(map, map->roads[i]->start)]->owner == id)){
                    a[i][j] = 1;
                }
            }
        }
    }
    return 0;
}

int count_graph_road(mapInfo *map, const int graph[ROAD_NUM][ROAD_NUM]){
    int count = 0;
    for(int i = 0; i < ROAD_NUM; i++){
        int flag = 0;
        for(int j = 0; j < ROAD_NUM; j++) flag += graph[i][j];
        if(flag == 0) continue;

        int max = 0;
        int got_road[ROAD_NUM] = {0};
        int got_land[LAND_NUM] = {0};
        got_road[i] = 1;
        dfs(map, i, graph, got_road, got_land, 1, &max);

        if(max > count) count = max;
    }
    return count;
}

void dfs(mapInfo *map, const int enter, const int graph[ROAD_NUM][ROAD_NUM], int got_road[ROAD_NUM], int got_land[LAND_NUM], const int level, int *max){
    if(*max < level) *max = level;
    for(int i = 0; i < ROAD_NUM; i++){
        if(got_road[i] == 1) continue;
        else if(graph[enter][i] == 0) continue;
        else{
            int flag = 0;
            for(int j = 0; j < LAND_NUM; j++){
                if(got_land[j] == 0) continue;
                if((map->roads[i]->start.x == map->lands[j]->p.x && map->roads[i]->start.y == map->lands[j]->p.y) || (map->roads[i]->end.x == map->lands[j]->p.x && map->roads[i]->end.y == map->lands[j]->p.y)){
                    if(flag == 0) flag = 1;
                    else flag = 0;
                }
            }
            if(flag == 1) continue;

            int tmp_road[ROAD_NUM] = {0};
            int tmp_land[LAND_NUM] = {0};
            for(int j = 0; j < ROAD_NUM; j++) tmp_road[j] = got_road[j];
            for(int j = 0; j < LAND_NUM; j++) tmp_land[j] = got_land[j];

            tmp_road[i] = 1;
            if((map->roads[enter]->start.x == map->roads[i]->start.x && map->roads[enter]->start.y == map->roads[i]->start.y) || (map->roads[enter]->start.x == map->roads[i]->end.x && map->roads[enter]->start.y == map->roads[i]->end.y)){
                tmp_land[get_land_p(map, map->roads[enter]->start)] = 1;
            }
            if((map->roads[enter]->end.x == map->roads[i]->start.x && map->roads[enter]->end.y == map->roads[i]->start.y) || (map->roads[enter]->end.x == map->roads[i]->end.x && map->roads[enter]->end.y == map->roads[i]->end.y)){
                tmp_land[get_land_p(map, map->roads[enter]->end)] = 1;
            }

            dfs(map, i, graph, tmp_road, tmp_land, level + 1, max);
        }
    }
}

/*
 * monopoly_action - Take one certain resource from all the other players
 * @players:	all players
 * @id:		player who use monopoly_action
 * AI version: done
 * [ Compile: pass, Run: pass ]
 */
void monopoly_action( mapInfo *info, int id )
{
    int32_t get_choice = 30;
    if( auto_battle_flag == 0 && id == 1 ) // Player version
    {
	printf("Which resource do you want to get ( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE): ");
	if( scanf("%d", &get_choice ) != 1 )
	{
	    printf(RED"\nPlease enter one integers\n\n"WHITE);
	    while(getchar() != '\n');
	}

	    if( get_choice < 0 || get_choice > 4 )
	    {
		printf(RED"\nYou can only type 0 - 4!\n\n"WHITE);
		return;
	    }
    }
    else // AI version: pick the resource with most number, mean AI
    {
	int max_resource = 0;
	for( int32_t i = 0; i < 5; i++ )
	{
	    if( info->players[ player_index( id, info->players ) ]->resource[i] > max_resource )	    get_choice = i;
	}
    }

    player *monoply = info->players[ player_index( id, info->players ) ];
    for( int32_t i = 0; i < PLAYER_NUM; i++ )
    {
	if( info->players[i]->id == id )   continue;

	monoply->resource[ get_choice ] += info->players[i]->resource[ get_choice ];
	info->players[i]->resource[ get_choice ] = 0;
    }

    /* Action message */
    printf("Player %d has used monopoly card and took away all ", monoply->id );
    switch( get_choice )
    {
	case BRICK:
	    printf("BRICK");
	    break;
	case LUMBER:
	    printf("LUMBER");
	    break;
	case WOOL:
	    printf("WOOL");
	    break;
	case GRAIN:
	    printf("GRAIN");
	    break;
	case ORE:
	    printf("ORE");
	    break;
    }
    printf(" from others' hand!\n");

    /* Devcard modification: used status = 1 */
    monoply->number_of_dev_card -= 1;
    struct list_head *pos = NULL;
    list_for_each( pos, monoply->devcard_list )
    {
	devcard *card = list_entry( pos, devcard, node );
	if( card->type == MONOPOLY && card->used == 0 )
	{
	    card->used = 1;
	    break;
	}
    }

    return;
}

/*
 * year_of_plenty_action - get 2 resource from the bank
 * @players:	all players
 * @id:		player who use the year_of_plenty_action card
 * AI version: done
 * Warning: Where does the used devCard go -> free
 * [ Compile: pass, Run: pass ]
 * */
int32_t year_of_plenty_action( mapInfo *info, int id )
{
    int32_t get_choice1 = 0;
    int32_t get_choice2 = 0;
    int32_t get_choice3 = 0;
    int32_t get[5] = {0};
    if( auto_battle_flag == 0 && id == 1 ) // Player version
    {
	while( 1 )
	{
	    if( !( season_flag == 1 && season_turn == AUTUMN ) )
	    {
		printf("What 2 resources do you want to get ( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE): ");
		if( scanf("%d %d", &get_choice1, &get_choice2 ) != 2 )
		{
		    printf(RED"\nPlease enter two integers\n\n"WHITE);
		    while(getchar() != '\n');
		    continue;
		}
		else if( get_choice1 < 0 || get_choice1 > 4 || get_choice2 < 0 || get_choice2 > 4 )
		{
		    printf(RED"\nYou can only type 0 - 4!\n\n"WHITE);
		    continue;
		}

		get[ get_choice1 ] += 1;
		get[ get_choice2 ] += 1;

		if( !is_resource_enough( resource, get ) )
		{
		    printf(RED"\nThe bank has not enough resources\n\n"WHITE);
		    continue;
		}
		else
		{
		    break;
		}
	    }
	    else
	    {
		printf("What 3 resources do you want to get ( 0: BRICK, 1: LUMBER, 2: WOOL, 3: GRAIN, 4: ORE): ");
		if( scanf("%d %d %d", &get_choice1, &get_choice2, &get_choice3 ) != 3 )
		{
		    printf(RED"\nPlease enter three integers\n\n"WHITE);
		    while(getchar() != '\n');
		    continue;
		}
		else if( get_choice1 < 0 || get_choice1 > 4 || get_choice2 < 0 || get_choice2 > 4 || get_choice3 < 0 || get_choice3 > 4 )
		{
		    printf(RED"\nYou can only type 0 - 4!\n\n"WHITE);
		    continue;
		}

		get[ get_choice1 ] += 1;
		get[ get_choice2 ] += 1;
		get[ get_choice3 ] += 1;

		if( !is_resource_enough( resource, get ) )
		{
		    printf(RED"\nThe bank has not enough resources\n\n"WHITE);
		    continue;
		}
		else
		{
		    break;
		}
	    }
	}
    }
    else // AI version: pick 2 least resources with least number
    {
	if( !( season_flag == 1 && season_turn == AUTUMN ) )
	{
	    int32_t min1 = 30;
	    int32_t min2 = 30;

	    player *player_A = info->players[ player_index( id, info->players ) ];
	    for( int32_t i = 0; i < 5; i++ )
	    {
		if( player_A->resource[i] < min1 )
		{
		    min2 = min1;
		    get_choice2 = get_choice1;
		    min1 = player_A->resource[i];
		    get_choice1 = i;
		}
		else if( player_A->resource[i] >= min1 && player_A->resource[i] < min2 )
		{
		    min2 = player_A->resource[i];
		    get_choice2 = i;
		}
	    }

	    get[ get_choice1 ] += 1;
	    get[ get_choice2 ] += 1;
	}
	else
	{
	    int32_t min1 = 30;
	    int32_t min2 = 30;
	    int32_t min3 = 30;

	    player *player_A = info->players[ player_index( id, info->players ) ];
	    for( int32_t i = 0; i < 5; i++ )
	    {
		if( player_A->resource[i] < min1 )
		{
		    min3 = min2;
		    get_choice3 = get_choice2;
		    min2 = min1;
		    get_choice2 = get_choice1;
		    min1 = player_A->resource[i];
		    get_choice1 = i;
		}
		else if( player_A->resource[i] >= min1 && player_A->resource[i] < min2 )
		{
		    min3 = min2;
		    get_choice3 = get_choice2;
		    min2 = player_A->resource[i];
		    get_choice2 = i;
		}
		else if( player_A->resource[i] >= min2 && player_A->resource[i] < min3 )
		{
		    min3 = player_A->resource[i];
		    get_choice3 = i;
		}
	    }

	    get[ get_choice1 ] += 1;
	    get[ get_choice2 ] += 1;
	    get[ get_choice3 ] += 1;
	}
    }

    resource[ get_choice1 ] -= 1;
    resource[ get_choice2 ] -= 1;
    if( season_flag == 1 && season_turn == 2 )	resource[ get_choice3 ] -= 1;
    info->players[ player_index( id, info->players ) ]->resource[ get_choice1 ] += 1;
    info->players[ player_index( id, info->players ) ]->resource[ get_choice2 ] += 1;
    if( season_flag == 1 && season_turn == 2 )	info->players[ player_index( id, info->players ) ]->resource[ get_choice3 ] += 1;

    if( season_flag == 1 && season_turn == 2 )
    {
	printf("\033[1;32m""Player %d has used year_of_plenty card and freely get 3 resource from bank\n"WHITE, info->players[ player_index( id, info->players ) ]->id );
    }
    else
    {
    printf("Player %d has used year_of_plenty card and freely get 2 resource from bank\n", info->players[ player_index( id, info->players ) ]->id );
    }


    /* Devcard modification: used status = 1 */
    info->players[ player_index( id, info->players ) ]->number_of_dev_card -= 1;
    struct list_head *pos = NULL;
    list_for_each( pos, info->players[ player_index( id, info->players ) ]->devcard_list )
    {
	devcard *card = list_entry( pos, devcard, node );
	if( card->type == YEAR_OF_PLENTY && card->used == 0 )
	{
	    card->used = 1;
	    break;
	}
    }

    return 0;
}

/*
 * dev_point_action - using point card, VP += 1
 * @info: to get information of players
 * @id  : one who use point card
 * AI version: not related
 * [ Compile: pass, Run: pass ]
 */
void dev_point_action( mapInfo *info, int id )
{
    player *player_A = info->players[ player_index( id, info->players ) ];

    /* Modify used status to 1 */
    player_A->number_of_dev_card -= 1;
    struct list_head *pos = NULL;
    list_for_each( pos, player_A->devcard_list )
    {
	devcard *card = list_entry( pos, devcard, node );
	if( card->type == VICTORY_POINT && card->used == 0 )
	{
	    card->used = 1;
	    break;
	}
    }

    /* Action message */
    printf("Player %d has used point card\n", player_A->id );

    return;
}

int victory_check(mapInfo *map){
    for(int i = 0; i < PLAYER_NUM; i++){
        if(map->players[i]->VP >= 10){
            int count = 0;
            struct list_head *pos = NULL;
            list_for_each( pos, map->players[i]->devcard_list )
            {
                devcard *card = list_entry( pos, devcard, node );
                if( card->type == VICTORY_POINT)	count += 1;
            }
            printf("Player %d get 10 point: \n%d village, %d city, %d point card", map->players[i]->id, map->players[i]->number_of_building[1], map->players[i]->number_of_building[2], count);
            if(map->players[i]->has_longest_road) printf(", has the LONGEST ROAD");
            if(map->players[i]->has_most_knights) printf(", has the MOST KINGHT");
            printf(".\n");
            printf("\033[1m"YELLOW"Player %d win!\n\n""\033[0m", map->players[i]->id);
            return map->players[i]->id;
        }
    }
    return 5;
}

/*
 * dev_card_action - total actions when using dev_cards stage
 * @info: total information of the game, mapinfo
 * @id  : player who wants to use devcards
 * Warning:
 * 1. free_road_building needs to be modified
 * 2. knight_action needs to be modified
 *  AI version: not yet
 * [ Compile: not yet, Run: not yet ]
 */
void dev_card_action( SDL_Renderer *renderer, mapInfo *info, int id )
{
    player *player_A = info->players[ player_index( id, info->players ) ];

    int32_t dev_choice = 0;
    if( auto_battle_flag == 0 && id == 1 ) // Player version
    {
        printf("Welcome to developement card action, now you have %d card(s): \n", player_A->number_of_dev_card);
        struct list_head *pos = NULL;
	    list_for_each( pos, player_A->devcard_list )
	    {
		devcard *card = list_entry( pos, devcard, node );
		if( card->used == 1 ) continue;
        else{
            printf("%s card-", card_name[card->type]);
            if( card->used == -1 ){
                printf("unusable\n");
            }
            else{
                printf("usable\n");
            }
        }
	    }

	   printf("\nWhich card do you want to use?\n");
	   printf("\t1 Knight action\n");
	   printf("\t2 Monopoly action\n");
	   printf("\t3 Free road building action\n");
	   printf("\t4 Year of plenty action\n");
	   printf("\t5 Point action\n");
	   printf("\t6 Exit\n");
	   printf("action:\t");
	   while( 1 )
	   {
		if( scanf("%d", &dev_choice ) != 1 )
		{
		   printf(RED"\nPlease enter one character\n\n"WHITE);
		   while(getchar() != '\n');
		   printf("Your choice ( 1 - 6 ): ");
		   continue;
		}
		else if( dev_choice > 6 || dev_choice < 1 )
		{
		   printf(RED"\nPlease enter an integer between 1 and 6\n\n"WHITE);
		   while(getchar() != '\n');
		   printf("Your choice ( 1 - 6 ): ");
		   continue;
		}
		else break;
	   }
    }
    else // AI version
    {
	dev_choice = 6;
	if( !list_empty( player_A->devcard_list ) )
	{
	    struct list_head *pos = NULL;
	    list_for_each( pos, player_A->devcard_list )
	    {
		int flag = 0;
		for( int i = 0; i < 5; i++ )
		{
		    if( resource[i] >= 1 )  flag += 1;
		}

		devcard *card = list_entry( pos, devcard, node );
		if( card->used == 0 )
		{ 
		    if( card->type == YEAR_OF_PLENTY && flag < 3 )  continue;
		    dev_choice = card->type + 1;
		}
		else			    continue;
	    }
	}
	else
	{
	    dev_choice = 6;
	}
    }

    /* Quit */
    if( dev_choice == 6 ) {
        if( auto_battle_flag == 0 && id == 1 ) printf("exit\n\n");
        return;
    }

    /* Check is can be used or not */
    int32_t flag = 0;
    struct list_head *pos = NULL;
    list_for_each( pos, player_A->devcard_list )
    {
	devcard *card = list_entry( pos, devcard, node );
	if( card->type == dev_choice - 1 && card->used == 0 ) {   flag = 1; break; }
	else continue;
    }

    if( flag == 0 )
    {
	printf(RED"\nThis card cannot be used\n\n"WHITE);
	return;
    }

    /* Use devcard */
    switch( dev_choice - 1 )
    {
	case KNIGHT:
	   knight_action( renderer, info, id );
	   break;
	case MONOPOLY:
	   monopoly_action( info, id );
	   break;
	case FREE_ROAD_BUILDING:
	   free_road_building_action( renderer, info, id );
	   break;
	case YEAR_OF_PLENTY:
	   year_of_plenty_action( info, id );
	   break;
	case VICTORY_POINT:
	   dev_point_action( info, id );
	   break;
	default:
	   printf(RED"\nFAIL\n\n"WHITE);
	   return;
    }

    return;
}


void reset_dev_card_status( mapInfo *map, int32_t id ) // set dev_card->used = 0
{
    player *player_A = map->players[ player_index( id, map->players ) ];

    struct list_head *pos = NULL;
    list_for_each( pos, player_A->devcard_list )
    {
	devcard *card = list_entry( pos, devcard, node );
	if( card->used == -1 )	card->used = 0;
    }

    return;
}
