#include "main.h"

Creature::Creature(std::string name) 
{
    this->name = name;
}

void Creature::attack(Creature enemy)
{
    Damage damageDealt;

    this->exhaustion += 1;
    std::cout << this->name << " attackerar " << enemy.name << "." << std::endl;

    if (weapon >= dice()){ // Attacker hits
        if (!enemy.defence()) // Defender fails
        {
            hitTable(&damageDealt);
            std::cout << this->name << " träffar " << enemy.name << " i " << damageDealt.area << "." << std::endl;
        }
        else
        {
            std::cout << enemy.name << " lyckas unvika " << this->name << "s attack." << std::endl;
        }
    }
    else
    {
        std::cout << this->name << " missar totalt." << std::endl;
    }
}

bool Creature::defence()
{
    this->exhaustion += 1;
    if (avoid >= dice()) return true;

    return false;
}

void Creature::damageTaken(Damage attackDamage)
{
    this->trauma += attackDamage.trauma;
    this->pain += attackDamage.pain;
    this->blood += attackDamage.blood;

    this->bleed += attackDamage.bleed;
}

int main()
{
    srand(time(0));
    //printf("Rolling: %d\n", dice());

    // Create people
    Creature h1("Arne"), h2("Gunnar");

    h1.attack(h2);

    return 0;
}