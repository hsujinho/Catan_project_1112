#include "render.h"

// SDL implement
void render_pieces(SDL_Renderer *renderer, mapInfo *map){
    //set background color
    SDL_SetRenderDrawColor(renderer, 130, 240, 255, 255);
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
    SDL_SetRenderDrawColor(renderer, 0, 206, 255, 255);
    SDL_RenderClear(renderer);

    if(season_flag){
        SDL_Surface *piece_surface = NULL;

        if(season_turn == SPRING)
            piece_surface = IMG_Load("picture/season/spring.png");
        else if(season_turn == SUMMER)
            piece_surface = IMG_Load("picture/season/summer.png");
        else if(season_turn == AUTUMN)
            piece_surface = IMG_Load("picture/season/autumn.png");
        else if(season_turn == WINTER)
            piece_surface = IMG_Load("picture/season/winter.png");

        SDL_Texture *piece_texture = SDL_CreateTextureFromSurface(renderer, piece_surface);
        SDL_Rect piece_rect = {600, 10, 100, 100};
        SDL_RenderCopy(renderer, piece_texture, NULL, &piece_rect);
        SDL_DestroyTexture(piece_texture);
        SDL_FreeSurface(piece_surface);
    }

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
            rob_surface = IMG_Load("picture/CreeperFace.png");
            SDL_Texture *rob_texture = SDL_CreateTextureFromSurface(renderer, rob_surface);
            SDL_Rect rob_rect = {x + NUM_OFFSET + PIECE_SIZE / 4, y + NUM_OFFSET, NUM_SIZE - PIECE_SIZE / 10, NUM_SIZE - PIECE_SIZE / 10};
            SDL_RenderCopy(renderer, rob_texture, NULL, &rob_rect);
            SDL_DestroyTexture(rob_texture);
            SDL_FreeSurface(rob_surface);
        }   
        

        SDL_FreeSurface(num_surface);   
    }

    for(int i = 0; i < ROAD_NUM; i++){
        int x, y;

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
        x = x + PIECE_SIZE / 2 - LAND_SIZE / 2 + CIRCLE_RAD;
        y = y + PIECE_SIZE / 2 - LAND_SIZE / 2 + CIRCLE_RAD;

        if(valid_point_mat[lands[i]->p.y][lands[i]->p.x] == TYPE_PORT_ANY)
            render_circle(renderer, x, y, CIRCLE_RAD, 255, 80, 255, ALPHA);
        else if(valid_point_mat[lands[i]->p.y][lands[i]->p.x] == TYPE_PORT_BRICK)
            render_circle(renderer, x, y, CIRCLE_RAD, 255, 86, 80, ALPHA);
        else if(valid_point_mat[lands[i]->p.y][lands[i]->p.x] == TYPE_PORT_LUMBER)
            render_circle(renderer, x, y, CIRCLE_RAD, 200, 98, 0, ALPHA);
        else if(valid_point_mat[lands[i]->p.y][lands[i]->p.x] == TYPE_PORT_WOOL)
            render_circle(renderer, x, y, CIRCLE_RAD, 210, 210, 210, ALPHA);
        else if(valid_point_mat[lands[i]->p.y][lands[i]->p.x] == TYPE_PORT_GRAIN)
            render_circle(renderer, x, y, CIRCLE_RAD, 246, 218, 0, ALPHA);
        else if(valid_point_mat[lands[i]->p.y][lands[i]->p.x] == TYPE_PORT_ORE)
            render_circle(renderer, x, y, CIRCLE_RAD, 104, 78, 56, ALPHA);
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


void render_circle(SDL_Renderer *renderer, int x, int y, int rad, int r, int g, int b, int a){
    //setting color 
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // draw circle and fill it with the color
    for(int i = 0; i < 360; i++){
        double angle = i * 3.1415926535 / 180;
        int x1 = x + rad * cos(angle);
        int y1 = y + rad * sin(angle);
        SDL_RenderDrawLine(renderer, x1, y1, x, y);
    }

    SDL_RenderCopy(renderer, NULL, NULL, NULL);
}


