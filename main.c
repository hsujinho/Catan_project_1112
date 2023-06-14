#include "catan.h"
#include "color.h"

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
    // printf("Welcome to Catan!\n");

    //declare variables

    player **players = NULL;
    piece **pieces = NULL;
    landbetween **landbetweens = NULL;
    road **roads = NULL;
    struct list_head *devcards = NULL;
    mapInfo *map = malloc(sizeof(mapInfo));
    int first_id = map->players[0]->id;

    //initialize variables
    init_game(&pieces, &landbetweens, &roads, &players, &devcards);
    map->players = players;
    map->pieces = pieces;
    map->lands = landbetweens;
    map->roads = roads;

    //init SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *window = SDL_CreateWindow("Catan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //render map
    render_map(renderer, map);

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
                if(id == 1){
                    printf("Please choose your initial building\n");

                    printf("please enter the x and y coordinate of the point to build your first settlement\n");
                    int x, y, chk, chk2, chk3, chk4;
                    while( (chk = scanf("%d %d", &x, &y)) != 2 || (chk2 = !is_in_three_pieces_lands_pos(x, y)) || (chk3 = is_land_occupied(map, x, y, id)) || (chk4 = is_land_connect_other_building(map, x, y))){
                        if(chk != 2){
                            printf(RED"Please enter two integers\n"WHITE);
                            while(getchar() != '\n');
                        }
                        else if(chk2){
                            printf(RED"Please enter a valid coordinate that among 3 pieces\n"WHITE);
                        }
                        else if(chk3){
                            printf(RED"Please enter an unoccupied land\n"WHITE);
                        }
                        else if(chk4){
                            printf(RED"Please enter a land that connect to other building\n"WHITE);
                        }
                    }
                    //build settlement
                    for(int i = 0; i < LAND_NUM; i++){
                        if(landbetweens[i]->p.x == x && landbetweens[i]->p.y == y){
                            landbetweens[i]->building = SETTLEMENT;
                            landbetweens[i]->owner = id;
                            landbetweens[i]->has_building = true;
                            printf("You have built a settlement at (%d, %d)\n", x, y);
                            break;
                        }
                    }
                    render_map(renderer, map);
                    
                    //TODO: build road
                }
                else{
                    // TODO: let bot choose initial building
                }
            }

            for(int i = 0; i < PLAYER_NUM; i++){
                for(int j = 0; j < PLAYER_NUM; j++){
                    if(reverse_turn[i] == players[j]->id){
                        if(reverse_turn[i] == 1){
                            printf("Please choose your initial building\n");

                            printf("please enter the x and y coordinate of the point to build your second settlement\n");
                            int x, y, chk, chk2, chk3, chk4;
                            while( (chk = scanf("%d %d", &x, &y)) != 2 || (chk2 = !is_in_three_pieces_lands_pos(x, y)) || (chk3 = is_land_occupied(map, x, y, reverse_turn[i])) || (chk4 = is_land_connect_other_building(map, x, y))){
                                if(chk != 2){
                                    printf(RED"Please enter two integers\n"WHITE);
                                    while(getchar() != '\n');
                                }
                                else if(chk2){
                                    printf(RED"Please enter a valid coordinate that among 3 pieces\n"WHITE);
                                }
                                else if(chk3){
                                    printf(RED"Please enter an unoccupied land\n"WHITE);
                                }
                                else if(chk4){
                                    printf(RED"Please enter a land that connect to other building\n"WHITE);
                                }
                            }

                            //build settlement
                            for(int k = 0; k < LAND_NUM; k++){
                                if(landbetweens[k]->p.x == x && landbetweens[k]->p.y == y){
                                    landbetweens[k]->building = SETTLEMENT;
                                    landbetweens[k]->owner = reverse_turn[i];
                                    landbetweens[k]->has_building = true;
                                    printf("You have built a settlement at (%d, %d)\n", x, y);
                                    break;
                                }
                            }

                            render_map(renderer, map);

                            //TODO: build road
                            //TODO: take resources
                        }
                        else{
                            // TODO: let bot choose initial building
                        }
                    }
                }
            }

            isBuildInitalSettle = true;
        }

        for(int i = 0; i < PLAYER_NUM; i++){
            int id = players[i]->id;
            //roll dice and take resources
            int dice = roll_dice();
            // printf("Player %d rolls %d points\n", id, dice);
            // take_resource(dice, map, resource, first_id);
            if(id == 1){
                
            }
            else{

            }
        }
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