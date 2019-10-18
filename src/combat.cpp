#include "combat.h"

combat::combat(Character *team1, Character *team2)
{
    this->team1 = team1;
    this->team2 = team2;
}

combat::~combat()
{
}

void combat::nextTurn()
{
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
}
