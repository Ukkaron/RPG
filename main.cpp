#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include "room.h"
#include "units.h"

using namespace std;

void Render();
void RoomPreGenerator();

int rSize;
cell platforms[16][16];

int main()
{
    GenerateMeleeWeapons();
    GenerateHero();
    srand(time(NULL));
    rSize = rand() % 9 + 8;
    cell *ptrPlatforms;
    ptrPlatforms = &platforms[0][0];
    room_generator(ptrPlatforms, rSize);
    RoomPreGenerator();
    Render();
}

void Render()
{
    int i, j;
    for(i=0; i<rSize; i++)
    {
        for(j=0; j<rSize; j++)
        {
            if(platforms[i][j].pit == 1)
            {
                printf("[O]");
            }
            else
            {
                if(platforms[i][j].rock == 1)
                {
                    printf("[W]");
                }
                else
                {
                    switch (platforms[i][j].EntityType.Type)
                    {
                        case HERO:
                            printf("[H]");
                            break;
                        case MONSTER:
                            printf("[A]");
                            break;
                        case NONE:
                            printf("[ ]");
                            break;
                    }
                }
            }
        }
        printf("\n");
    }
}

void RoomPreGenerator()
{
    int i;
    int j;
    for(i = 0; i < rSize; i++)
    {
        for(j = 0; j < rSize; j++)
        {
            platforms[i][j].EntityType.Type = NONE;
            platforms[i][j].EntityType.EntityID = -1;
        }
    }
    platforms[0][0].EntityType.Type = HERO;
    platforms[0][0].EntityType.EntityID = 0;
}
