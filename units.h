using namespace std;

class Entity
{
  public: int ID;
  public: int Level;
  public: int HealthPower;
  public: int Armor;
  public: int MagicResistance;
  public: int Experience;
  public: int Gold;
  public: Entity(int lvl, int exp, int gld);
};

Entity::Entity(int lvl, int exp, int gld)
{
    Level = lvl;
    HealthPower = lvl * 100;
    Experience = exp;
    Gold = gld;
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
};
