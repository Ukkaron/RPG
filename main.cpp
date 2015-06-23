#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include <string.h>

#include "classes.h"
#include "functions.h"

using namespace std;


int rSize;
cell platform[16][16];
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
    cell *ptrPlatform;
    ptrPlatform = &platform[0][0];
    tGenerator(ptrPlatform, rSize, Hero.x, Hero.y);
    eGenerator(ptrPlatform, rSize); // Я переделаю в eGenerator
    Render(ptrPlatform, rSize); // ЧТО ЭТО ТАКОЕ ? Посмотри 125 строчку в функциях и выбери какой-то
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
                    Moved = Hero.Move(ptrPlatform, rSize, UP);
                    break;
                case 2:
                    // code for arrow down
                    Moved = Hero.Move(ptrPlatform, rSize, DOWN);
                    break;
                case 5:
                    // code for arrow right
                    Moved = Hero.Move(ptrPlatform, rSize, RIGHT);
                    break;
                case 4:
                    // code for arrow left
                    Moved = Hero.Move(ptrPlatform, rSize, LEFT);
                    break;
                case 27:
                    Moved = true;
            }
            system("cls");
            Render(ptrPlatform, rSize);
        }
        while(Moved == false);
        system("cls");
        Render(ptrPlatform, rSize);
        //spell
        system("cls");
        Render(ptrPlatform, rSize);
    }while(platform[rSize - 1][rSize - 1].eType != HERO);
}
