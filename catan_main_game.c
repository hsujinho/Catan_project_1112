#include "catan.h"
#include "color.h"

int main(){
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

    return 0;
}