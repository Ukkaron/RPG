#include <iostream>

#include "RPG_source.h"

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
    int i;
    int room_size;
    srand(time(NULL));
    room_size = rand() % 9 + 8;
    cell platforms[room_size][room_size];
    cell *y_line[room_size];
    for (i=0; i< room_size; i++)
    {
        y_line[i] = &platforms[i][0];
    }
    room_generator(y_line, room_size);
}

