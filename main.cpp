#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

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
    bool Moved;
    keypad(stdscr, true);
    GenerateMeleeWeapons();
    GenerateHero();
    printw("Press S to start");
    do
        Current = getch();
    while(Current != 's');
    system("cls");
    srand(time(NULL));
    rSize = rand() % 9 + 8;
    cell *ptrPlatforms;
    ptrPlatforms = &platforms[0][0];
    RoomPreGenerator();
    room_generator(ptrPlatforms, rSize);
    Render();
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
            system("cls");
            Render();
        }
        while(Moved == false);
        system("cls");
        Render();
        //spell
        system("cls");
        Render();
    }while(platforms[rSize - 1][rSize - 1].EntityType.Type != HERO);
}
