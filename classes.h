#ifndef CLASSES_H
#define CLASSES_H

using namespace std;

enum EntityType { NONE, MONSTER, HERO };
enum TerrainType { PLANE, PIT, ROCK };
enum DirKey {UP, DOWN, LEFT, RIGHT};

class cell
{
    public:
        EntityType eType;
        TerrainType tType;
        int eID;
        int tID;
        cell()
        {
            eType = NONE;
            tType = PLANE;
            eID = -1;
            tID = -1;
        }
};

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

class cHero: public Entity
{
    public: int ManaPool;
    public: int WeaponID;
    public: int ArtifactID[6];
    public: int SkillID[4];
    public: void Show();
    public: void Save();
    public: bool Move(cell* ptrFlat, int rSize, DirKey Key);
    public: bool Attack(cell* ptrFlat, int rSize, DirKey Key);
};

void cHero::Show()
{
    printf("Hero %s \n", Name);
    printf("Level: %d \n", Level);
    printf("Health power: %d \n", HealthPower);
    printf("Mana: %d \n", ManaPool);
    printf("Gold: %d \n", Gold);
    char Current[50];
    strcpy(Current, Weapon[WeaponID].Name.c_str());
    printf("Weared weapon: %s \n", Current);
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
            if(y < rSize && IsEmpty((ptrFlat + y*16 + 16 + x)) == true)
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
            if(x < rSize && IsEmpty((ptrFlat + y*16 + x + 1)) == true)
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
bool cHero::Attack(cell* ptrFlat, int rSize, DirKey Key)
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
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(Monster[j].HealthPower < DealDamage)
                        {
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                            Experience += Monster[j].Experience / 10;
                            Level = Experience / 1000;
                            Gold += Monster[j].Gold;
                        }
                        else
                        {
                            Monster[j].HealthPower -= DealDamage;
                        }
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
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
            if(y < rSize)
            {
                for(i = 1; i <= Sword[WeaponID].Range; i++)
                {
                    if( (ptrFlat + (y + i)*16 + x) )
                    {
                        j = (*(ptrFlat + (y + i)*16 + x)).eID;
                        DealDamage = Sword[WeaponID].DamagePhysical * (1 - Monster[j].Armor / 1000);
                        DealDamage += Sword[WeaponID].DamageMagic * (1 - Monster[j].MagicResistance / 1000);
                        DealDamage += Sword[WeaponID].DamageClear;
                        DealDamage *= Level;
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(Monster[j].HealthPower < DealDamage)
                        {
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                            Experience += Monster[j].Experience / 10;
                            Level = Experience / 1000;
                            Gold += Monster[j].Gold;
                        }
                        else
                        {
                            Monster[j].HealthPower -= DealDamage;
                        }
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
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
                    if( (ptrFlat + y*16 + x - i) )
                    {
                        j = (*(ptrFlat + y*16 + x - i)).eID;
                        DealDamage = Sword[WeaponID].DamagePhysical * (1 - Monster[j].Armor / 1000);
                        DealDamage += Sword[WeaponID].DamageMagic * (1 - Monster[j].MagicResistance / 1000);
                        DealDamage += Sword[WeaponID].DamageClear;
                        DealDamage *= Level;
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(Monster[j].HealthPower < DealDamage)
                        {
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                            Experience += Monster[j].Experience / 10;
                            Level = Experience / 1000;
                            Gold += Monster[j].Gold;
                        }
                        else
                        {
                            Monster[j].HealthPower -= DealDamage;
                        }
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
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
            if(y > 0)
            {
                for(i = 1; i <= Sword[WeaponID].Range; i++)
                {
                    if( (ptrFlat + y*16 + x + i) )
                    {
                        j = (*(ptrFlat + y*16 + x + i)).eID;
                        DealDamage = Sword[WeaponID].DamagePhysical * (1 - Monster[j].Armor / 1000);
                        DealDamage += Sword[WeaponID].DamageMagic * (1 - Monster[j].MagicResistance / 1000);
                        DealDamage += Sword[WeaponID].DamageClear;
                        DealDamage *= Level;
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
                        Log << "> Dealing Damage " << DealDamage << endl;
                        if(Monster[j].HealthPower < DealDamage)
                        {
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eType = NONE;
                            (*(ptrFlat + Monster[j].y*16 + Monster[j].x)).eID = -1;
                            Experience += Monster[j].Experience / 10;
                            Level = Experience / 1000;
                            Gold += Monster[j].Gold;
                        }
                        else
                        {
                            Monster[j].HealthPower -= DealDamage;
                        }
                        Log << "> Monster HP " << Monster[j].HealthPower << endl;
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
}



#endif
