#pragma once
#include "catan.h"
#include "color.h"

//all of the coordinate is transforms, from(1, 1) to (12, 3). (row colume)

int get_road_2p(mapInfo *map, const point p1, const point p2);
int get_land_p(mapInfo *map, const point point);
int get_player_index(mapInfo *map, const int player_id);
void print_test_building(mapInfo *map, const int ab[LAND_NUM]);
void print_test_road(mapInfo *map, const int ab[ROAD_NUM]);
int build_road(mapInfo *map, const int player_id, const int index);
int build_building(mapInfo *map, const int player_id, const int index);
road *ai_choose_road(mapInfo *map, const int ab[ROAD_NUM]);
landbetween *ai_choose_building(mapInfo *map, const int ab[LAND_NUM]);
point from_screen_to_coor(const int x1, const int y1);
int take_initial_resource(mapInfo *map, const int player_id, const point p);
int start_build(mapInfo *map, const int player_id);
int free_road_building_action(mapInfo *map, const int player_id);
bool is_resource_enough_b(mapInfo *map, const int player_id, const int resource_need[5]);
int build_action(mapInfo *map, const int player_id);

int get_road_2p(mapInfo *map, const point p1, const point p2){
    for(int i = 0; i < ROAD_NUM; i++){
        if((map->roads[i]->start.x == p1.x && map->roads[i]->start.y == p1.y ) && (map->roads[i]->end.x == p2.x && map->roads[i]->end.y == p2.y )){
            return i;
        }
        if((map->roads[i]->start.x == p2.x && map->roads[i]->start.y == p2.y ) && (map->roads[i]->end.x == p1.x && map->roads[i]->end.y == p1.y )){
            return i;
        }
    }
    return -1;
}

int get_land_p(mapInfo *map, const point point){
    for(int i = 0; i < LAND_NUM; i++){
        if(map->lands[i]->p.x == point.x && map->lands[i]->p.y == point.y){
            return i;
        }
    }
    return -1;
}

int get_player_index(mapInfo *map, const int player_id){
    for(int i = 0; i <= PLAYER_NUM; i++){
        if(map->players[i]->id == player_id) return i;
    }
    return 0;
}

void print_test_building(mapInfo *map, const int ab[LAND_NUM]){
    for(int i = 0; i < Y_LONG; i++){
        printf("%02d\t", i+1);
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == 0 || valid_point_mat[i][j] == TYPE_PIECE){
                printf("  ");
            }
            else{
                point p = {j, i};
                int index = get_land_p(map, p);
                if(ab[index] == 1){
                    PRINT_WHITE;
                    printf("o ");
                    PRINT_WHITE;
                }
                else{
                    switch (map->lands[index]->owner)
                    {
                    case -1:
                        printf("x ");
                        break;
                    case 1:
                        PRINT_RED;
                        printf("* ");
                        PRINT_WHITE;
                        break;
                    case 2:
                        PRINT_GREEN;
                        printf("* ");
                        PRINT_WHITE;
                        break;
                    case 3:
                        PRINT_YELLOW;
                        printf("* ");
                        PRINT_WHITE;
                        break;
                    case 4:
                        PRINT_BLUE;
                        printf("* ");
                        PRINT_WHITE;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        printf("\t");
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == 0 || valid_point_mat[i][j] == TYPE_PIECE){
                printf("  ");
            }
            else{
                point p = {j, i};
                int road_owner = -1;
                for(int k = 0; k < ROAD_NUM; k++){
                    if( (map->roads[k]->start.x == p.x && map->roads[k]->start.y == p.y)
                    ||  (map->roads[k]->end.x == p.x && map->roads[k]->end.y == p.y)){
                        if(map->roads[k]->owner != -1){
                            if(road_owner != -1 ) road_owner = 5;
                            else road_owner = map->roads[k]->owner;
                        }
                    }
                }
                switch (road_owner)
                {
                case -1:
                    printf("* ");
                    break;
                case 1:
                    PRINT_RED;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                case 2:
                    PRINT_GREEN;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                case 3:
                    PRINT_YELLOW;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                case 4:
                    PRINT_BLUE;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                case 5:
                    printf("x ");
                    break;
                default:
                    break;
                }
            }
        }
        printf("\n");
    }
    return;
}

