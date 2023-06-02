#include"catan.h"
// landbetween *get_land(landbetween **lands, point p);
// int *get_road_1p_index(road **roads, point p);
int get_road_2p(road **roads, point p1, point p2);
int build_road(road **roads, player **players, int player_id,  int index);
int build_village(landbetween **lands, road **roads, player **players, int player_id, int index);
int build_castle(landbetween **lands, road **roads, player **players, int player_id, int index);
int buildaction_build_road(landbetween **lands, road **roads, player **players, int player_id);
bool road_buildable(landbetween **lands, road **roads, player **players, road r, int player_id);
int buildaction_build_village(landbetween **lands, road **roads, player **players, int player_id);
bool village_buildable(landbetween **lands, road **roads, player **players, landbetween l, int player_id, int mod);//mod 0 not concider road; 1 otherwise
int buildaction_build_castle(landbetween **lands, road **roads, player **players, int player_id);
bool is_resource_enough(player **players, int player_id, int resource_need[5]);
int build_action(landbetween **lands, road **roads, player **players, int player_id);

// landbetween *get_land(landbetween **lands, point p){
//     for(int i = 0; i < LAND_NUM; i++){
//         if(((*lands)+i)->p.x == p.x && ((*lands)+i)->p.y == p.y){
//             return ((*lands)+ i);
//         }
//     }
//     return NULL;
// }

// int *get_road_1p_index(road **roads, point p){
//     int count = 0;
//     int tmp[3];
//     for(int i = 0; i < ROAD_NUM; i++){
//         if((((*roads)+i)->start.x == p.x && ((*roads)+i)->start.y == p.y )|| (((*roads)+i)->end.x == p.x && ((*roads)+i)->end.y == p.y )){
//             tmp[count] = i;
//             count ++;
//         }
//     }
//     int *tmp2 = calloc(sizeof(int), count);
//     for(int i = 0; i < count; i++){
//         *(tmp2 + i) = tmp[i];
//     }
//     return tmp2;
// }

int get_road_2p(road **roads, point p1, point p2){
    for(int i = 0; i < ROAD_NUM; i++){
        if((((*roads)+i)->start.x == p1.x && ((*roads)+i)->start.y == p1.y ) && (((*roads)+i)->end.x == p2.x && ((*roads)+i)->end.y == p2.y )){
            return i;
        }
        if((((*roads)+i)->start.x == p2.x && ((*roads)+i)->start.y == p2.y ) && (((*roads)+i)->end.x == p1.x && ((*roads)+i)->end.y == p1.y )){
            return i;
        }
    }
    return -1;
}

int build_road(road **roads, player **players, int player_id,  int index){
    if(index != -1){
        ((*roads)+index)->owner = player_id;
        ((*players) + player_id)->number_of_building[ROAD] += 1;
        return 0;
    }
    else return -1;
}

int build_village(landbetween **lands, road **roads, player **players, int player_id, int index){
    landbetween *target = (*lands) + index;
    if(target != NULL){
        target->building = 1;
        target->has_building = true;
        target->owner = player_id;
        ((*players) + player_id)->number_of_building[SETTLEMENT] += 1;
        return 0;
    }
    else return -1;
}

int build_castle(landbetween **lands, road **roads, player **players, int player_id, int index){
    landbetween *target = (*lands) + index;
    if(target != NULL){
        target->building = 2;
        target->has_building = true;
        target->owner = player_id;
        ((*players) + player_id)->number_of_building[SETTLEMENT] -= 1;
        ((*players) + player_id)->number_of_building[CITY] += 1;
        return 0;
    }
    else return -1;
}

