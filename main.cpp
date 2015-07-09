#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <ncurses.h>

#include "classes.h"

using namespace std;


int rSize;
cell platform[16][16];
terrain block [12];
cWeapon Weapon[5];
cHero Hero;
cMonster Monster[12];

void GenerateHero()
{
    int i;
    ifstream HeroInput("Hero.sav");
    string Label;
    HeroInput >> Label;
    if(Label == "#hero:")
    {
        HeroInput >> Hero.Name;
        Hero.ID = 0;
        HeroInput >> Hero.Experience;
        Hero.Level = Hero.Experience / 1000;
        Hero.HealthPower = Hero.Level * 100;
        Hero.ManaPool = Hero.Level * 150;
        Hero.Armor = Hero.Level * 5;
        Hero.MagicResistance = Hero.Level * 2;
        HeroInput >> Hero.Gold;
        HeroInput >> Hero.WeaponID;
        for(i = 0; i < 6; i++)
        {
            HeroInput >> Hero.ArtifactID[i];
        }
        for(i = 0; i < 4; i++)
        {
            HeroInput >> Hero.SkillID[i];
        }
        printw("Hero loaded.\n");
        Hero.Show(Weapon);
    }
    else
    {
        printw("Enter the name of your hero: ");
        cin >> Hero.Name;
        Hero.Experience = 1000;
        Hero.Level = Hero.Experience / 1000;
        Hero.HealthPower = Hero.Level * 100;
        Hero.ManaPool = Hero.Level * 150;
        Hero.Armor = Hero.Level * 5;
        Hero.MagicResistance = Hero.Level * 2;
        Hero.Gold = 1000;
    }
    HeroInput.close();
}

void MonsterGenerator()
{
    int lvl;
    int strength;
    int exp;
    int gld;
    int dmg;
    int armor;
    int magRes;
    int i;
    for(i = 0; i < 12; i++)
    {
        lvl = rand() % 10 - 5 + Hero.Level;
        if(lvl < 1)
        {
            lvl = 1;
        }
        strength = 1;
        exp = lvl * 1000;
        gld = lvl * 100;
        dmg = lvl * 50;
        armor = lvl * 4;
        magRes = lvl;
        Monster[i].putMonster(lvl, strength, exp, gld, dmg, 0, armor, magRes);
    }
}

void Render(cell* ptr, int rSize)
{
    int i, j;
    for(i=0; i<rSize; i++)
    {
        for(j=0; j<rSize; j++)
        {
            if((*(ptr + i*16 + j)).tType == PIT)
            {
                printw("[O]");
            }
            else
            {
                if((*(ptr + i*16 + j)).tType == ROCK)
                {
                    printw("[W]");
                }
                else
                {
                    switch ((*(ptr + i*16 + j)).eType)
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

void eGenerator(cell* ptr, int rSize)
{
    int i;
    int x;
    int y;
    (*ptr).eType = HERO;
    (*ptr).eID = 0;
    for(i = 0; i < (rSize*0.75); i++)
    {
        do
        {
            x = rand() % rSize;
            y = rand() % rSize;

        }while((*(ptr + y*16 + x)).tType != PLANE  || (*(ptr + y*16 + x)).eType != NONE);
        (*(ptr + y*16 + x)).eType = MONSTER;
        (*(ptr + y*16 + x)).eID = i;
        Monster[i].x = x;
        Monster[i].y = y;
    }
}

void GenerateMeleeWeapons()
{
    Weapon[0].putWeapon(0, "Sword of Zephyr", 50, 10, 0, 1500, 1);
    Weapon[1].putWeapon(1, "Iron Sword", 35, 0, 0, 300, 1);
    Weapon[2].putWeapon(2, "Steel Sword", 50, 0, 0, 700, 1);
    Weapon[3].putWeapon(3, "Mithril Sword", 40, 0, 20, 3000, 1);
}

int main()
{
    char Current;
    bool Moved;
    initscr();
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
    cell *ptrPlatform;
    ptrPlatform = &platform[0][0];
    eGenerator(ptrPlatform, rSize); // Я переделаю в eGenerator
    Render(ptrPlatform, rSize); // ЧТО ЭТО ТАКОЕ ? Посмотри 125 строчку в функциях и выбери какой-то
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
            clear();
            Render(ptrPlatform, rSize);
        }
        while(Moved == false);
        clear();
        Render(ptrPlatform, rSize);
        //spell
        clear();
        Render(ptrPlatform, rSize);
    }while(platform[rSize - 1][rSize - 1].eType != HERO);
    endwin();
}
