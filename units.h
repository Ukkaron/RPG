#include <string.h>
#include "weapon.h"

enum Arrow {UP, DOWN, LEFT, RIGHT};

using namespace std;

class Entity
{
  public: int ID;
  public: char Name[50];
  public: int Level;
  public: int HealthPower;
  public: int Armor;
  public: int MagicResistance;
  public: int Experience;
  public: int Gold;
  public: int x;
  public: int y;
};

class cMonster: public Entity
{
    public: int DamagePhysical;
    public: int DamageMagic;
    public: void putMonster(int lvl, int strength, int exp, int gld, int DmgPh, int DmgMg, int Arm, int MgRes);
};

void cMonster::putMonster(int lvl, int strength, int exp, int gld, int DmgPh, int DmgMg, int Arm, int MgRes)
{
    Level = lvl;
    HealthPower = lvl*75*strength;
    Experience = exp;
    Gold = gld;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    Armor = Arm;
    MagicResistance = MgRes;
}

cMonster Monster[4];

class cHero: public Entity
{
    public: int ManaPool;
    public: int WeaponID;
    public: int ArtifactID[6];
    public: int SkillID[4];
    public: void Show();
    public: void Save();
    public: bool Move(cell* ptrFlat, Arrow Key);
};

void cHero::Show()
{
    printw("Hero %s \n", Name);
    printw("Level: %d \n", Level);
    printw("Health power: %d \n", HealthPower);
    printw("Mana: %d \n", ManaPool);
    printw("Gold: %d \n", Gold);
    char Current[50];
    strcpy(Current, Sword[WeaponID].Name.c_str());
    printw("Weared weapon: %s \n", Current);
}
void cHero::Save()
{
    ofstream HeroOutput("Hero.sav");
    int i;
    HeroOutput << "#hero: " << Name << " " << Experience;
    HeroOutput << " " << Gold << " " << WeaponID;
    for(i = 0; i < 6; i++)
    {
        HeroOutput << " " << ArtifactID[i];
    }
    for(i = 0; i < 6; i++)
    {
        HeroOutput << " " << SkillID[i];
    }
}
bool cHero::Move(cell* ptrFlat, DirKey Key)
{
    switch(Key)
    {
        case UP:
            if(y > 0 && IsEmpty((ptrFlat + y*16 - 16 + x)) == true)
            {
                (*(ptrFlat + y*16 - 16 + x)).EntityType.EntityID = 0;
                (*(ptrFlat + y*16 - 16 + x)).EntityType.Type = HERO;
                (*(ptrFlat + y*16 + x)).EntityType.EntityID = -1;
                (*(ptrFlat + y*16 + x)).EntityType.Type = NONE;
                y--;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case DOWN:
            if(y < rSize && IsEmpty((ptrFlat + y*16 + 16 + x)) == true)
            {
                (*(ptrFlat + y*16 + 16 + x)).EntityType.EntityID = 0;
                (*(ptrFlat + y*16 + 16 + x)).EntityType.Type = HERO;
                (*(ptrFlat + y*16 + x)).EntityType.EntityID = -1;
                (*(ptrFlat + y*16 + x)).EntityType.Type = NONE;
                y++;
                return true;
            }
            {
                return false;
            }
            break;
        case LEFT:
            if(x > 0 && IsEmpty((ptrFlat + y*16 + x - 1)) == true)
            {
                (*(ptrFlat + y*16 + x - 1)).EntityType.EntityID = 0;
                (*(ptrFlat + y*16 + x - 1)).EntityType.Type = HERO;
                (*(ptrFlat + y*16 + x)).EntityType.EntityID = -1;
                (*(ptrFlat + y*16 + x)).EntityType.Type = NONE;
                x--;
                return true;
            }
            {
                return false;
            }
            break;
        case RIGHT:
            if(x < rSize && IsEmpty((ptrFlat + y*16 + x + 1)) == true)
            {
                (*(ptrFlat + y*16 + x + 1)).EntityType.EntityID = 0;
                (*(ptrFlat + y*16 + x + 1)).EntityType.Type = HERO;
                (*(ptrFlat + y*16 + x)).EntityType.EntityID = -1;
                (*(ptrFlat + y*16 + x)).EntityType.Type = NONE;
                x++;
                return true;
            }
            {
                return false;
            }
            break;
    }
    return false;
}

cHero Hero;

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
    for(i = 0; i < 4; i++)
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