void print_test_road(mapInfo *map, const int ab[ROAD_NUM]){
    for(int i = 0; i < Y_LONG; i++){
        printf("%02d\t", i+1);
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == 0 || valid_point_mat[i][j] == TYPE_PIECE){
                printf("  ");
            }
            else{
                point p = {j, i};
                switch (map->lands[get_land_p(map, p)]->owner)
                {
                case -1:
                    printf("* ");
                    break;
                case 1:
                    PRINT_RED;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                case 2:
                    PRINT_GREEN;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                case 3:
                    PRINT_YELLOW;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                case 4:
                    PRINT_BLUE;
                    printf("* ");
                    PRINT_WHITE;
                    break;
                default:
                    break;
                }
            }
        }
        printf("\t");
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == 0 || valid_point_mat[i][j] == TYPE_PIECE){
                printf("  ");
            }
            else{
                point p = {j, i};
                int road_owner = -1;
                for(int k = 0; k < ROAD_NUM; k++){
                    if( (map->roads[k]->start.x == p.x && map->roads[k]->start.y == p.y)
                    ||  (map->roads[k]->end.x == p.x && map->roads[k]->end.y == p.y)){
                        if(map->roads[k]->owner != -1){
                            if(road_owner != -1 ) road_owner = 5;
                            else road_owner = map->roads[k]->owner;
                        }
                    }
                }
                for(int k = 0; k < ROAD_NUM; k++){
                    if( (map->roads[k]->start.x == p.x && map->roads[k]->start.y == p.y)
                    ||  (map->roads[k]->end.x == p.x && map->roads[k]->end.y == p.y)){
                        if(ab[k] == 1){
                            road_owner += 10;
                        }
                    }
                }
                switch (road_owner % 10)
                {
                case 1:
                    PRINT_RED;
                    break;
                case 2:
                    PRINT_GREEN;
                    break;
                case 3: 
                    PRINT_YELLOW;
                    break;
                case 4:
                    PRINT_BLUE;
                    break;
                case 5:
                    PRINT_MAGENTA;
                    break;
                default:
                    break;
                }
                if(road_owner > 5) printf("o ");
                else printf("* ");
                PRINT_WHITE;
            }  
        }
        printf("\n");
    }
    return;
}

int build_road(mapInfo *map, const int player_id, const int index){
    if(index >= 0 && index < ROAD_NUM && map->roads[index]->owner == -1){
        map->roads[index]->owner = player_id;
        map->players[get_player_index(map, player_id)]->number_of_building[ROAD] += 1;
        return 0;
    }
    else return -1;
}

int build_building(mapInfo *map, const int player_id, const int index){
    if(index >= 0 && index < LAND_NUM && map->lands[index]->owner == -1){
        map->lands[index]->building = 1;
        map->lands[index]->has_building = true;
        map->lands[index]->owner = player_id;
        map->players[get_player_index(map, player_id)]->number_of_building[SETTLEMENT] += 1;
        map->players[get_player_index(map, player_id)]->VP ++;
        return 0;
    }
    else if(index >= 0 && index < LAND_NUM && map->lands[index]->owner == player_id && map->lands[index]->building == 1){
        map->lands[index]->building = 2;
        map->players[get_player_index(map, player_id)]->number_of_building[SETTLEMENT] -= 1;
        map->players[get_player_index(map, player_id)]->number_of_building[CITY] += 1;
        map->players[get_player_index(map, player_id)]->VP ++;
        return 0;
    }
    else return -1;
}

point from_screen_to_coor(const int x1, const int y1){
    point p = {0, 0};
    if(y1 - 1 < Y_LONG) p.y = y1 - 1;
    else return p;

    int count = 0;
    for(int i = 0; i < X_LONG; i++){
        if(valid_point_mat[p.y][i] != 0 && valid_point_mat[p.y][i] != TYPE_PIECE){
            count++;
            if(count == x1) p.x = i;
        }
    }
    return p;
}

int take_initial_resource(mapInfo *map, const int player_id, const point p){
    int top = p.y - 1, bot = p.y + 2, left = p.x - 1, right = p.x + 1;
    if(top < 0) top = 0;
    if(bot > Y_LONG) bot = Y_LONG;
    if(left < 0) left = 0;
    if(right > X_LONG) right = X_LONG;

    for(int i = top; i < bot; i++){
        for(int j = left; j < right; j++){
            if(valid_point_mat[i][j] == TYPE_PIECE){
                for(int k = 0; k < PIECE_NUM; k++){
                    if(map->pieces[k]->p.x == j && map->pieces[k]->p.y == i){
                        map->players[get_player_index(map, player_id)]->resource[map->pieces[k]->eco_type] += 1;
                        resource[map->pieces[k]->eco_type] -= 1;
                    }
                }
            }
        }
    }
    return 0;
}

