class Entity
{
  public: int ID;
  public: int Level;
  public: int HealthPower;
  public: int ManaPool;
  public: int Armor;
  public: int Experience;
  public: int Gold;
  public: int WeaponID;
  public: int ArtifactID[6];
  public: int X;
  public: int Y;
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
    ArtifactID = artID;
}
