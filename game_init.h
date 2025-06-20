#pragma once
#include "catan.h"
#include "utils.h"

void randomize(void **array, size_t n, size_t size);
void init_game(piece ***pieces, landbetween ***lands, road ***roads, player ***players, struct list_head **devcards);
player **init_player();
piece **init_piece();
int piece_index(int x, int y, piece **pieces);
int land_index(const int x, const int y, landbetween **lands);
int player_index(const int id, player **players);
int point_type(const int x, const int y);
int resource_num(const int id, mapInfo *map);
landbetween **init_landbetween();
road **init_road();
struct list_head *init_devcard();