road *ai_choose_road(mapInfo *map, const int ab[ROAD_NUM]){
    int n = 0, gra = 10, c = 0, gra_top = 50;
    do{
        gra = 10;
        n = random() % ROAD_NUM;
        if(!ab[n]) continue;
        c++;
        if(c > 20000){
            gra_top --;
            c = 0;
        }


        if(map->roads[n]->start.x > map->roads[n]->end.x && map->roads[n]->start.x < X_LONG/2) gra--;
        if(map->roads[n]->start.y > map->roads[n]->end.y && map->roads[n]->start.y < Y_LONG/2) gra--;
        if(map->roads[n]->start.x < map->roads[n]->end.x && map->roads[n]->start.x > X_LONG/2) gra--;
        if(map->roads[n]->start.y < map->roads[n]->end.y && map->roads[n]->start.x > X_LONG/2) gra--;

    }while((!ab[n]) || gra < gra_top);
    return map->roads[n];
}

landbetween *ai_choose_building(mapInfo *map, const int ab[LAND_NUM]){
    int n = 0, gra = 10, c = 0, gra_top = 30;
    do{
        gra = 10;
        n = (random()+1) % LAND_NUM;
        if(!ab[n]) continue;
        c++;
        if(c > 50000){
            gra_top --;
            c = 0;
        }

        int getsource[5] = {0};
        int point[3] = {0};
        int count = 0;

        int top = map->lands[n]->p.y - 1, bot = map->lands[n]->p.y + 2, left = map->lands[n]->p.x - 1, right = map->lands[n]->p.x + 1;
        if(top < 0) top = 0;
        if(bot > Y_LONG) bot = Y_LONG;
        if(left < 0) left = 0;
        if(right > X_LONG) right = X_LONG;

        for(int i = top; i < bot; i++){
            for(int j = left; j < right; j++){
                if(valid_point_mat[i][j] == TYPE_PIECE){
                    for(int k = 0; k < PIECE_NUM; k++){
                        if(map->pieces[k]->p.x == j && map->pieces[k]->p.y == i){
                            getsource[map->pieces[k]->eco_type] += 1;
                            point[count] = map->pieces[k]->number;
                            count++;
                        }
                    }
                }
            }
        }

        if(getsource[3] + getsource[4] > 1) gra += 4;
        if(getsource[3] > 1) gra += 6;
        if(getsource[2] * getsource[3] * getsource[4] == 1) gra += 6;
        if(getsource[0] * getsource[1] >= 1) gra += 3;

        if(getsource[0]+getsource[1]+getsource[2]+getsource[3]+getsource[4] < 3 && random()%100 < 90) continue;

        for(int i = 0; i < 3; i++){
            if(point[i] == 7) gra -= 12;
            else if(point[i] == 0) gra -= 12;
            else if(point[i] > 7) gra -= ((point[i] - 7) / 2);
            else gra -= ((7 - point[i]) / 2);
        }
    }while((!ab[n]) || gra < gra_top);
    return map->lands[n];
}

