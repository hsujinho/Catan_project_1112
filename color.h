#pragma once 

#include <stdio.h>

#define RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define BLACK "\033[0;30m"
#define WHITE "\033[0;37m"


#define PRINT_RED printf(RED)
#define PRINT_WHITE printf(WHITE)
#define PRINT_GREEN printf(GREEN)
#define PRINT_BLUE printf(BLUE)
#define PRINT_YELLOW printf(YELLOW)
#define PRINT_CYAN printf(CYAN)
#define PRINT_MAGENTA printf(MAGENTA)
#define PRINT_BLACK printf(BLACK)