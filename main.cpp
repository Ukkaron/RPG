#include <iostream>

using namespace std;
class Entity
{
  public: int Level;
  public: int HealthPower;
  public: int ManaPool;
  public: int Armor;
  public: int Experience;
  public: int Gold;
  public: int WeaponID;
  public: int[] ArtifactID = new int[6];
  public: int X;
  public: int Y;
  public: Entity(int lvl, int exp, int gld, int wpnID, int[6] artID);
};

Entity::Entity(int lvl, int exp, int gld, int wpnID, int[6] artID)
{
    Level = lvl;
    HealthPower = lvl * 100;
    ManaPool = lvl * 150;
    Experience = exp;
    Gold = gld;
    WeaponID = wpnID;
    ArtifactID = artID;
}

int main()
{
  cout << "Hellow World !" << endl;
  return 0;
}