int start_build(mapInfo *map, const int player_id){
    printf("Player %d turn...\n", player_id);
    int ability[LAND_NUM] = {0};
    for(int i = 0; i < LAND_NUM; i++){
        ability[i] = 1;
    }
    for(int i = 0; i < LAND_NUM; i++){
        if(ability[i] == 0) continue;
        if(map->lands[i]->has_building){
            ability[i] = 0;
            continue;
        } 
        for(int j = 0; j < ROAD_NUM; j++){
            if(map->roads[j]->start.x == map->lands[i]->p.x && map->roads[j]->start.y == map->lands[i]->p.y ){
                if(map->lands[get_land_p(map, map->roads[j]->end)]->has_building) ability[i] = 0;
            }
            if(map->roads[j]->end.x == map->lands[i]->p.x && map->roads[j]->end.y == map->lands[i]->p.y){
                if(map->lands[get_land_p(map, map->roads[j]->start)]->has_building) ability[i] = 0;
            }
        }
    }

    int x = 0, y = 0;
    point location = {0, 0};
    if(player_id == 1){
        print_test_building(map, ability);
        printf("Please enter a coordinate to build village(row colume):\n");
        while(get_land_p(map, location) == -1 || !ability[get_land_p(map, location)]){
            printf("\tbuilding location: ");
            x = 0;
            y = 0;
            if(scanf("%d %d", &y, &x) == 0) continue;
            location = from_screen_to_coor(x, y);
            printf("\n");
            if(location.x * location.y == 0 || get_land_p(map, location) == -1 || !ability[get_land_p(map, location)]) printf("Location can not build, please try again.\n");
        }
    }
    else{
        ai_choose_building(map, ability);
        location = ai_choose_building(map, ability)->p;
        printf("\n");
    }
    if(build_building(map, player_id, get_land_p(map, location)) != -1){
        take_initial_resource(map, player_id, location);
        int ability_road[ROAD_NUM] = {0};
        for(int i = 0; i < ROAD_NUM; i++){
            if(map->roads[i]->owner != -1) continue;
            if(    (map->roads[i]->start.x == location.x && map->roads[i]->start.y == location.y)
                ||  (map->roads[i]->end.x == location.x && map->roads[i]->end.y == location.y)){
                ability_road[i] = 1;
            }
        }
        point p1 = {0, 0};
        point p2 = {0, 0};
        if(player_id == 1){
            print_test_road(map, ability_road);
            printf("Please enter two coordinate to build road(row colume):\n");
            while(get_road_2p(map, p1, p2) == -1 || !ability_road[get_road_2p(map, p1, p2)]){
                x = 0;
                y = 0;
                printf("\troad start: ");
                if(scanf("%d %d", &y, &x) == 0) continue;
                p1 = from_screen_to_coor(x, y);
                x = 0;
                y = 0;
                printf("\troad end:   ");
                if(scanf("%d %d", &y, &x) == 0) continue;
                p2 = from_screen_to_coor(x, y);
                printf("\n");
                if(get_road_2p(map, p1, p2) == -1 || !ability_road[get_road_2p(map, p1, p2)]) printf("Location can not build, please try again.\n");
            }
        }
        else{
            road *tmp = ai_choose_road(map, ability_road);
            p1 = tmp->start;
            p2 = tmp->end;
        }
        if(get_road_2p(map, p1, p2) == -1 || build_road(map, player_id, get_road_2p(map, p1, p2)) == -1){
            map->lands[get_land_p(map, location)]->building = -1;
            map->lands[get_land_p(map, location)]->has_building = false;
            map->lands[get_land_p(map, location)]->owner = -1;
            map->players[get_player_index(map, player_id)]->number_of_building[SETTLEMENT] -= 1;
            map->players[get_player_index(map, player_id)]->VP --;
            return -1;
        }
    }
    else return -1;
    return 0;
}

int free_road_building_action(mapInfo *map, const int player_id){ //return 0 if build success; -1 if condition error; -2 if exit with no buinding; -3 if unknow error
    for(int n = 0; n < 2; n++){
        if(map->players[get_player_index(map, player_id)]->number_of_building[ROAD] >= 15){
            printf("Road number can not over than 15. \n\n");
            if(n == 0){
                return -1;
            }
            if(n == 1){
                return 0;
            }
        }

        int ability[ROAD_NUM] = {0};
        for(int i = 0; i < ROAD_NUM; i++){
            if(map->roads[i]->owner != -1) continue;
            if(    map->lands[get_land_p(map, map->roads[i]->start)]->owner == player_id
            ||  map->lands[get_land_p(map, map->roads[i]->end)]->owner == player_id){
                ability[i] = 1;
                continue;
            }
            for(int j = 0; j < ROAD_NUM; j++){
                if(     (map->roads[j]->start.x == map->roads[i]->end.x && map->roads[j]->start.y == map->roads[i]->end.y)
                ||  (map->roads[j]->end.x == map->roads[i]->start.x && map->roads[j]->end.y == map->roads[i]->start.y)){
                    if(map->roads[j]->owner == player_id){
                        ability[i] = 1;
                        break;
                    }
                }
            }
        }

        int jump_flag = 1;
        for(int i = 0; i < ROAD_NUM; i++){
            if(ability[i] == 1){
                jump_flag = 0;
                break;
            }
        }
        if(jump_flag){
            printf("There isn't any location can be built.\n\n");
            if(n == 0){
                return -1;
            }
            if(n == 1){
                return 0;
            }
        }
        //print_test_road(map, ability);

        int x = 0, y = 0;
        point p1 = {0, 0};
        point p2 = {0, 0};
        printf("Please enter two coordinate to build road(row colume):\n\tEnter 0 0 if you want to exit(Notice: if you have built one time, you will give up a chance)\n");
        while(get_road_2p(map, p1, p2) == -1 || !ability[get_road_2p(map, p1, p2)]){
            // print_test_building(map, ability);
            x = 0;
            y = 0;
            printf("\troad start: ");
            if(scanf("%d %d", &y, &x) == 0) continue;
            if(x == 0 && y == 0) break;
            p1 = from_screen_to_coor(x, y);
            x = 0;
            y = 0;
            printf("\troad end:   ");
            if(scanf("%d %d", &y, &x) == 0) continue;
            if(x == 0 && y == 0){
                if(n == 0){
                    printf("exit\n");
                    return -2;
                }
                if(n == 1){
                    printf("exit\n");
                    return 0;
                }
            }
            p2 = from_screen_to_coor(x, y);
            if(get_road_2p(map, p1, p2) == -1 || !ability[get_road_2p(map, p1, p2)]) printf("Location can not build, please try again.\n");
        }
        if(get_road_2p(map, p1, p2) == -1 || build_road(map, player_id, get_road_2p(map, p1, p2)) == -1){
            printf("Build fail\n");
            return -3;
        }
    }
    return 0;
}
//AI

