#include <stdio.h>
#include <ncurses.h>
#include "map.h"
#include "vehicule.h"
#include "random.h"

int main(void)
{
    char Map [MAX_ROWS][MAX_COLS];

  

   //read_map("Map_2.txt", Map);
   random_car();
  
    return 0;
}