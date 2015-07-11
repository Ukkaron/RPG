#ifndef CLASSES_H
#define CLASSES_H

#include <string.h>

using namespace std;

enum EntityType { NONE, MONSTER, HERO };
enum TerrainType { PLANE, PIT, ROCK };
enum DirKey {UP, DOWN, LEFT, RIGHT};

ofstream fLog("last.log");

class cell
{
    public:
        EntityType eType;
        TerrainType tType;
        int eID;
        int value;
        int Texture;
        cell()
        {
            eType = NONE;
            tType = PLANE;
            eID = -1;
            value = 0;
        }
};

bool IsEmpty(cell* ptr)
{
    if((*ptr).tType == false)
    {
        if((*ptr).eType == NONE)
        {
            return true;
        }
    }
    return false;
}

class terrain
{
    public:
        int id;
        int value; // Значение глебины, или количество ХП.
        int x, y;
};

class cWeapon
{
    public:
        int ID;
        string Name;
        int DamagePhysical;
        int DamageMagic;
        int DamageClear;
        int Price;
        int Range;
        void putWeapon(int wpnID, string wpnName, int DmgPh, int DmgMg, int DmgCl, int Prc, int Rng);
};

void cWeapon::putWeapon(int wpnID, string wpnName, int DmgPh, int DmgMg, int DmgCl, int Prc, int Rng)
{
    ID = wpnID;
    Name = wpnName;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    DamageClear = DmgCl;
    Price = Prc;
    Range = Rng;
}

