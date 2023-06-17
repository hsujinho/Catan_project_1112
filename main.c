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
                start_build(map, id, renderer);
                render_map(renderer, map);
            }
            //setting second settlement
            for(int i = 0; i < PLAYER_NUM; i++){
                for(int j = 0; j < PLAYER_NUM; j++){
                    if(reverse_turn[i] == players[j]->id){
                        start_build(map, players[j]->id, renderer);
                        render_map(renderer, map);
                    }
                }
            }
            isBuildInitalSettle = true;
        }

        for(int i = 0; i < PLAYER_NUM; i++){
            sleep(2);   
            int id = players[i]->id;
            int dice = roll_dice();
            printf("Player %d rolls %d points\n", id, dice);
            take_resource(dice, map, resource, id);


            build_action(renderer, map, id);
        }
        
        scanf(" ");
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