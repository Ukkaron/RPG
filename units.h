#include "weapon.h"

using namespace std;

class Entity
{
  public: int ID;
  public: string Name;
  public: int Level;
  public: int HealthPower;
  public: int Armor;
  public: int MagicResistance;
  public: int Experience;
  public: int Gold;
};

class Monster: public Entity
{
    public: int DamagePhysical;
    public: int DamageMagic;
    public: string Name;
    public: void putMonster(int lvl, int strength, int exp, int gld, int DmgPh, int DmgMg, int Arm, int MgRes);
};

void Monster::putMonster(int lvl, int strength, int exp, int gld, int DmgPh, int DmgMg, int Arm, int MgRes)
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
};

void cHero::Show()
{
    cout << "Hero " << Name << endl;
    cout << "Level:" << Level << endl;
    cout << "Health power: " << HealthPower << endl;
    cout << "Mana: " << ManaPool << endl;
    cout << "Gold: " << Gold << endl;
    cout << "Weared weapon: " << Sword[WeaponID].Name << endl;
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
        cout << "Hero loaded." << endl;
        Hero.Show();
    }
    else
    {
        cout << "Enter the name of your hero: ";
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
