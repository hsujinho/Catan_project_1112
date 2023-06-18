#include "catan.h"
#include "color.h"
#include "build.h"

void print_simple_map(){
    for(int i = 0; i < Y_LONG; i++){
        for(int j = 0; j < X_LONG; j++){
            if(valid_point_mat[i][j] == 0){
                printf("  ");
            }else if(valid_point_mat[i][j] != TYPE_PIECE){
                if(valid_point_mat[i][j] != TYPE_LANDBETWEEN){
                    if(valid_point_mat[i][j] == TYPE_PORT_ANY){
                        PRINT_BLUE;
                        printf("P ");
                        PRINT_WHITE;
                    }
                    else{
                        PRINT_YELLOW;
                        printf("P ");
                        PRINT_WHITE;
                    }
                }
                else
                    printf("* ");
            }
            else{
                PRINT_RED;
                printf("+ ");
                PRINT_WHITE;
            }
        }
        printf("\n");
    }
}

int main(){ 
    printf("Welcome to Catan!\n");
    //print_simple_map();
    PRESS_ENTER;

    //declare variables
    player **players = NULL;
    piece **pieces = NULL;
    landbetween **landbetweens = NULL;
    road **roads = NULL;
    struct list_head *devcards = NULL;
    mapInfo *map = malloc(sizeof(mapInfo));
    //initialize variables
    init_game(&pieces, &landbetweens, &roads, &players, &devcards);
    map->players = players;
    map->pieces = pieces;
    map->lands = landbetweens;
    map->roads = roads;
    map->devcards = devcards;

    //init SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *window = SDL_CreateWindow("Catan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //render map
    render_map(renderer, map);

    //game loop
    bool isRunning = true, isWindowOpen = true, isBuildInitalSettle = false;
    while (isRunning && isWindowOpen) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isWindowOpen = false;
            }      
        }

        if(!isBuildInitalSettle){
            //setting initial building and take resources
            int reverse_turn[4] = {0};
            //setting first settlement
            for(int i = 0; i < PLAYER_NUM; i++){
                int id = players[i]->id;
                reverse_turn[3 - i] = id;
                // if(id == 1){
                //     printf("Please choose your initial building\n");

                //     printf("please enter the x and y coordinate of the point to build your first settlement\n");
                //     int x, y, chk, chk2, chk3, chk4;
                //     while( (chk = scanf("%d %d", &x, &y)) != 2 || (chk2 = !is_in_three_pieces_lands_pos(x, y)) || (chk3 = is_land_occupied(map, x, y, id)) || (chk4 = is_land_connect_other_building(map, x, y))){
                //         if(chk != 2){
                //             printf(RED"Please enter two integers\n"WHITE);
                //             while(getchar() != '\n');
                //         }
                //         else if(chk2){
                //             printf(RED"Please enter a valid coordinate that among 3 pieces\n"WHITE);
                //         }
                //         else if(chk3){
                //             printf(RED"Please enter an unoccupied land\n"WHITE);
                //         }
                //         else if(chk4){
                //             printf(RED"Please enter a land that connect to other building\n"WHITE);
                //         }
                //     }
                //     //build settlement
                //     for(int j = 0; j < LAND_NUM; j++){
                //         if(landbetweens[j]->p.x == x && landbetweens[j]->p.y == y){
                //             landbetweens[j]->building = SETTLEMENT;
                //             landbetweens[j]->owner = id;
                //             landbetweens[j]->has_building = true;
                //             printf("You have built a settlement at (%d, %d)\n", x, y);
                //             break;
                //         }
                //     }

                //     //start_build(map, id); <-- this function include build initial settlement, road, and take initial resource
                //     //desire to add the function which can render where can build
                //     render_map(renderer, map);
                    
                //     int cho_num = 0, cho;
                //     point sta[3] = {{0, 0}, {0, 0}, {0, 0}}, end[3] = {{0, 0}, {0, 0}, {0, 0}};
                //     for(int k = 0; k < ROAD_NUM; k++){
                //         if( (roads[k]->start.x == x && roads[k]->start.y == y) || (roads[k]->end.x == x && roads[k]->end.y == y)){
                //             sta[cho_num] = roads[k]->start;
                //             end[cho_num] = roads[k]->end;
                //             cho_num++;
                //             printf("Road %d: (%d, %d) -> (%d, %d)\n", cho_num, roads[k]->start.x, roads[k]->start.y, roads[k]->end.x, roads[k]->end.y);
                //         }
                //     }
                //     printf("Please enter the number of roads above to choose a road to build\n");
                //     while((chk = scanf("%d", &cho)) != 1 || cho < 1 || cho > cho_num){
                //         if(chk != 1){
                //             printf(RED"Please enter an integer\n"WHITE);
                //             while(getchar() != '\n');
                //         }
                //         else{
                //             printf(RED"Please enter a valid number\n"WHITE);
                //         }
                //     }
                //     //build road
                //     for(int k = 0; k < ROAD_NUM; k++){
                //         if(roads[k]->start.x == sta[cho - 1].x && roads[k]->start.y == sta[cho - 1].y && roads[k]->end.x == end[cho - 1].x && roads[k]->end.y == end[cho - 1].y){
                //             roads[k]->owner = id;
                //             printf("You have built a road at (%d, %d) -> (%d, %d)\n", roads[k]->start.x, roads[k]->start.y, roads[k]->end.x, roads[k]->end.y);
                //             break;
                //         }
                //     }

                // }
                // else{
                    start_build(map, id, renderer);
                    render_map(renderer, map);
                    
                // }
            }
            //setting second settlement
            for(int i = 0; i < PLAYER_NUM; i++){
                for(int j = 0; j < PLAYER_NUM; j++){
                    if(reverse_turn[i] == players[j]->id){
                        // if(reverse_turn[i] == 1){
                        //     printf("Please choose your initial building\n");

                        //     printf("please enter the x and y coordinate of the point to build your second settlement\n");
                        //     int x, y, chk, chk2, chk3, chk4;
                        //     while( (chk = scanf("%d %d", &x, &y)) != 2 || (chk2 = !is_in_three_pieces_lands_pos(x, y)) || (chk3 = is_land_occupied(map, x, y, reverse_turn[i])) || (chk4 = is_land_connect_other_building(map, x, y))){
                        //         if(chk != 2){
                        //             printf(RED"Please enter two integers\n"WHITE);
                        //             while(getchar() != '\n');
                        //         }
                        //         else if(chk2){
                        //             printf(RED"Please enter a valid coordinate that among 3 pieces\n"WHITE);
                        //         }
                        //         else if(chk3){
                        //             printf(RED"Please enter an unoccupied land\n"WHITE);
                        //         }
                        //         else if(chk4){
                        //             printf(RED"Please enter a land that connect to other building\n"WHITE);
                        //         }
                        //     }

                        //     //build settlement
                        //     for(int k = 0; k < LAND_NUM; k++){
                        //         if(landbetweens[k]->p.x == x && landbetweens[k]->p.y == y){
                        //             landbetweens[k]->building = SETTLEMENT;
                        //             landbetweens[k]->owner = reverse_turn[i];
                        //             landbetweens[k]->has_building = true;
                        //             printf("You have built a settlement at (%d, %d)\n", x, y);
                        //             break;
                        //         }
                        //     }

                        //     render_map(renderer, map);

                        //     for(int k = 0; k < PIECE_NUM; k++){
                        //         POINT_AROUND_PIECE(around, pieces[k]->p.x, pieces[k]->p.y, 1);
                        //         for(int l = 0; l < 6; l++){
                        //             if(around[l].x == x && around[l].y == y){
                        //                 int resource_type = pieces[k]->eco_type;
                        //                 players[j]->resource[resource_type] += 1;
                        //                 resource[resource_type] -= 1;     
                        //             }
                        //         }
                        //     }

                        //     int cho_num = 0, cho;
                        //     point sta[3] = {{0, 0}, {0, 0}, {0, 0}}, end[3] = {{0, 0}, {0, 0}, {0, 0}};
                        //     for(int k = 0; k < ROAD_NUM; k++){
                        //         if( (roads[k]->start.x == x && roads[k]->start.y == y) || (roads[k]->end.x == x && roads[k]->end.y == y)){
                        //             sta[cho_num] = roads[k]->start;
                        //             end[cho_num] = roads[k]->end;
                        //             cho_num++;
                        //             printf("Road %d: (%d, %d) -> (%d, %d)\n", cho_num, roads[k]->start.x, roads[k]->start.y, roads[k]->end.x, roads[k]->end.y);
                        //         }
                        //     }
                        //     printf("Please enter the number of roads above to choose a road to build\n");
                        //     while((chk = scanf("%d", &cho)) != 1 || cho < 1 || cho > cho_num){
                        //         if(chk != 1){
                        //             printf(RED"Please enter an integer\n"WHITE);
                        //             while(getchar() != '\n');
                        //         }
                        //         else{
                        //             printf(RED"Please enter a valid number\n"WHITE);
                        //         }
                        //     }
                        //     //build road
                        //     for(int k = 0; k < ROAD_NUM; k++){
                        //         if(roads[k]->start.x == sta[cho - 1].x && roads[k]->start.y == sta[cho - 1].y && roads[k]->end.x == end[cho - 1].x && roads[k]->end.y == end[cho - 1].y){
                        //             roads[k]->owner = reverse_turn[i];
                        //             printf("You have built a road at (%d, %d) -> (%d, %d)\n", roads[k]->start.x, roads[k]->start.y, roads[k]->end.x, roads[k]->end.y);
                        //             break;
                        //         }
                        //     }

                        //     render_map(renderer, map);
                        // }
                        // else{
                            start_build(map, players[j]->id, renderer);
                            render_map(renderer, map);
                        // }
                    }
                }
            }

            isBuildInitalSettle = true;
        }

        while(1){
            most_knight_check(renderer, map);
            longest_road_check(renderer, map);
            if(victory_check(map) != 5){
                printf("Player %d win!\n\n", victory_check(map));
                return 0;
            }

            print_player(map);
            for(int i = 0; i < PLAYER_NUM; i++){   
                int id = players[i]->id;
                printf("\nPlayer %d turn...\n", id);

                //roll dice and take resources
                int dice = roll_dice();
                printf("Player %d rolls %d points\n", id, dice);
                if(dice == 7){
                    robber_situation(map, id, renderer);
                    render_map(renderer, map);
                }
                else take_resource(dice, map, resource, id);
                render_map(renderer, map);
                int select = 0;
                while(1){
                    most_knight_check(renderer, map);
                    longest_road_check(renderer, map);
                    if(victory_check(map) != 5){
                        printf("Player %d win!\n\n", victory_check(map));
                        return 0;
                    }
                    if(id == 1){
                        printf("Input:\t0 to exit \n\t1 to enter trade action \n\t2 to enter build action \n\t3 to enter developement card action \n\t4 to view the infomation of all players \n");
                        printf("action:\t");
                        if(scanf("%d", &select)  != 1){
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF);
                            continue;
                        }
                        printf("\n");
                        if(select == 0){
                            printf("Exit. \n\n");
                            most_knight_check(renderer, map);
                            longest_road_check(renderer, map);
                            break;
                        }
                        else if(select == 1){ // trade
                            trade_action( map, id );
                        }
                        else if(select == 2){ // build
                            if(build_action(renderer, map, id) == -1) continue;
                        }
                        else if(select == 3){ // card
                            dev_card_action( renderer, map, id );
                        }
                        else if(select == 4){ // card
                            print_player( map );
                        }
                    }
                    else{
                        //ai select action
                        if(build_action(renderer, map, id) == -1) continue;
                        dev_card_action( renderer, map, id );

                        select = random() % 4;
                        if(select == 1 && (random() % 100) < 50) continue;
                        if(select == 0){
                            most_knight_check(renderer, map);
                            longest_road_check(renderer, map);
                            break;
                        }
                        else if(select == 1){ // trade
                            trade_action( map, id );
                        }
                        else if(select == 2){ // build
                            if(build_action(renderer, map, id) == -1) continue;
                        }
                        else if(select == 3){ // card
                            dev_card_action( renderer, map, id );
                        }
                    }
                    most_knight_check(renderer, map);
                    longest_road_check(renderer, map);
                    if(victory_check(map) != 5){
                        printf("Player %d win!\n\n", victory_check(map));
                        return 0;
                    }
                }
                most_knight_check(renderer, map);
                longest_road_check(renderer, map);
                if(victory_check(map) != 5){
                    printf("Player %d win!\n\n", victory_check(map));
                    return 0;
                }
            }
            most_knight_check(renderer, map);
            longest_road_check(renderer, map);
            if(victory_check(map) != 5){
                printf("Player %d win!\n\n", victory_check(map));
                return 0;
            }
            sleep(2);
        }
        break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free_player(players);
    free_piece(pieces);
    free_landbetween(landbetweens);
    free_road(roads);
    free_devcard(devcards);
    free(map);

    return 0;
}
