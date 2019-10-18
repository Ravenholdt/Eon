#pragma once

#include <iostream>
#include <string> //Strings
#include <map>

#include "damage.h"

#include "enums.h"

class Character
{
    public:
        int id = 0;
        std::string name;

        int age;
        int dateOfBirth;

        int armour[26];

        int exhaustion = 0;

        Character(std::string name);
        void generate();

        int useSkill(skills skill, int difficulty = 3);

        int newVinit();
        void attack(Character *enemy);
        bool defence();
        void damageTaken(Damage attackDamage);

    private:
        std::map<attributes, int> attribute;
        std::map<personalities, int> personality;

        std::map<skills, int> skill;

        std::map<damageTypes, int> damage;

        int chock;
        int body;
        int damageColumns;
        int exhausionColumns;

        int lenght;
        int weight;

        int movement;
        int carry;

        int vinit;
        int stridsvana = 0;
};