int buildaction_build_road(landbetween **lands, road **roads, player **players, int player_id){
    int resource_need[5] = {1, 1, 0, 0, 0};
    if(is_resource_enough(players, player_id, resource_need) == false){
        printf("Resource is not enough. ");
        return -1;
    } 
    if(((*players) + player_id)->number_of_building[ROAD] == 15){
        printf("Road number can not over than 15.");
        return -1;
    } 

    int ability[ROAD_NUM] = {0};
    for(int i = 0; i < ROAD_NUM; i++){
        ability[i] = road_buildable(lands, roads, players, *((*roads)+i), player_id);
    }


    int p1X = 0, p1Y = 0, p2X = 0, p2Y = 0;
    if(player_id == 1){
        printf("Please input the start of the road: x y \n");
        scanf("%d %d", &p1X, &p1Y);
    }
    if(player_id == 1){
        printf("Please input the end of the road: x y \n");
        scanf("%d %d", &p2X, &p2Y);
    }
    point a = {p1X, p1Y};
    point b = {p2X, p2Y};

    int tmp = get_road_2p(roads, a, b);
    if(tmp == -1){
        if(player_id == 1) printf("coordinate error\n");
        return -1;
    }
    if(ability[tmp] == 1){
        build_road(roads, players, player_id, tmp);
        for(int i = 0; i < 5; i++){
            ((*players) + player_id) -> resource[i] -= resource_need[i];
            resource[i] += resource_need[i];
        }
        return 0;
    }
    else{
        if(player_id == 1) printf("This location can not build\n");
        return -1;
    }
}

bool road_buildable(landbetween **lands, road **roads, player **players, road r, int player_id){
    if(r.owner != 0){
        return 0;
    }
    if((*lands)[land_index(r.start.x, r.start.y, lands)].owner == player_id || (*lands)[land_index(r.end.x, r.end.y, lands)].owner == player_id){
        return 1;
    }
    else{
        int count = 0;
        int tmp[3];
        for(int i = 0; i < ROAD_NUM; i++){
            if((((*roads)+i)->start.x == r.start.x && ((*roads)+i)->start.y == r.start.y )|| (((*roads)+i)->end.x == r.start.x && ((*roads)+i)->end.y == r.start.x )){
                tmp[count] = i;
                count ++;
            }
        }

        road tmp_road;
        for(int i = 0; i <count; i++){
            tmp_road = *((*roads) + tmp[i]);
            if(tmp_road.owner == player_id){
                return 1;
            }
        }

        count = 0;
        for(int i = 0; i < ROAD_NUM; i++){
            if((((*roads)+i)->start.x == r.end.x && ((*roads)+i)->start.y == r.end.y )|| (((*roads)+i)->end.x == r.end.x && ((*roads)+i)->end.y == r.end.x )){
                tmp[count] = i;
                count ++;
            }
        }
        for(int i = 0; i <count; i++){
            tmp_road = *((*roads) + tmp[i]);
            if(tmp_road.owner == player_id){
                return 1;
            }
        }
    }
    return 0;
}

int buildaction_build_village(landbetween **lands, road **roads, player **players, int player_id){
    int resource_need[5] = {1, 1, 1, 1, 0};
    if(is_resource_enough(players, player_id, resource_need) == false){
        if(player_id == 1) printf("Resource is not enough. ");
        return -1;
    } 
    if(((*players)+player_id)->number_of_building[SETTLEMENT] == 5){
        if(player_id == 1) printf("Village number can not over than 5. ");
        return -1;
    } 

    int ability[LAND_NUM] = {0};
    for(int i = 0; i < LAND_NUM; i++){
        ability[i] = village_buildable(lands, roads, players, *((*lands) + i), player_id, 1);
    }

    int pX = 0, pY = 0;
    if(player_id == 1){
        printf("Please input the location to building: x y \n");
        scanf("%d %d", &pX, &pY);
    }

    int tmp = land_index(pX, pY, lands);
    if(tmp == -1){
        if(player_id == 1) printf("coordinate error\n");
        return -1;
    }
    if(ability[tmp] == 1){
        build_village(lands, roads, players, player_id, tmp);
        for(int i = 0; i < 5; i++){
            ((*players) + player_id) -> resource[i] -= resource_need[i];
            resource[i] += resource_need[i];
        }
        return 0;
    }
    else{
        if(player_id == 1) printf("This location can not build\n");
        return -1;
    }
}

