#pragma once

#include <stdio.h>
#include <string> //Strings

#include "dice.h"

class Damage
{
    public:
        std::string area;
        std::string areaSub;

        int areaCode;

        int trauma = 0;
        int pain = 0;
        int bleed = 0;
        int blood = 0;

        int armor[26];

        int damage = 0;
        int damageModified = 0;

        bool amp = false;
        bool bryt = false;
        bool faller = false;
        bool fast = false;
        bool inreSkada = false;
        bool kvav = false;
        bool men = false;
        bool tappar = false;
        bool arr = false;

        void addDamage(int trauma, int pain, int bleed, int blood = 0);
};

int hitTable(Damage *damage);
int hitTableHead(Damage *damage);
int hitTableAbdomen(Damage *damage);
int hitTableArm(Damage *damage, bool right);
int hitTableLeg(Damage *damage, bool right);

int damageTableFace(Damage *damage, char type);
int damageTableSkull(Damage *damage, char type);
int damageTableNeck(Damage *damage, char type);
int damageTableChest(Damage *damage, char type);
int damageTableStomach(Damage *damage, char type);
int damageTableGenital(Damage *damage, char type);
int damageTableArm(Damage *damage, char type);
int damageTableLeg(Damage *damage, char type);

void damageTableCutMarrow(Damage *damage, int type, bool leg = false);
void damageTableCutMuscle(Damage *damage, int type, bool leg = false);
void damageTableCutArtary(Damage *damage);
void damageTableCutConcussion(Damage *damage, int type);
void damageTableCutBleeding(Damage *damage, int type);
void damageTableCutFlesh(Damage *damage, int type);