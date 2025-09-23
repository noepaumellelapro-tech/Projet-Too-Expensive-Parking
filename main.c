#include <stdio.h>
#include <ncurses.h>
#include "map.h"

int main(void)
{
    char Map [MAX_ROWS][MAX_COLS];
    //affichage_graphique();
   read_map("Map_1.txt", Map);
  
    return 0;
}