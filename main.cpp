#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "room.h"
#include "units.h"

using namespace std;

int main()
{
    int i, j;
    int room_size;
    srand(time(NULL));
    room_size = rand() % 9 + 8;
    cell platforms[room_size][room_size];
    cell *y_line[room_size];
    for (i=0; i< room_size; i++)
    {
        y_line[i] = &platforms[i][0];
    }
    room_generator(y_line, room_size);
    for(i=0; i<room_size; i++)
    {
        for(j=0; j<room_size; j++)
        {
            if(platforms[j][i].pit == 1)
                printf("O");
            if(platforms[j][i].rock == 1)
                printf("W");
            else
                printf(" ");
        }
        printf("\n");
    }
}
