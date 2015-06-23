#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <ncurses.h>

#include "classes.h"
#include "functions.h"

using namespace std;

void Render();
void RoomPreGenerator();

int rSize;
cell platforms[16][16];

int main()
{
    char Current;
    WINDOW* CurrentWindow;
    CurrentWindow = initscr();
    keypad(stdscr, true);
    GenerateMeleeWeapons();
    GenerateHero();
    printw("Press S to start");
    do
        Current = getch();
    while(Current != 's');
    clear();
    srand(time(NULL));
    rSize = rand() % 9 + 8;
    cell *ptrPlatforms;
    ptrPlatforms = &platforms[0][0];
    RoomPreGenerator();
    room_generator(ptrPlatforms, rSize);
    Render();
        bool Moved;
    do
    {
        do
        {
            Moved = false;
            Current = getch();
            switch((int)Current)
            {
                case 3:
                    // code for arrow up
                    Moved = Hero.Move(ptrPlatforms, rSize, UP);
                    break;
                case 2:
                    // code for arrow down
                    Moved = Hero.Move(ptrPlatforms, rSize, DOWN);
                    break;
                case 5:
                    // code for arrow right
                    Moved = Hero.Move(ptrPlatforms, rSize, RIGHT);
                    break;
                case 4:
                    // code for arrow left
                    Moved = Hero.Move(ptrPlatforms, rSize, LEFT);
                    break;
                case 27:
                    Moved = true;
            }
            clear();
            Render();
        }
        while(Moved == false);
        clear();
        Render();
        //spell
        clear();
        Render();
    }while(platforms[rSize - 1][rSize - 1].EntityType.Type != HERO);
    endwin();
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
                printw("[O]");
            }
            else
            {
                if(platforms[i][j].rock == 1)
                {
                    printw("[W]");
                }
                else
                {
                    switch (platforms[i][j].EntityType.Type)
                    {
                        case HERO:
                            printw("[H]");
                            break;
                        case MONSTER:
                            printw("[A]");
                            break;
                        case NONE:
                            printw("[ ]");
                            break;
                    }
                }
            }
        }
        printw("\n");
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
