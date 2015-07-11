#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <ncurses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "classes.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int CELL_SIZE = 64;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;


void ApplySurface(int x, int y, SDL_Texture *tex)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer, tex, NULL, &pos);
}

int rSize;
cell Platform[16][16];
terrain block [12];
cWeapon Weapon[5];
cHero Hero;
cMonster Monster[12];

void LoadHero()
{
    int i;
    ifstream HeroInput("Hero.sav");
    string Label;
    HeroInput >> Label;
    Hero.Dead = false;
    Hero.AllowAttackTexture = false;
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
        // printw("Hero loaded.\n");
        // Hero.Show(Weapon);
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
        lvl = rand() % 10 - 3 + Hero.Level;
        if(lvl < 1)
        {
            lvl = 1;
        }
        strength = 1;
        exp = 200*(lvl / Hero.Level);
        gld = lvl * 100;
        dmg = lvl * 50;
        armor = lvl * 4;
        magRes = lvl;
        Monster[i].putMonster(lvl, strength, exp, gld, dmg, 0, armor, magRes);
        Monster[i].Dead = true;
    }
}

void Render(cell* ptr, int rSize, SDL_Texture* texEmptyCell[], SDL_Texture* texHeroStandby, SDL_Texture* texHeroAttack, SDL_Texture* texMonster, SDL_Texture* texPit, SDL_Texture* texRock)
{
    SDL_RenderClear(renderer);
    fLog << "Render cleared and ready for battle!" << endl;
    int i, j;
    for(i=0; i<rSize; i++)
    {
        for(j=0; j<rSize; j++)
        {
            ApplySurface(j*CELL_SIZE, i*CELL_SIZE, texEmptyCell[(*(ptr + i*16 + j)).Texture]);
            if((*(ptr + i*16 + j)).tType == PIT)
            {
                ApplySurface(j*CELL_SIZE, i*CELL_SIZE, texPit);
            }
            else
            {
                if((*(ptr + i*16 + j)).tType == ROCK)
                {
                    ApplySurface(j*CELL_SIZE, i*CELL_SIZE, texRock);
                }
                else
                {
                    switch ((*(ptr + i*16 + j)).eType)
                    {
                        case HERO:
                            if(Hero.AllowAttackTexture)
                            {
                                ApplySurface(j*CELL_SIZE, i*CELL_SIZE, texHeroAttack);
                            }
                            else
                            {
                                ApplySurface(j*CELL_SIZE, i*CELL_SIZE, texHeroStandby);
                            }
                            break;
                        case MONSTER:
                            ApplySurface(j*CELL_SIZE, i*CELL_SIZE, texMonster);
                            break;
                        default: break;
                    }
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void room_generator(int N)
{
    int dice;
    int x, y;
    int i;
    int j;

    // Генерация героя
    Hero.x = 0;
    Hero.y = 0;
    Platform[0][0].eType = HERO;
    Platform[0][0].eID = 0;

    // выбор текстур пола
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            dice = rand() % 90;
            if(dice < 30)
            {
                Platform[i][j].Texture = 0;
            }
            else
            {
                if(dice < 30)
                {
                    Platform[i][j].Texture = 1;
                }
                else
                {
                    Platform[i][j].Texture = 2;
                }
            }
        }
    }

    // Генерация ландшафта
    i = 0;
    while(i < N)
    {
        dice = rand() % 2;
        x = rand() % 8;
        y = rand() % 8;
        if((Hero.x < x-2) || (Hero.x > x+2) || (Hero.y < y-2) || (Hero.y > y+2) && (Platform[x][y].tType == PLANE))
        {
            if(dice == 1)
            {
                Platform[y][x].tType = ROCK;
                Platform[y][x].value = rand() % 10000 + 10000;
                i++;
            }
            else
            {
                Platform[y][x].tType = PIT;
                Platform[y][x].value = rand() % 10000 + 10000;
                i++;
            }
        }
    }

    // Генерация монстров
    i = 0;
    while(i < N)
    {
        x = rand() % 8;
        y = rand() % 8;
        if((Hero.x < x-2) || (Hero.x > x+2) || (Hero.y < y-2) || (Hero.y > y+2) && (Platform[x][y].tType == PLANE) && (Platform[x][y].eType == NONE))
        {
            Monster[i].Dead = false;
            Monster[i].x = x;
            Monster[i].y = y;
            Platform[y][x].eType = MONSTER;
            Platform[y][x].eID = i;
            i++;
        }
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
    fLog << "Start!" << endl;
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fLog << "At initialization of SDL2: " << SDL_GetError() << endl;
    }
    fLog << "Render intialized!" << endl;
    window = SDL_CreateWindow("LoL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        fLog << "At window creation: " << SDL_GetError() << endl;
    }
    fLog << "Window intialized!" << endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr)
    {
        fLog << "At renderer creation: " << SDL_GetError() << endl;
    }
    fLog << "Render intialized!" << endl;
    SDL_Texture *texEmptyCell[3];
    texEmptyCell[0] = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/EmptyCell00.png");
    texEmptyCell[1] = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/EmptyCell01.png");
    texEmptyCell[2] = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/EmptyCell02.png");
    SDL_Texture *texHeroStandby = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/HeroStandby.png");
    SDL_Texture *texHeroAttack = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/HeroAttack.png");
    SDL_Texture *texMonster = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/Monster.png");
    SDL_Texture *texPit = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/Pit.png");
    SDL_Texture *texRock = IMG_LoadTexture(renderer, "/home/avallach/Документи/Workspace/RPG/bin/Debug/textures/Rock.png");
    fLog << "Textures loaded!" << endl;
    SDL_Event MainEvent;
    GenerateMeleeWeapons();
    fLog << "Weapons created!" << endl;
    LoadHero();
    fLog << "Hero loaded!" << endl;
    MonsterGenerator();
    fLog << "Monsters created!" << endl;
    ofstream fLogMonster("monsters.log");
    int i;
    for(i = 0; i < 12; i++)
    {
        fLogMonster << Monster[i].HealthPower << endl;
    }
    fLogMonster.close();
    rSize = 8;
    cell *ptrPlatform;
    ptrPlatform = &Platform[0][0];
    room_generator(rSize);
    fLog << "Room generated!" << endl;
    Render(ptrPlatform, rSize, texEmptyCell, texHeroStandby, texHeroAttack, texMonster, texPit, texRock);
    fLog << "First rendering successful!" << endl;
    SDL_Scancode AttackKey;
    SDL_Scancode MoveKey;
    bool Quit = false;
    do
    {
        bool Moved = false;
        bool Pressed = false;
        while(!Moved && Quit == false)
        {
            while(SDL_PollEvent(&MainEvent))
            {
                if(MainEvent.type == SDL_QUIT)
                {
                    Quit = true;
                }
                if(MainEvent.key.type == SDL_KEYDOWN)
                {
                    MoveKey = MainEvent.key.keysym.scancode;
                    Pressed = false;
                }
                if(MainEvent.key.type == SDL_KEYUP)
                {
                    Pressed = true;
                }
                if(Pressed)
                {
                    switch(MoveKey)
                    {
                        case SDL_SCANCODE_UP:// code for arrow up
                            Moved = Hero.Move(ptrPlatform, rSize, UP);
                            fLog << "Moved up!" << endl;
                            break;
                        case SDL_SCANCODE_DOWN:// code for arrow down
                            Moved = Hero.Move(ptrPlatform, rSize, DOWN);
                            fLog << "Moved down!" << endl;
                            break;
                        case SDL_SCANCODE_RIGHT:// code for arrow right
                            Moved = Hero.Move(ptrPlatform, rSize, RIGHT);
                            fLog << "Moved right!" << endl;
                            break;
                        case SDL_SCANCODE_LEFT:// code for arrow left
                            Moved = Hero.Move(ptrPlatform, rSize, LEFT);
                            fLog << "Moved left!" << endl;
                            break;
                        case SDL_SCANCODE_SPACE:
                            Moved = true;
                            fLog << "Move missed!" << endl;
                            break;
                        default: break;
                    }
                }
            }
        }//spell
        Hero.AllowAttackTexture = true;
        Render(ptrPlatform, rSize, texEmptyCell, texHeroStandby, texHeroAttack, texMonster, texPit, texRock);
        bool Attacked = false;
        Pressed = false;
        while(!Attacked && !Quit)
        {
            while(SDL_PollEvent(&MainEvent))
            {
                if(MainEvent.type == SDL_QUIT)
                {
                    Quit = true;
                }
                if(MainEvent.key.type == SDL_KEYDOWN)
                {
                    AttackKey = MainEvent.key.keysym.scancode;
                    Pressed = false;
                }
                if(MainEvent.key.type == SDL_KEYUP)
                {
                    Pressed = true;
                }
                if(Pressed)
                {
                    switch(AttackKey)
                    {
                        case SDL_SCANCODE_UP:// code for arrow up
                            Attacked = Hero.Attack(ptrPlatform, rSize, UP, Weapon, Monster);
                            fLog << "Attack up!" << endl;
                            break;
                        case SDL_SCANCODE_DOWN:// code for arrow down
                            Attacked = Hero.Attack(ptrPlatform, rSize, DOWN, Weapon, Monster);
                            fLog << "Attack down!" << endl;
                            break;
                        case SDL_SCANCODE_RIGHT:// code for arrow right
                            Attacked = Hero.Attack(ptrPlatform, rSize, RIGHT, Weapon, Monster);
                            fLog << "Attack right!" << endl;
                            break;
                        case SDL_SCANCODE_LEFT:// code for arrow left
                            Attacked = Hero.Attack(ptrPlatform, rSize, LEFT, Weapon, Monster);
                            fLog << "Attack left!" << endl;
                            break;
                        case SDL_SCANCODE_SPACE:
                            Attacked = true;
                            fLog << "Attack canceled!" << endl;
                            break;
                        default: break;
                    }
                }
            }
        }
        Hero.AllowAttackTexture = false;
        Render(ptrPlatform, rSize, texEmptyCell, texHeroStandby, texHeroAttack, texMonster, texPit, texRock);
    }while(Platform[rSize - 1][rSize - 1].eType != HERO && Quit == false);
    for(i = 0; i < 3; i++);
    {
        SDL_DestroyTexture(texEmptyCell[i]);
    }
    SDL_DestroyTexture(texHeroStandby);
    SDL_DestroyTexture(texHeroAttack);
    SDL_DestroyTexture(texMonster);
    SDL_DestroyTexture(texPit);
    SDL_DestroyTexture(texRock);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    fLog << "Finish!" << endl;
    fLog.close();
}
