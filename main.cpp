#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "room.h"
#include "units.h"
#include "weapon.h"

using namespace std;

void Render(cell* ptrPlatform, int rSize);

int main()
{
    int i, j;
    int room_size;
    srand(time(NULL));
    room_size = rand() % 9 + 8;
    cell platforms[room_size][room_size], *ptrPlatform;
    cell *y_line[room_size];
    for (i=0; i< room_size; i++)
    {
        y_line[i] = &platforms[i][0];
    }
    room_generator(y_line, room_size);
    ptrPlatform = &platforms[0][0];
    Render(ptrPlatform, room_size);
}

void Render(cell* ptrPlatform, int rSize)
{
    int i, j;
    for(i=0; i<rSize; i++)
    {
        for(j=0; j<rSize; j++)
        {
            if((*(ptrPlatform + i*j + j)).pit == 1)
            {
                printf("[O]");
            }
            else
            {
                if((*(ptrPlatform + i*j + j)).rock == 1)
                {
                    printf("[W]");
                }
                else
                {
                    printf("[ ]");
                }
            }
        }
        printf("\n");
    }
}
