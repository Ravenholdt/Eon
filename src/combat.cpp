#include "combat.h"

Combat::Combat(Character *team1, Character *team2)
{
    this->team1 = team1;
    this->team2 = team2;
}

Combat::~Combat()
{
}

bool Combat::nextTurn()
{
    this->round++;

    std::cout << "-------------------------------- " << round << std::endl;

    if (!this->vinit) // If we don't have an attacker, create one.
    {
        while (this->vinit == 0)
        {
            int t1 = this->team1->newVinit();
            int t2 = this->team2->newVinit();
            
            this->vinit = t2 - t1;
        }

        if (this->vinit < 0){
            this->attacker = team1;
            this->defender = team2;
        } else {
            this->attacker = team2;
            this->defender = team1;
        }
    } else // If we have an attacker, give the defender a fair chance.
    {
        if (this->defender->newVinit() >= 0)
        {
            Character *buffer = this->defender;
            this->defender = this->attacker;
            this->attacker = buffer;
        }
    }

    this->attacker->attack(this->defender);

    this->attacker->tick();
    this->defender->tick();

    if (!this->attacker->alive)
    {
        std::cout << this->attacker->name << " is dead!" << std::endl;
        return false;
    }
    if (!this->defender->alive)
    {
        std::cout << this->defender->name << " is dead!" << std::endl;
        return false;
    }

    return true;
}
