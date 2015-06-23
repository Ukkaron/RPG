#ifndef FUNCTOINS_H
#define FUNCTIONS_H

bool IsEmpty(cell* ptr)
{
    if((*ptr).pit == false && (*ptr).rock == false)
    {
        if((*ptr).EntityType.Type == NONE)
        {
            return true;
        }
    }
    return false;
}

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
        Hero.Show();
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

void room_generator (cell *ptr, int n)
{
    int i;
    int x, y; // Переменные координаты
    bool dice; // Переменная кубика
    for(i=0; i<(n*0.75); i++)
    {
        x = rand() % (n-2) + 2;
        y = rand() % (n-2) + 2;
        dice = rand() % 2;
        if(dice == 1)
            (*(ptr + y*x + x)).pit = true;
        else
            (*(ptr + y*x + x)).rock = true;
    }
}

void Render(cell* ptr, int rSize)
{
    int i, j;
    for(i=0; i<rSize; i++)
    {
        for(j=0; j<rSize; j++)
        {
            if((*(ptr + i*16 + j)).pit == 1)
            {
                printw("[O]");
            }
            else
            {
                if((*(ptr + i*16 + j)).rock == 1)
                {
                    printw("[W]");
                }
                else
                {
                    switch ((*(ptr + i*16 + j)).EntityType.Type)
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

void RoomPreGenerator(cell* ptr, int rSize)
{
    int i;
    int j;
    int x;
    int y;
    for(i = 0; i < rSize; i++)
    {
        for(j = 0; j < rSize; j++)
        {
            (*(ptr + i*16 + j)).EntityType.Type = NONE;
            (*(ptr + i*16 + j)).EntityType.EntityID = -1;
        }
    }
    (*ptr).EntityType.Type = HERO;
    (*ptr).EntityType.EntityID = 0;
    for(i = 0; i < (rSize*0.75); i++)
    {
        do
        {
            x = rand() % rSize;
            y = rand() % rSize;

        }while((*(ptr + y*16 + x)).pit == true || (*(ptr + y*16 + x)).rock == true || (*(ptr + y*16 + x)).EntityType.Type != NONE);
        (*(ptr + y*16 + x)).EntityType.Type = MONSTER;
        (*(ptr + y*16 + x)).EntityType.EntityID = i;
        Monster[i].x = x;
        Monster[i].y = y;
    }
}

cWeapon Weapon[5];
void GenerateMeleeWeapons()
{
    Weapon[0].putWeapon(0, "Sword of Zephyr", 50, 10, 0, 1500, 1);
    Weapon[1].putWeapon(1, "Iron Sword", 35, 0, 0, 300, 1);
    Weapon[2].putWeapon(2, "Steel Sword", 50, 0, 0, 700, 1);
    Weapon[3].putWeapon(3, "Mithril Sword", 40, 0, 20, 3000, 1);
}

#endif
