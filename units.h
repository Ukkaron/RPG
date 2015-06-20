using namespace std;

class Entity
{
  public: int ID;
  public: int Level;
  public: int HealthPower;
  public: int ManaPool;
  public: int Armor;
  public: int MagicResistance;
  public: int Experience;
  public: int Gold;
  public: int WeaponID;
  public: int ArtifactID[6];
  public: int SkillID[4];
  public: Entity(int lvl, int exp, int gld, int wpnID, int artID[6]);
};

Entity::Entity(int lvl, int exp, int gld, int wpnID, int artID[6])
{
    Level = lvl;
    HealthPower = lvl * 100;
    ManaPool = lvl * 150;
    Experience = exp;
    Gold = gld;
    WeaponID = wpnID;
    if(artID)
    {
        int i; // counter
        for(i = 0; i < 6; i++)
        {
            ArtifactID[i] = (*artID + i);
        }
    }
}

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
    ManaPool = 0;
    Experience = exp;
    Gold = gld;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    Armor = Arm;
    MagicResistance = MgRes;
}
