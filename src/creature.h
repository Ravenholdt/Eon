#include <iostream>
#include <string> //Strings

#include "damage.h"

class Creature
{
    public:
        std::string name;
        int id = 0;

        int exhaustion = 0;

        int avoid = 12;
        int weapon = 12;

        int pain = 0;
        int trauma = 0;
        int blood = 0;

        int bleed = 0;

        Creature(std::string name);

        void attack(Creature *enemy);
        bool defence();
        void damageTaken(Damage attackDamage);
};