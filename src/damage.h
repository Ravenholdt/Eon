#pragma once

#include <stdio.h>
#include <string> //Strings

#include "dice.h"

class Damage
{
    public:
        std::string area = "None";
        std::string areaSub = "None";

        int areaCode = -1;

        int trauma = 0;
        int pain = 0;
        int bleed = 0;
        int blood = 0;

        int armour[26];

        int damage = 0;
        int damageModified = 0;
        char damageType = 'h';

        bool amp = false;
        bool bryt = false;
        bool faller = false;
        bool fast = false;
        bool inreSkada = false;
        bool kvav = false;
        bool men = false;
        bool tappar = false;
        bool arr = false;

        void addDamage(int trauma = 0, int pain = 0, int bleed = 0, int blood = 0);
};

enum class hitTableAimLocation{ normal, high, low, head, armLeft, armRight, chest, abdomen, legLeft, legRight };

void hitTableAim(Damage *damage, hitTableAimLocation aim);