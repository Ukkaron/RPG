using namespace std;

class cWeapon
{
    public: int ID;
    public: string Name;
    public: int DamagePhysical;
    public: int DamageMagic;
    public: int DamageClear;
    public: int Price;
};

class cWeaponMelee: cWeapon
{
    public: int Range;
    public: cWeaponMelee(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc);
    public: void putWeaponMelee(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc);
};

cWeaponMelee::cWeaponMelee(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc)
{
    ID = wpnID;
    Name = Nm;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    DamageClear = DmgCl;
    Price = Prc;
    Range = 1;
}

void cWeaponMelee::putWeaponMelee(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc)
{
    ID = wpnID;
    Name = Nm;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    DamageClear = DmgCl;
    Price = Prc;
    Range = 1;
}

class cWeaponBow: cWeapon
{
    public: int Range;
    public: cWeaponBow(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc);
    public: void putWeaponBow(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc);
};

cWeaponBow::cWeaponBow(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc)
{
    ID = wpnID;
    Name = Nm;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    DamageClear = DmgCl;
    Price = Prc;
    Range = 3;
}

void cWeaponBow::putWeaponBow(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc)
{
    ID = wpnID;
    Name = Nm;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    DamageClear = DmgCl;
    Price = Prc;
    Range = 3;
}

class cWeaponStaff: cWeapon
{
    public: int Range;
    public: cWeaponStaff(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc);
    public: void putWeaponStaff(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc);
};

cWeaponStaff::cWeaponStaff(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc)
{
    ID = wpnID;
    Name = Nm;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    DamageClear = DmgCl;
    Price = Prc;
    Range = 2;
}

void cWeaponStaff::putWeaponStaff(int wpnID, string Nm, int DmgPh, int DmgMg, int DmgCl, int Prc)
{
    ID = wpnID;
    Name = Nm;
    DamagePhysical = DmgPh;
    DamageMagic = DmgMg;
    DamageClear = DmgCl;
    Price = Prc;
    Range = 2;
}

cWeaponMelee Sword[5] = cWeaponMelee(-1, "X", 0, 0, 0, 0);
void GenerateMeleeWeapons()
{
    Sword[0].putWeaponMelee(0, "Sword of Zephyr", 50, 10, 0, 1500);
    Sword[1].putWeaponMelee(1, "Iron Sword", 35, 0, 0, 300);
    Sword[2].putWeaponMelee(2, "Steel Sword", 50, 0, 0, 700);
    Sword[3].putWeaponMelee(3, "Mithril Sword", 40, 0, 20, 3000);
}
