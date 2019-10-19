#include "character.h"
#include "dice.h"

#include "enums.h"

Character::Character(std::string name) 
{
    this->name = name;

    this->skill[skills::sword] = 14;
    this->skill[skills::dodge] = 12;

    this->generate();

    for (int i = 0; i < (int)damageTypes::max; i++){
        this->damage[(damageTypes)i] = 0;
    }
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
    penalty += (this->damage[damageTypes::pain] -1) / this->damageColumns;
    penalty += (this->exhaustion -1) / (this->exhausionColumns*2);

    std::cout << "(" << this->name << ") Penalty: " << penalty << "(" << this->damage[damageTypes::pain] << "/" << this->exhaustion << ")" << std::endl;

    exhaustion += 1;

    if (this->skill[skill] >= dice(difficulty + penalty))
        return 1;

    return 0;
}



int Character::newVinit()
{
    return this->vinit - dice();
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
                         "Blödningstakt: " << enemy->damage[damageTypes::bleed] << " (+" << damageDealt.bleed << ")" << std::endl <<
                         "Blodförlust: " << enemy->damage[damageTypes::blood] << " (" << enemy->bloodTick << "/10)" << std::endl;
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

    checkHealth(attackDamage.trauma, attackDamage.pain, attackDamage.blood);
}

void Character::checkHealth(int newTrauma, int newPain, int newBlood){
    int dicePool;

    if (newTrauma > 0 || newPain > 0 || newBlood > 0)
    { // Death check
        dicePool = 0;
        dicePool += (this->damage[damageTypes::trauma] -1) / this->damageColumns;
        dicePool += (this->damage[damageTypes::blood] -1) / this->damageColumns;

        if (dice(dicePool) > this->chock){
            this->alive = false;
        }
    }

    { // Consious check
        int change = newTrauma + newPain + newBlood;

        dicePool = 0;
        dicePool += (this->damage[damageTypes::trauma] -1) / this->damageColumns;
        dicePool += (this->damage[damageTypes::blood] -1) / this->damageColumns;
        dicePool += (this->damage[damageTypes::pain] -1) / this->damageColumns;

        if (dice(dicePool) > this->chock) // Fail roll
        {
            if (change > 0) // If taking damage
            {
                this->conscious = false;
            }
        } else // Succeed roll
        {
            if (change < 0) // If healing
            {
                this->conscious = true;
            }
        }
    }
}



void Character::tick(){
    int bloodLoss = 0;

    if (!this->damage[damageTypes::bleed]) return; // If not bleeing, quit.

    if (this->damage[damageTypes::bleed] < 10)
    {
        this->bloodTick += 1;

        if (this->bloodTick >= 10)
        {
            this->bloodTick = 0;
            bloodLoss = 1;
        }
    } else {
        bloodLoss = this->damage[damageTypes::bleed] / 10;
    }

    Damage damage;
    damage.addDamage(0, 0, 0, bloodLoss);
    this->damageTaken(damage);
    
    std::cout << this->name << ", Bloodloss: " << this->damage[damageTypes::blood] << ", (" << this->bloodTick << "/10, "<< this->damage[damageTypes::bleed] << ")" << std::endl;
}