class Entity
{
    public:
        int ID;
        bool Dead;
        char Name[50];
        int Level;
        int HealthPower;
        int Armor;
        int MagicResistance;
        int Experience;
        int Gold;
        int x;
        int y;
        DirKey Direction;
        bool AllowAttackTexture;
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

class cHero: public Entity
{
    public:
        int ManaPool;
        int WeaponID;
        int ArtifactID[6];
        int SkillID[4];
        void Show(cWeapon Weapon[]);
        void Save();
        bool Move(cell* ptrFlat, int rSize, DirKey Key);
        bool Attack(cell* ptrFlat, int rSize, DirKey Key, cWeapon Sword[], cMonster Monster[]);
};

void cHero::Show(cWeapon Weapon[])
{
    printw("Hero %s \n", Name);
    printw("Level: %d \n", Level);
    printw("Health power: %d \n", HealthPower);
    printw("Mana: %d \n", ManaPool);
    printw("Gold: %d \n", Gold);
    cout << Weapon[WeaponID].Name.c_str() << endl;
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
bool cHero::Move(cell* ptrFlat, int rSize, DirKey Key)
{
    switch(Key)
    {
        case UP:
            if(y > 0 && IsEmpty((ptrFlat + y*16 - 16 + x)) == true)
            {
                (*(ptrFlat + y*16 - 16 + x)).eID = 0;
                (*(ptrFlat + y*16 - 16 + x)).eType = HERO;
                (*(ptrFlat + y*16 + x)).eID = -1;
                (*(ptrFlat + y*16 + x)).eType = NONE;
                y--;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case DOWN:
            if(y < (rSize - 1) && IsEmpty((ptrFlat + y*16 + 16 + x)) == true)
            {
                (*(ptrFlat + y*16 + 16 + x)).eID = 0;
                (*(ptrFlat + y*16 + 16 + x)).eType = HERO;
                (*(ptrFlat + y*16 + x)).eID = -1;
                (*(ptrFlat + y*16 + x)).eType = NONE;
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
                (*(ptrFlat + y*16 + x - 1)).eID = 0;
                (*(ptrFlat + y*16 + x - 1)).eType = HERO;
                (*(ptrFlat + y*16 + x)).eID = -1;
                (*(ptrFlat + y*16 + x)).eType = NONE;
                x--;
                return true;
            }
            {
                return false;
            }
            break;
        case RIGHT:
            if(x < (rSize - 1) && IsEmpty((ptrFlat + y*16 + x + 1)) == true)
            {
                (*(ptrFlat + y*16 + x + 1)).eID = 0;
                (*(ptrFlat + y*16 + x + 1)).eType = HERO;
                (*(ptrFlat + y*16 + x)).eID = -1;
                (*(ptrFlat + y*16 + x)).eType = NONE;
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

ofstream Log("attack.log");
bool cHero::Attack(cell* ptrFlat, int rSize, DirKey Key, cWeapon Sword[], cMonster Monster[])
{
    int i;
    int j;
    int DealDamage;
    switch(Key)
    {
        case UP:
            if(y > 0)
            {
                for(i = 1; i <= Sword[WeaponID].Range; i++)
                {
                    if( (*(ptrFlat + (y - i)*16 + x)).eType == MONSTER )
                    {
                        j = (*(ptrFlat + (y - i)*16 + x)).eID;
                        DealDamage = Sword[WeaponID].DamagePhysical * (1 - Monster[j].Armor / 1000);
                        DealDamage += Sword[WeaponID].DamageMagic * (1 - Monster[j].MagicResistance / 1000);
                        DealDamage += Sword[WeaponID].DamageClear;
                        DealDamage *= Level;
                        Log << "> Monster HP before attack " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(!Monster[j].Dead)
                        {
                            if(Monster[j].HealthPower <= DealDamage)
                            {
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                                Experience += Monster[j].Experience / 10;
                                Level = Experience / 1000;
                                Gold += Monster[j].Gold;
                                Monster[j].Dead = true;
                                Monster[j].HealthPower = 0;
                            }
                            else
                            {
                                Monster[j].HealthPower -= DealDamage;
                            }
                            Log << "> Monster HP after attack " << Monster[j].HealthPower << endl;
                        }
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
            break;
        case DOWN:
            if(y < (rSize - 1))
            {
                for(i = 1; i <= Sword[WeaponID].Range; i++)
                {
                    if( (*(ptrFlat + (y + i)*16 + x)).eType == MONSTER)
                    {
                        j = (*(ptrFlat + (y + i)*16 + x)).eID;
                        DealDamage = Sword[WeaponID].DamagePhysical * (1 - Monster[j].Armor / 1000);
                        DealDamage += Sword[WeaponID].DamageMagic * (1 - Monster[j].MagicResistance / 1000);
                        DealDamage += Sword[WeaponID].DamageClear;
                        DealDamage *= Level;
                        Log << "> Monster HP before attack " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(!Monster[j].Dead)
                        {
                            if(Monster[j].HealthPower <= DealDamage)
                            {
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                                Experience += Monster[j].Experience / 10;
                                Level = Experience / 1000;
                                Gold += Monster[j].Gold;
                                Monster[j].Dead = true;
                                Monster[j].HealthPower = 0;
                            }
                            else
                            {
                                Monster[j].HealthPower -= DealDamage;
                            }
                            Log << "> Monster HP after attack " << Monster[j].HealthPower << endl;
                        }
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
            break;
        case LEFT:
            if(x > 0)
            {
                for(i = 1; i <= Sword[WeaponID].Range; i++)
                {
                    if( (*(ptrFlat + y*16 + x - i)).eType == MONSTER)
                    {
                        j = (*(ptrFlat + y*16 + x - i)).eID;
                        DealDamage = Sword[WeaponID].DamagePhysical * (1 - Monster[j].Armor / 1000);
                        DealDamage += Sword[WeaponID].DamageMagic * (1 - Monster[j].MagicResistance / 1000);
                        DealDamage += Sword[WeaponID].DamageClear;
                        DealDamage *= Level;
                        Log << "> Monster HP before attack " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(!Monster[j].Dead)
                        {
                            if(Monster[j].HealthPower <= DealDamage)
                            {
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                                Experience += Monster[j].Experience / 10;
                                Level = Experience / 1000;
                                Gold += Monster[j].Gold;
                                Monster[j].Dead = true;
                                Monster[j].HealthPower = 0;
                            }
                            else
                            {
                                Monster[j].HealthPower -= DealDamage;
                            }
                            Log << "> Monster HP after attack " << Monster[j].HealthPower << endl;
                        }
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
            break;
        case RIGHT:
            if(x < (rSize - 1))
            {
                for(i = 1; i <= Sword[WeaponID].Range; i++)
                {
                    if( (*(ptrFlat + y*16 + x + i)).eType == MONSTER)
                    {
                        j = (*(ptrFlat + y*16 + x + i)).eID;
                        DealDamage = Sword[WeaponID].DamagePhysical * (1 - Monster[j].Armor / 1000);
                        DealDamage += Sword[WeaponID].DamageMagic * (1 - Monster[j].MagicResistance / 1000);
                        DealDamage += Sword[WeaponID].DamageClear;
                        DealDamage *= Level;
                        Log << "> Monster HP before attack " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(!Monster[j].Dead)
                        {
                            if(Monster[j].HealthPower <= DealDamage)
                            {
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                                (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                                Experience += Monster[j].Experience / 10;
                                Level = Experience / 1000;
                                Gold += Monster[j].Gold;
                                Monster[j].Dead = true;
                                Monster[j].HealthPower = 0;
                            }
                            else
                            {
                                Monster[j].HealthPower -= DealDamage;
                            }
                            Log << "> Monster HP after attack " << Monster[j].HealthPower << endl;
                        }
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
            break;
    }
    return false;
}



#endif
