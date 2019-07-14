#include "character.h"

Character::Character(std::string name) 
{
    this->name = name;
}

void Character::attack(Character *enemy)
{
    Damage damageDealt;

    damageDealt.damageModified = dice(4);
    this->exhaustion += 1;
    std::cout << this->name << " attackerar " << enemy->name << "." << std::endl;

    if (weapon >= dice()){ // Attacker hits
        if (!enemy->defence()) // Defender fails
        { 
            hitTable(&damageDealt);
            enemy->damageTaken(damageDealt);
            std::cout << this->name << " träffar " << enemy->name << " i " << damageDealt.area << " (" << damageDealt.areaSub << ")." << std::endl;
            std::cout << "Skadevärde: " << damageDealt.damageModified << std::endl;
            std::cout << "Trauma: " << enemy->trauma << std::endl << "Smärta: " << enemy->pain << std::endl << "Blödningstakt: " << enemy->bleed << std::endl;
        }
        else
        {
            std::cout << enemy->name << " lyckas unvika " << this->name << "s attack." << std::endl;
        }
    }
    else
    {
        std::cout << this->name << " missar totalt." << std::endl;
    }
}

bool Character::defence()
{
    this->exhaustion += 1;
    if (avoid >= dice()) return true;

    return false;
}

void Character::damageTaken(Damage attackDamage)
{
    this->trauma += attackDamage.trauma;
    this->pain += attackDamage.pain;
    this->blood += attackDamage.blood;

    this->bleed += attackDamage.bleed;
}