bool village_buildable(landbetween **lands, road **roads, player **players, landbetween l, int player_id, int mod){
    int count = 0;
    int tmp[3];
    for(int i = 0; i < ROAD_NUM; i++){
        if((((*roads)+i)->start.x == l.p.x && ((*roads)+i)->start.y == l.p.y )|| (((*roads)+i)->end.x == l.p.x && ((*roads)+i)->end.y == l.p.y )){
            tmp[count] = i;
            count ++;
        }
    }

    road tmp_road[count];
    for(int i = 0; i < count; i++){
        tmp_road[i] = *((*roads) + tmp[i]);
    }

    bool flag = 0;
    for(int j = 0; j < count; j++){
        if((*lands)[land_index(tmp_road[j].start.x, tmp_road[j].start.y, lands)].owner != 0 || (*lands)[land_index(tmp_road[j].start.x, tmp_road[j].start.y, lands)].has_building != 0
        || (*lands)[land_index(tmp_road[j].end.x, tmp_road[j].end.y, lands)].owner != 0 || (*lands)[land_index(tmp_road[j].end.x, tmp_road[j].end.y, lands)].has_building != 0){
            flag = 1;
        }
    }
    if(mod == 1){
        for(int j = 0; j < count; j++){
            if(tmp_road->owner == player_id){
                break;
            }
            if(j == count - 1) flag = 1;
        }
    }
    return !flag;
}

int buildaction_build_castle(landbetween **lands, road **roads, player **players, int player_id){
    int resource_need[5] = {0, 0, 0, 2, 3};
    if(is_resource_enough(players, player_id, resource_need) == false){
        if(player_id == 1) printf("Resource is not enough. ");
        return -1;
    } 
    if(((*players)+player_id)->number_of_building[CITY] == 4){
        if(player_id == 1) printf("Castle number can not over than 4. ");
        return -1;
    }

    int ability[LAND_NUM] = {0};
    for(int i = 0; i < LAND_NUM; i++){
        if(((*lands)+i)->owner == player_id && ((*lands)+i)->building == 1){
            ability[i] = 1;
        }
        else{
            ability[i] = 0;
        }
    }

    int pX = 0, pY = 0;
    if(player_id == 1){
        printf("Please input the location to building: x y \n");
        scanf("%d %d", &pX, &pY);
    }

    int tmp = land_index(pX, pY, lands);
    if(tmp == -1){
        if(player_id == 1) printf("coordinate error\n");
        return -1;
    }
    if(ability[tmp] == 1){
        build_castle(lands, roads, players, player_id, tmp);
        for(int i = 0; i < 5; i++){
            ((*players) + player_id) -> resource[i] -= resource_need[i];
            resource[i] += resource_need[i];
        }
        return 0;
    }
    else{
        if(player_id == 1) printf("This location can not build\n");
        return -1;
    }
}

bool is_resource_enough(player **players, int player_id, int resource_need[5]){
    for(int i = 0; i < 5; i++){
        if(((*players) + player_id) -> resource[i] < resource_need[i]){
            return false;
        }
    }
    return true;
}

int build_action(landbetween **lands, road **roads, player **players, int player_id){
    while(1){
        int act = 0; 
        // 0 road; 1 village; 2 castle; 3 exit

        if(player_id == 1){
            printf("Input 0 to build road; 1 to build village; 2 to build castle; 3 to exit\n");
            scanf("%d", &act);
        }

        if(act == 0){
            int build_if = buildaction_build_road(lands, roads, players, player_id);
            if(player_id == 1 && build_if == -1){
                printf("Build fail\n");
            }
        }
        else if(act == 1){
            int build_if = buildaction_build_village(lands, roads, players, player_id);
            if(player_id == 1 && build_if == -1){
                printf("Build fail\n");
            }
        }
        else if(act == 2){
            int build_if = buildaction_build_castle(lands, roads, players, player_id);
            if(player_id == 1 && build_if == -1){
                printf("Build fail\n");
            }
        }
        else if(act == 3){
            return 0;
        }
    }
}