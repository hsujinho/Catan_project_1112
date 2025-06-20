#include "game_init.h"


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

int resource_num(const int id, mapInfo *map){
    player **players = map->players;
    int index = player_index(id, players);
    int sum = 0;
    for(int i = 0; i < 5; i++)
        sum += players[index]->resource[i];
    return sum;
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
        card->used = -1;
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


