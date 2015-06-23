#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <conio.h>

#include "classes.h"
#include "functions.h"

using namespace std;


int rSize;
cell platforms[16][16];
terrain block [12];

int main()
{
    char Current;
    bool Moved;
    keypad(stdscr, true);
    GenerateMeleeWeapons();
    GenerateHero();
    printw("Press S to start");
    do
        Current = _getch();
    while(Current != 's');
    system("cls");
    srand(time(NULL));
    rSize = rand() % 9 + 8;
    cell *ptrPlatforms;
    ptrPlatforms = &platforms[0][0];
    tGenerator(ptrPlatforms, rSize, Hero.x, Hero.y);
    eGenerator(); // Я переделаю в eGenerator
    Render(); // ЧТО ЭТО ТАКОЕ ? Посмотри 125 строчку в функциях и выбери какой-то
    do
    {
        do
        {
            Moved = false;
            Current = _getch();
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
