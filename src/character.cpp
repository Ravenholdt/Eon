#include "character.h"
#include "dice.h"

#include "enums.h"

Character::Character(std::string name) 
{
    this->name = name;

    this->skill[skills::sword] = 14;
    this->skill[skills::dodge] = 12;

    this->generate();
}

void Character::generate()
{
    for (int i = 0; i < (int)attributes::max; i++){
        this->attribute[(attributes)i] = dice(3, 6, 0);
    }


    for (int i = 0; i < (int)personalities::max; i++){
        this->personality[(personalities)i] = dice(3, 6, 0);
    }

    this->personality[personalities::fame] = 5;
    this->personality[personalities::luck] = 11;


    this->age = this->attribute[attributes::education] + dice();
    this->dateOfBirth = dice(1, 365, 0);


    // TODO Händelser


    this->chock = (this->attribute[attributes::strength] + 
                   this->attribute[attributes::endurance] + 
                   this->attribute[attributes::willpower]) / 3;

    int body = (this->attribute[attributes::strength] + 
                  this->attribute[attributes::endurance] + 
                  dice(3, 6, 0));

    if (body <= 14){
        this->body = 1;
    }else if(body <= 24){
        this->body = 2;
    }else if(body <= 38){
        this->body = 3;
    }else if(body <= 48){
        this->body = 4;
    }else{
        this->body = 5;
    }

    this->damageColumns = body + 3;


    this->exhausionColumns = (this->attribute[attributes::endurance] + 
                              this->attribute[attributes::willpower]) / 4;


    this->lenght = (this->attribute[attributes::strength] + 
                  this->attribute[attributes::endurance] + 
                  dice(3, 6, 0) + 145);

    this->weight = lenght - 105;

    this->movement = (this->attribute[attributes::mobility] + 
                      this->attribute[attributes::endurance] + 
                      10) / 4;

    this->carry = (this->attribute[attributes::strength] + 
                  this->attribute[attributes::endurance]) / 2;

    // TODO grundskada

    this->vinit = ((this->attribute[attributes::mobility] / 2) + this->stridsvana) / 2;
    if (this->vinit < 5) vinit = 5;

    // TODO familjanäring

    // TODO Yrken
}



int Character::useSkill(skills skill, int difficulty){
    int penalty = 0; 
    penalty += this->damage[damageTypes::pain]/this->damageColumns;
    penalty += this->exhaustion/(this->exhausionColumns*2);

    std::cout << "(" << this->name << ") Penalty: " << penalty << "(" << this->damage[damageTypes::pain] << "/" << this->exhaustion << ")" << std::endl;

    exhaustion += 1;

    if (this->skill[skill] >= dice(difficulty + penalty))
        return 1;

    return 0;
}



int Character::newVinit()
{
    return dice() - this->vinit;
}

void Character::attack(Character *enemy)
{
    Damage damageDealt;

    damageDealt.damageModified = dice(4);
    std::cout << this->name << " attackerar " << enemy->name << "." << std::endl;

    if (this->useSkill(skills::sword)) // Attacker hits
    {
        if (!enemy->defence()) // Defender fails
        { 
            hitTableAim(&damageDealt, hitTableAimLocation::normal);
            enemy->damageTaken(damageDealt);
            std::cout << this->name << " träffar " << enemy->name << " i " << damageDealt.area << " (" << damageDealt.areaSub << ")." << std::endl;
            std::cout << "Skadevärde: " << damageDealt.damageModified << std::endl;
            std::cout << "Trauma: " << enemy->damage[damageTypes::trauma] << " (+" << damageDealt.trauma << ")" << std::endl << 
                         "Smärta: " << enemy->damage[damageTypes::pain] << " (+" << damageDealt.pain << ")" << std::endl << 
                         "Blödningstakt: " << enemy->damage[damageTypes::bleed] << " (+" << damageDealt.bleed << ")" << std::endl;
        }
        else
        {
            std::cout << enemy->name << " lyckas undvika " << this->name << "s attack." << std::endl;
        }
    }
    else
    {
        std::cout << this->name << " missar totalt." << std::endl;
    }
}

bool Character::defence()
{
    if (this->useSkill(skills::dodge)) return true;

    return false;
}

void Character::damageTaken(Damage attackDamage)
{
    this->damage[damageTypes::trauma] += attackDamage.trauma;
    this->damage[damageTypes::pain] += attackDamage.pain;
    this->damage[damageTypes::blood] += attackDamage.blood;

    this->damage[damageTypes::bleed] += attackDamage.bleed;
}