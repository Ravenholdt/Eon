#pragma once

#include <stdio.h>
#include <string> //Strings

#include "dice.h"

class Damage
{
    public:
        std::string area;

        int trauma;
        int pain;
        int bleed;
        int blood;

        int armor[26];

        int damage;
        int damageApplied;
};

int hitTable(Damage *damage);
int hitTableHead(Damage *damage);
int hitTableAbdomen(Damage *damage);
int hitTableArm(Damage *damage, bool right);
int hitTableLeg(Damage *damage, bool right);