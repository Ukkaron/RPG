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
  public: int ArtifactID[6]; // Пиешет ошибку, ругается на int[]
  public: int X;
  public: int Y;
  public: Entity(int lvl, int exp, int gld, int wpnID, int artID[6]); // Пишет ошибку в последней переменной
};

Entity::Entity(int lvl, int exp, int gld, int wpnID, int artID[6])
{
    Level = lvl;
    HealthPower = lvl * 100;
    ManaPool = lvl * 150;
    Experience = exp;
    Gold = gld;
    WeaponID = wpnID;
    ArtifactID = artID; // Ошибка, пишет неопределенны переменные
}