bool is_resource_enough_b(mapInfo *map, const int player_id, const int resource_need[5]){
    for(int i = 0; i < 5; i++){
        if(map->players[get_player_index(map, player_id)]->resource[i] < resource_need[i]){
            return false;
        }
    }
    return true;
}

int build_action(mapInfo *map, const int player_id){
    if(player_id == 1) printf("Player %d, welcome to building action.\n", player_id);
    while(1){
        if(player_id == 1){
            int act = 0; // 0 road; 1 village; 2 castle; 3 exit
            printf("Input:\t0 to exit \n\t1 to build road \n\t2 to build village \n\t3 to build castle \n\t4 to buy development card\n");
            printf("action:\t");
            if(scanf("%d", &act) == 0) continue;

            if(act == 0){
                printf("Exit. \n\n");
                return 0;
            }
            else if(act == 1){
                int resource_need[5] = {1, 1, 0, 0, 0};
                if(!is_resource_enough_b(map, player_id, resource_need)){
                    printf("Resource is not enough. \n\n");
                    continue;
                }
                if(map->players[get_player_index(map, player_id)]->number_of_building[ROAD] >= 15){
                    printf("Road number can not over than 15. \n\n");
                    continue;
                }

                int ability[ROAD_NUM] = {0};
                for(int i = 0; i < ROAD_NUM; i++){
                    if(map->roads[i]->owner != -1) continue;
                    if(map->lands[get_land_p(map, map->roads[i]->start)]->owner == player_id
                    ||  map->lands[get_land_p(map, map->roads[i]->end)]->owner == player_id){
                        ability[i] = 1;
                        continue;
                    }
                    for(int j = 0; j < ROAD_NUM; j++){
                        if(map->roads[j]->start.x == map->roads[i]->end.x && map->roads[j]->start.y == map->roads[i]->end.y){
                            if(map->roads[j]->owner == player_id && (map->lands[get_land_p(map, map->roads[j]->start)]->owner == -1 || map->lands[get_land_p(map, map->roads[j]->start)]->owner == player_id)){
                                ability[i] = 1;
                                break;
                            }
                        }
                        if(map->roads[j]->end.x == map->roads[i]->start.x && map->roads[j]->end.y == map->roads[i]->start.y){
                            if(map->roads[j]->owner == player_id && (map->lands[get_land_p(map, map->roads[j]->end)]->owner == -1 || map->lands[get_land_p(map, map->roads[j]->end)]->owner == player_id)){
                                ability[i] = 1;
                                break;
                            }
                        }
                    }
                }

                int jump_flag = 1;
                for(int i = 0; i < ROAD_NUM; i++){
                    if(ability[i] == 1){
                        jump_flag = 0;
                        break;
                    }
                }
                if(jump_flag){
                    printf("There isn't any location can be built.\n\n");
                    continue;
                }
                print_test_road(map, ability);

                int x = 0, y = 0;
                point p1 = {0, 0};
                point p2 = {0, 0};
                printf("Please enter two coordinate to build road(row colume):\n\tEnter 0 0 if you want to exit\n");
                while(get_road_2p(map, p1, p2) == -1 || !ability[get_road_2p(map, p1, p2)]){
                    // print_test_building(map, ability);
                    x = 0;
                    y = 0;
                    printf("\troad start: ");
                    if(scanf("%d %d", &y, &x) == 0) continue;
                    if(x == 0 && y == 0) break;
                    p1 = from_screen_to_coor(x, y);
                    x = 0;
                    y = 0;
                    printf("\troad end:   ");
                    if(scanf("%d %d", &y, &x) == 0) continue;
                    if(x == 0 && y == 0) break;
                    p2 = from_screen_to_coor(x, y);
                    if(get_road_2p(map, p1, p2) == -1 || !ability[get_road_2p(map, p1, p2)]) printf("Location can not build, please try again.\n");
                }
                if(get_road_2p(map, p1, p2) == -1) printf("exit\n");
                else if(build_road(map, player_id, get_road_2p(map, p1, p2)) == -1) printf("Build fail\n");
                else{
                    for(int i = 0; i < 5; i++){
                        map->players[get_player_index(map, player_id)]->resource[i] -= resource_need[i];
                        resource[i] += resource_need[i];
                    }
                }
            }
            else if(act == 2){
                int resource_need[5] = {1, 1, 1, 1, 0};
                if(!is_resource_enough_b(map, player_id, resource_need)){
                    printf("Resource is not enough. \n\n");
                    continue;
                }
                if(map->players[get_player_index(map, player_id)]->number_of_building[SETTLEMENT] >= 5){
                    printf("Village number can not over than 5. \n\n");
                    continue;
                }

                int ability[LAND_NUM] = {0};
                for(int i = 0; i < LAND_NUM; i++){
                    int flag = 0;
                    if(map->lands[i]->has_building) continue;
                    for(int j = 0; j < ROAD_NUM; j++){
                        if(map->roads[j]->start.x == map->lands[i]->p.x && map->roads[j]->start.y == map->lands[i]->p.y ){
                            if(map->lands[get_land_p(map, map->roads[j]->end)]->has_building) flag = 1;
                        }
                        if(map->roads[j]->end.x == map->lands[i]->p.x && map->roads[j]->end.y == map->lands[i]->p.y){
                            if(map->lands[get_land_p(map, map->roads[j]->start)]->has_building) ability[i] = flag = 1;
                        }
                    }
                    if(flag) continue;
                    
                    flag = 0;
                    for(int j = 0; j < ROAD_NUM; j++){
                        if(map->roads[j]->start.x == map->lands[i]->p.x && map->roads[j]->start.y == map->lands[i]->p.y ){
                            if(map->roads[j]->owner == player_id) flag = 1;
                        }
                        if(map->roads[j]->end.x == map->lands[i]->p.x && map->roads[j]->end.y == map->lands[i]->p.y){
                            if(map->roads[j]->owner == player_id) flag = 1;
                        }
                    }
                    if(flag) ability[i] = 1;
                }
                print_test_building(map, ability);
                int jump_flag = 1;
                for(int i = 0; i < LAND_NUM; i++){
                    if(ability[i] == 1){
                        jump_flag = 0;
                        break;
                    }
                }
                if(jump_flag){
                    printf("There isn't any location can be built.\n\n");
                    continue;
                }

                int x = 0, y = 0;
                point location = {0, 0};
                printf("Please enter a coordinate to build village(row colume):\n\tEnter 0 0 if you want to exit\n");
                while(get_land_p(map, location) == -1 || !ability[get_land_p(map, location)]){
                    printf("\tbuilding location: ");
                    x = 0;
                    y = 0;
                    if(scanf("%d %d", &y, &x) == 0) continue;
                    if(x == 0 && y == 0) break;
                    location = from_screen_to_coor(x, y);
                    if(get_land_p(map, location) == -1 || !ability[get_land_p(map, location)]) printf("Location can not build, please try again.\n");
                }
                if(get_land_p(map, location) == -1) printf("exit\n");
                else if(build_building(map, player_id, get_land_p(map, location)) == -1) printf("Build fail\n");
                else{
                    for(int i = 0; i < 5; i++){
                        map->players[get_player_index(map, player_id)]->resource[i] -= resource_need[i];
                        resource[i] += resource_need[i];
                    }
                }
            }
            else if(act == 3){
                int resource_need[5] = {0, 0, 0, 2, 3};
                if(!is_resource_enough_b(map, player_id, resource_need)){
                    printf("Resource is not enough. \n\n");
                    continue;
                }
                if(map->players[get_player_index(map, player_id)]->number_of_building[CITY] >= 4){
                    printf("Castle number can not over than 4. \n\n");
                    continue;
                }

                int ability[LAND_NUM] = {0};
                for(int i = 0; i < LAND_NUM; i++){
                    if(map->lands[i]->owner == player_id && map->lands[i]->building == 1){
                        ability[i] = 1;
                    }
                    else{
                        ability[i] = 0;
                    }
                }
                print_test_building(map, ability);
                int jump_flag = 1;
                for(int i = 0; i < LAND_NUM; i++){
                    if(ability[i] == 1){
                        jump_flag = 0;
                        break;
                    }
                }
                if(jump_flag){
                    printf("There isn't any location can be built.\n\n");
                    continue;
                }


                int x = 0, y = 0;
                point location = {0, 0};
                printf("Please enter a coordinate to build castle(row colume):\n\tEnter 0 0 if you want to exit\n");
                while(get_land_p(map, location) == -1 || !ability[get_land_p(map, location)]){
                    printf("\tbuilding location: ");
                    x = 0;
                    y = 0;
                    if(scanf("%d %d", &y, &x) == 0) continue;
                    if(x == 0 && y == 0) break;
                    location = from_screen_to_coor(x, y);
                    if(get_land_p(map, location) == -1 || !ability[get_land_p(map, location)]) printf("Location can not build, please try again.\n");
                }
                if(get_land_p(map, location) == -1) printf("exit\n");
                else if(build_building(map, player_id, get_land_p(map, location)) == -1) printf("Build fail\n");
                else{
                    for(int i = 0; i < 5; i++){
                        map->players[get_player_index(map, player_id)]->resource[i] -= resource_need[i];
                        resource[i] += resource_need[i];
                    }
                }
            }
            else if(act == 4){
                int resource_need[5] = {0, 0, 1, 1, 1};
                if(!is_resource_enough_b(map, player_id, resource_need)){
                    printf("Resource is not enough. \n\n");
                    continue;
                } 
                if(list_empty(map->devcards)){
                    printf("Cards run out. \n\n");
                    continue;
                }
                list_move(map->devcards->next, map->players[get_player_index(map, player_id)]->devcard_list);
                for(int i = 0; i < 5; i++){
                    map->players[get_player_index(map, player_id)]->resource[i] -= resource_need[i];
                    resource[i] += resource_need[i];
                }
            }
            else{
                    printf("Input error. \n\n");
                    continue;
            }
        }
        else{
            if(random()%100 < 3) break;
            int resource_need_road[5] = {1, 1, 0, 0, 0};
            int resource_need_village[5] = {1, 1, 1, 1, 0};
            int resource_need_castle[5] = {0, 0, 0, 2, 3};
            int resource_need_card[5] = {0, 0, 1, 1, 1};
            int act1 = is_resource_enough_b(map, player_id, resource_need_road) && map->players[get_player_index(map, player_id)]->number_of_building[ROAD] < 15;
            int act2 = is_resource_enough_b(map, player_id, resource_need_village) && map->players[get_player_index(map, player_id)]->number_of_building[SETTLEMENT] < 5;
            int act3 = is_resource_enough_b(map, player_id, resource_need_castle) && map->players[get_player_index(map, player_id)]->number_of_building[CITY]< 4;
            int act4 = is_resource_enough_b(map, player_id, resource_need_card) && !list_empty(map->devcards);

            if(random()%10 < 1) act1 = 0;
            if(random()%10 < 2) act2 = 0;
            if(random()%10 < 3) act3 = 0;
            if(random()%10 < 4) act4 = 0;

            if(act2 && random()%10 < 5) act1 = 0;
            if(act3 && random()%10 < 4) act1 = 0;
            if(act3 && random()%10 < 6) act2 = 0;
            if(act4 && random()%10 < 1){
                act1 = 0;
                act2 = 0;
                act3 = 0;
            }

            if(act1){
                if(random()%100 < 1) break;
                int ability[ROAD_NUM] = {0};
                for(int i = 0; i < ROAD_NUM; i++){
                    if(map->roads[i]->owner != -1) continue;
                    if(map->lands[get_land_p(map, map->roads[i]->start)]->owner == player_id
                    ||  map->lands[get_land_p(map, map->roads[i]->end)]->owner == player_id){
                        ability[i] = 1;
                        continue;
                    }
                    for(int j = 0; j < ROAD_NUM; j++){
                        if(map->roads[j]->start.x == map->roads[i]->end.x && map->roads[j]->start.y == map->roads[i]->end.y){
                            if(map->roads[j]->owner == player_id && (map->lands[get_land_p(map, map->roads[j]->start)]->owner == -1 || map->lands[get_land_p(map, map->roads[j]->start)]->owner == player_id)){
                                ability[i] = 1;
                                break;
                            }
                        }
                        if(map->roads[j]->end.x == map->roads[i]->start.x && map->roads[j]->end.y == map->roads[i]->start.y){
                            if(map->roads[j]->owner == player_id && (map->lands[get_land_p(map, map->roads[j]->end)]->owner == -1 || map->lands[get_land_p(map, map->roads[j]->end)]->owner == player_id)){
                                ability[i] = 1;
                                break;
                            }
                        }
                    }
                }

                int jump_flag = 1;
                for(int i = 0; i < ROAD_NUM; i++){
                    if(ability[i] == 1){
                        jump_flag = 0;
                        break;
                    }
                }
                if(jump_flag){
                    continue;
                }

                road *tmp = ai_choose_road(map, ability);
                point p1 = tmp->start;
                point p2 = tmp->end;
                
                if(get_road_2p(map, p1, p2) == -1 || build_road(map, player_id, get_road_2p(map, p1, p2)) == -1) continue;
                else{
                    for(int i = 0; i < 5; i++){
                        map->players[get_player_index(map, player_id)]->resource[i] -= resource_need_road[i];
                        resource[i] += resource_need_road[i];
                    }
                }
            }
            else if(act2){
                if(random()%100 < 1) break;
                int ability[LAND_NUM] = {0};
                for(int i = 0; i < LAND_NUM; i++){
                    int flag = 0;
                    if(map->lands[i]->has_building) continue;
                    for(int j = 0; j < ROAD_NUM; j++){
                        if(map->roads[j]->start.x == map->lands[i]->p.x && map->roads[j]->start.y == map->lands[i]->p.y ){
                            if(map->lands[get_land_p(map, map->roads[j]->end)]->has_building) flag = 1;
                        }
                        if(map->roads[j]->end.x == map->lands[i]->p.x && map->roads[j]->end.y == map->lands[i]->p.y){
                            if(map->lands[get_land_p(map, map->roads[j]->start)]->has_building) ability[i] = flag = 1;
                        }
                    }
                    if(flag) continue;
                    
                    flag = 0;
                    for(int j = 0; j < ROAD_NUM; j++){
                        if(map->roads[j]->start.x == map->lands[i]->p.x && map->roads[j]->start.y == map->lands[i]->p.y ){
                            if(map->roads[j]->owner == player_id) flag = 1;
                        }
                        if(map->roads[j]->end.x == map->lands[i]->p.x && map->roads[j]->end.y == map->lands[i]->p.y){
                            if(map->roads[j]->owner == player_id) flag = 1;
                        }
                    }
                    if(flag) ability[i] = 1;
                }
                int jump_flag = 1;
                for(int i = 0; i < LAND_NUM; i++){
                    if(ability[i] == 1){
                        jump_flag = 0;
                        break;
                    }
                }
                if(jump_flag){
                    continue;
                }

                point location = ai_choose_building(map, ability)->p;
                if(get_land_p(map, location) == -1 || build_building(map, player_id, get_land_p(map, location)) == -1) continue;
                else{
                    for(int i = 0; i < 5; i++){
                        map->players[get_player_index(map, player_id)]->resource[i] -= resource_need_village[i];
                        resource[i] += resource_need_village[i];
                    }
                }
            }
            else if(act3){
                if(random()%100 < 1) break;
                int ability[LAND_NUM] = {0};
                for(int i = 0; i < LAND_NUM; i++){
                    if(map->lands[i]->owner == player_id && map->lands[i]->building == 1){
                        ability[i] = 1;
                    }
                    else{
                        ability[i] = 0;
                    }
                }
                int jump_flag = 1;
                for(int i = 0; i < LAND_NUM; i++){
                    if(ability[i] == 1){
                        jump_flag = 0;
                        break;
                    }
                }
                if(jump_flag){
                    continue;
                }

                point location = ai_choose_building(map, ability)->p;
                if(get_land_p(map, location) == -1 || build_building(map, player_id, get_land_p(map, location)) == -1) continue;
                else{
                    for(int i = 0; i < 5; i++){
                        map->players[get_player_index(map, player_id)]->resource[i] -= resource_need_castle[i];
                        resource[i] += resource_need_castle[i];
                    }
                }
            }
            else if(act4){
                if(random()%100 < 1) break;
                list_move(map->devcards->next, map->players[get_player_index(map, player_id)]->devcard_list);
                for(int i = 0; i < 5; i++){
                    map->players[get_player_index(map, player_id)]->resource[i] -= resource_need_card[i];
                    resource[i] += resource_need_card[i];
                }
            }
            else{
                printf("\n");
                return 0;
            }
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n");
    }
    return 0;
}
