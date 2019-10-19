#include "damage.h"

class HitTable{
    private:
        class DamageTable{
            private:
                class Cut{
                    public:
                        void marrow(Damage *damage, int type, bool fall = false);
                        void muscle(Damage *damage, int type, bool fall = false);
                        void artery(Damage *damage);
                        void concussion(Damage *damage, int type, bool vital = false, bool fall = false);
                        void bleeding(Damage *damage, int type);
                        void flesh(Damage *damage, int type);
                }cut;
                class Crush{
                    public:
                        void marrow(Damage *damage, int type, bool fall = false);
                        void muscle(Damage *damage, int type, bool fall = false);
                        void artery(Damage *damage);
                        void concussion(Damage *damage, int type, bool vital = false, bool fall = false);
                        void bleeding(Damage *damage, int type);
                        void flesh(Damage *damage, int type);
                }crush;
                class Pierce{
                    public:
                        void marrow(Damage *damage, int type, bool fall = false);
                        void muscle(Damage *damage, int type, bool fall = false);
                        void artery(Damage *damage, int type);
                        void concussion(Damage *damage, int type, bool vital = false, bool fall = false);
                        void bleeding(Damage *damage, int type);
                        void flesh(Damage *damage, int type);
                }pierce;
            public:
                void face(Damage *damage);
                void skull(Damage *damage);
                void neck(Damage *damage);
                void chest(Damage *damage);
                void stomach(Damage *damage);
                void genital(Damage *damage);
                void arm(Damage *damage);
                void leg(Damage *damage);
        }damageTable;
    public:
        void normal(Damage *damage);
        void high(Damage *damage);
        void low(Damage *damage);

        void head(Damage *damage);
        void chest(Damage *damage);
        void abdomen(Damage *damage);
        void arm(Damage *damage, bool right);
        void leg(Damage *damage, bool right);
}hitTable;

void Damage::addDamage(int trauma, int pain, int bleed, int blood){
    this->trauma += trauma;
    this->pain += pain;
    this->bleed += bleed;
    this->blood += blood;
}

void hitTableAim(Damage *damage, hitTableAimLocation aim = hitTableAimLocation::normal)
{
    switch (aim)
    {
    case hitTableAimLocation::normal: // Base
        hitTable.normal(damage);
        break;

    case hitTableAimLocation::high: // Base aim
        hitTable.normal(damage);
        break;
    case hitTableAimLocation::low:
        hitTable.normal(damage);
        break;
    
    case hitTableAimLocation::head: // Advanced aim
        hitTable.head(damage);
        break;
    case hitTableAimLocation::armLeft:
        hitTable.arm(damage, false);
        break;
    case hitTableAimLocation::armRight:
        hitTable.arm(damage, true);
        break;
    case hitTableAimLocation::chest:
        hitTable.chest(damage);
        break;
    case hitTableAimLocation::abdomen:
        hitTable.abdomen(damage);
        break;
    case hitTableAimLocation::legLeft:
        hitTable.leg(damage, false);
        break;
    case hitTableAimLocation::legRight:
        hitTable.leg(damage, true);
        break;
    }
}

void HitTable::normal(Damage *damage)
{
    int roll = dice(1, 100, false);

    if(roll <= 20){ // Head
        head(damage);
    }

    else if(roll <= 40){ // Left arm
        arm(damage, false);
    }
    
    else if(roll <= 60){ // Right arm
        arm(damage, true);
    }
    
    else if(roll <= 70){ // Chest
        chest(damage);
    }
    
    else if(roll <= 80){ // Abdomen 
        abdomen(damage);
    }
    
    else if(roll <= 90){ // Left leg
        leg(damage, false);
    }
    
    else if(roll <= 100){ // Right leg
        leg(damage, true);
    }
}

void HitTable::high(Damage *damage)
{
    int roll = dice(1, 100, false);

    if(roll <= 30){ // Head
        head(damage);
    }

    else if(roll <= 60){ // Left arm
        arm(damage, false);
    }
    
    else if(roll <= 90){ // Right arm
        arm(damage, true);
    }
    
    else if(roll <= 100){ // Chest
        chest(damage);
    }
    
    
}

void HitTable::low(Damage *damage)
{
    int roll = dice(1, 100, false);

    if(roll <= 20){ // Abdomen 
        abdomen(damage);
    }
    
    else if(roll <= 60){ // Left leg
        leg(damage, false);
    }
    
    else if(roll <= 100){ // Right leg
        leg(damage, true);
    }
}

void HitTable::head(Damage *damage)
{
    int roll = dice(1, 10, false);
    if(roll <= 4){
        damage->area.assign("ansiktet");
        damageTable.face(damage);
    }
    
    else if(roll <= 8){
        damage->area.assign("skallen");
        damageTable.skull(damage);
    }

    else if(roll <= 10){
        damage->area.assign("halsen");
        damageTable.neck(damage);
    }
}

void HitTable::arm(Damage *damage, bool right=false)
{
    int roll = dice(1, 10, false);

    if (right){
        damage->area.assign("höger ");
    } else {
        damage->area.assign("vänster ");
    }

    if(roll <= 2){
        damage->area.append("skuldra");
    }

    else if(roll <= 4){
        damage->area.append("överarm");
    }

    else if(roll <= 5){
        damage->area.append("armbåge");
    }

    else if(roll <= 8){
        damage->area.append("underarm");
    }

    else if(roll <= 10){
        damage->area.append("hand");
    }

    damageTable.arm(damage);
}

void HitTable::chest(Damage *damage)
{
    damage->area.assign("bröstkorgen");
    damageTable.chest(damage);
}

void HitTable::abdomen(Damage *damage)
{
    int roll = dice(1, 10, false);

    if(roll <= 8){
        damage->area.assign("magen");
        damageTable.stomach(damage);
    }

    else if(roll <= 10){
        damage->area.assign("underlivet");
        damageTable.genital(damage);
    }
}

void HitTable::leg(Damage *damage, bool right=false)
{
    int roll = dice(1, 10, false);

    if (right){
        damage->area.assign("höger ");
    } else {
        damage->area.assign("vänster ");
    }

    if(roll <= 2){
        damage->area.append("höft");
    }

    else if(roll <= 4){
        damage->area.append("lår");
    }

    else if(roll <= 6){
        damage->area.append("knä");
    }

    else if(roll <= 9){
        damage->area.append("vad");
    }

    else if(roll <= 10){
        damage->area.append("fot");
    }

    damageTable.leg(damage);
}

void HitTable::DamageTable::face(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,3,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärna
                    damage->areaSub.assign("Hjärna");
                    damage->addDamage(dmg*2, dmg, dmg/2);
                    damage->amp = true;
                    damage->fast = true;
                    damage->men = true;
                    break;
                case 2: // Öga
                    damage->areaSub.assign("Öga");
                    damage->addDamage(dmg/2, dmg, dmg/10);
                    damage->amp = true;
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 3: // Käke
                    damage->areaSub.assign("Mun/Käke");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 4: // Öra
                    damage->areaSub.assign("Öra");
                    damage->addDamage(dmg/10, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 5: // Näsa
                    damage->areaSub.assign("Näsa");
                    damage->addDamage(dmg/10, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->bryt = true;
                    damage->arr = true;
                    break;
                case 6: // Omtöckning
                    cut.concussion(damage, 3, true);
                    break;
                case 7: // Blödning
                    cut.bleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    cut.flesh(damage, 2);
                    break;
                case 9: // Köttsår
                    cut.flesh(damage, 1);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,4,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärna
                    damage->areaSub.assign("Hjärna");
                    damage->addDamage(dmg*2, dmg, 0);
                    damage->men = true;
                    break;
                case 2: // Öga
                    damage->areaSub.assign("Öga");
                    damage->addDamage(dmg/2, dmg, 0);
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 3: // Käke
                    damage->areaSub.assign("Mun/Käke");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 4: // Öra
                    damage->areaSub.assign("Öra");
                    damage->addDamage(dmg/10, dmg/2, 0);
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 5: // Näsa
                    damage->areaSub.assign("Näsa");
                    damage->addDamage(dmg/10, dmg/2, dmg/10);
                    damage->bryt = true;
                    damage->arr = true;
                    break;
                case 6: // Omtöckning
                    crush.concussion(damage, 2, true);
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 2, true);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 1, true);
                    break;
                case 9: // Blödning
                    crush.bleeding(damage, 0);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,3,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärna
                    damage->areaSub.assign("Hjärna");
                    damage->addDamage(dmg*2, dmg, dmg/2);
                    damage->fast = true;
                    damage->men = true;
                    break;
                case 2: // Öga
                    damage->areaSub.assign("Öga");
                    damage->addDamage(dmg/2, dmg, dmg/10);
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 3: // Käke
                    damage->areaSub.assign("Mun/Käke");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 4: // Öra
                    damage->areaSub.assign("Öra");
                    damage->addDamage(dmg/10, dmg/2, dmg/10);
                    damage->men = true;
                    damage->arr = true;
                    break;
                case 5: // Näsa
                    damage->areaSub.assign("Näsa");
                    damage->addDamage(dmg/10, dmg/2, dmg/10);
                    damage->bryt = true;
                    damage->arr = true;
                    break;
                case 6: // Omtöckning
                    pierce.concussion(damage, 2, true);
                    break;
                case 7: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 8: // Blödning
                    pierce.bleeding(damage, 0);
                    break;
                case 9: // Köttsår
                    pierce.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

void HitTable::DamageTable::skull(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärna
                    damage->fast = true;
                case 2: // Hjärna
                    damage->areaSub.assign("Hjärna");
                    damage->addDamage(dmg*2, dmg, dmg/2);
                    damage->amp = true;
                    damage->men = true;
                    break;
                case 3: // Skalle
                    damage->arr = true;
                case 4: // Skalle
                    damage->fast = true;
                case 5: // Skalle
                    damage->areaSub.assign("Skalle");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->bryt = true;
                    break;
                case 6: // Omtöckning
                    cut.concussion(damage, 3, true);
                    break;
                case 7: // Omtöckning
                    cut.concussion(damage, 2, true);
                    break;
                case 8: // Bleeding
                    cut.bleeding(damage, 1);
                    break;
                case 9: // Köttsår
                    cut.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,3,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärna
                    damage->faller = true;
                case 2: // Hjärna
                    damage->areaSub.assign("Hjärna");
                    damage->addDamage(dmg*2, dmg, 0);
                    damage->men = true;
                    break;
                case 3: // Skalle
                    damage->arr = true;
                case 4: // Skalle
                case 5: // Skalle
                    damage->areaSub.assign("Skalle");
                    damage->addDamage(dmg/2, dmg/2, 0);
                    damage->bryt = true;
                    break;
                case 6: // Omtöckning
                    crush.concussion(damage, 2, true);
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 2, true);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 1, true);
                    break;
                case 9: // Bleeding
                    crush.bleeding(damage, 0);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärna
                case 2: // Hjärna
                    damage->areaSub.assign("Hjärna");
                    damage->addDamage(dmg*2, dmg, dmg/2);
                    damage->fast = true;
                    damage->men = true;
                    break;
                case 3: // Skalle
                    damage->arr = true;
                case 4: // Skalle
                    damage->areaSub.assign("Skalle");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->fast = true;
                    damage->bryt = true;
                    break;
                case 5: 
                case 6: // Omtöckning
                    pierce.concussion(damage, 1, true);
                    break;
                case 7: // Bleeding
                    pierce.bleeding(damage, 2);
                    break;
                case 8: // Bleeding
                    pierce.bleeding(damage, 0);
                    break;
                case 9: // Köttsår
                    pierce.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

void HitTable::DamageTable::neck(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Strupe
                    damage->tappar = true;
                case 2: // Strupe
                    damage->areaSub.assign("Strupe");
                    damage->addDamage(dmg, dmg*2, dmg);
                    damage->amp = true;
                    damage->kvav = true;
                    break;
                case 3: // Nackkotor
                    damage->fast = true;
                case 4: // Nackkotor
                    damage->areaSub.assign("Nackkotor");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->bryt = true;
                    break;
                case 5: // Pulsåder
                    damage->areaSub.assign("Pulsåder");
                    damage->addDamage(dmg/2, dmg/2, dmg*2);
                    damage->amp = true;
                    break;
                case 6: // Artärblödning
                    cut.artery(damage);
                    break;
                case 7: // Omtöckning
                    cut.concussion(damage, 2, true);
                    break;
                case 8: // Blödning
                    cut.bleeding(damage, 1);
                    break;
                case 9: // Köttsår
                    cut.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,3,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Strupe
                    damage->areaSub.assign("Strupe");
                    damage->addDamage(dmg, dmg*2, dmg);
                    damage->kvav = true;
                    damage->tappar = true;
                    break;
                case 2: // Nackkotor
                case 3: // Nackkotor
                    damage->faller = true;
                case 4: // Nackkotor
                    damage->tappar = true;
                case 5: // Nackkotor
                    damage->areaSub.assign("Nackkotor");
                    damage->addDamage(dmg/2, dmg/2, 0);
                    damage->bryt = true;
                    break;
                case 6: // Omtöckning
                    crush.concussion(damage, 2, true);
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 2, true);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 1, true);
                    break;
                case 9: // Blödning
                    crush.bleeding(damage, 0);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Strupe
                    damage->areaSub.assign("Strupe");
                    damage->addDamage(dmg, dmg*2, dmg);
                    damage->fast = true;
                    damage->kvav = true;
                    damage->tappar = true;
                    break;
                case 2: // Nackkotor
                    damage->areaSub.assign("Nackkotor");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->bryt = true;
                    damage->fast = true;
                    break;
                case 3: // Pulsåder
                    damage->fast = true;
                case 4: // Pulsåder
                    damage->areaSub.assign("Pulsåder");
                    damage->addDamage(dmg/2, dmg/2, dmg*2);
                    break;
                case 5: // Artärblödning
                    pierce.artery(damage, 1);
                    break;
                case 6: // Artärblödning
                    pierce.artery(damage, 0);
                    break;
                case 7: // Omtöckning
                    pierce.concussion(damage, 1, true);
                    break;
                case 8: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 9: // Blödning
                    pierce.bleeding(damage, 0);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

void HitTable::DamageTable::chest(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärta
                    damage->areaSub.assign("Hjärta");
                    damage->addDamage(dmg, dmg/10, dmg*5);
                    damage->amp = true;
                    damage->faller = true;
                    damage->fast = true;
                    break;
                case 2: // Lunga
                    damage->areaSub.assign("Lunga");
                    damage->addDamage(dmg, dmg, dmg);
                    damage->amp = true;
                    damage->fast = true;
                    damage->inreSkada = true;
                    break;
                case 3: // Lunga
                    damage->areaSub.assign("Lunga");
                    damage->addDamage(dmg, dmg, dmg);
                    damage->amp = true;
                    damage->faller = true;
                    damage->inreSkada = true;
                    break;
                case 4: // Pulsåder
                    damage->areaSub.assign("Pulsåder");
                    damage->addDamage(dmg/2, dmg/2, dmg*2);
                    damage->amp = true;
                    break;
                case 5: // Ryggrad
                    damage->areaSub.assign("Ryggrad");
                    damage->addDamage(dmg, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->bryt = true;
                    damage->fast = true;
                    break;
                case 6: // Revben
                    damage->fast = true;
                    break;
                case 7: // Revben
                    damage->areaSub.assign("Revben");
                    damage->addDamage(dmg/10, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->bryt = true;
                    break;
                case 8: // Omtöckning
                    cut.concussion(damage, 1);
                    break;
                case 9: // Blödning
                    cut.bleeding(damage, 2);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,2,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Lunga
                    damage->areaSub.assign("Lunga");
                    damage->addDamage(dmg, dmg, 0);
                    damage->faller = true;
                    damage->inreSkada = true;
                    break;
                case 2: // Ryggrad
                    damage->faller = true;
                case 3: // Ryggrad
                    damage->areaSub.assign("Ryggrad");
                    damage->addDamage(dmg, dmg/2, 0);
                    damage->bryt = true;
                    break;
                case 4: // Revben
                    damage->faller = true;
                case 5: // Revben
                    damage->tappar = true;
                case 6: // Revben
                    damage->areaSub.assign("Revben");
                    damage->addDamage(dmg/10, dmg/2, 0);
                    damage->bryt = true;
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 1);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 0);
                    break;
                case 9: // Blödning
                    crush.bleeding(damage, 2);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Hjärta
                    damage->faller = true;
                case 2: // Hjärta
                    damage->areaSub.assign("Hjärta");
                    damage->addDamage(dmg, dmg/10, dmg*5);
                    damage->fast = true;
                    break;
                case 3: // Lunga
                    damage->faller = true;
                case 4: // Lunga
                    damage->areaSub.assign("Lunga");
                    damage->addDamage(dmg, dmg, dmg);
                    damage->fast = true;
                    damage->inreSkada = true;
                    break;
                case 5: // Pulsåder
                    damage->areaSub.assign("Pulsåder");
                    damage->addDamage(dmg/2, dmg/2, dmg*2);
                    damage->fast = true;
                    break;
                case 6: // Ryggrad
                    damage->areaSub.assign("Ryggrad");
                    damage->addDamage(dmg, dmg/2, dmg/10);
                    damage->bryt = true;
                    damage->fast = true;
                    break;
                case 7: // Revben
                    damage->areaSub.assign("Revben");
                    damage->addDamage(dmg/10, dmg/2, dmg/10);
                    damage->bryt = true;
                    damage->fast = true;
                    break;
                case 8: // Omtöckning
                    pierce.concussion(damage, 0);
                    break;
                case 9: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

void HitTable::DamageTable::stomach(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Inälvor
                    damage->faller = true;
                case 2: // Inälvor
                    damage->areaSub.assign("Inälvor");
                    damage->addDamage(dmg/2, dmg/2, dmg);
                    damage->amp = true;
                    damage->inreSkada = true;
                    break;
                case 3: // Ryggrad
                    damage->areaSub.assign("Ryggrad");
                    damage->addDamage(dmg, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->bryt = true;
                    damage->fast = true;
                    break;
                case 4: // Pulsåder
                    damage->areaSub.assign("Pulsåder");
                    damage->addDamage(dmg/2, dmg/2, dmg*2);
                    damage->amp = true;
                    break;
                case 5: // Artärblödning
                    cut.artery(damage);
                    break;
                case 6: // Omtöckning
                    cut.concussion(damage, 1);
                    break;
                case 7: // Blödning
                    cut.bleeding(damage, 2);
                    break;
                case 8: // Blödning
                    cut.bleeding(damage, 1);
                    break;
                case 9: // Köttsår
                    cut.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,3,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Inälvor
                    damage->faller = true;
                case 2: // Inälvor
                    damage->areaSub.assign("Inälvor");
                    damage->addDamage(dmg/2, dmg/2, 0);
                    damage->inreSkada = true;
                    break;
                case 3: // Ryggrad
                    damage->faller = true;
                case 4: // Ryggrad
                    damage->areaSub.assign("Ryggrad");
                    damage->addDamage(dmg, dmg/2, 0);
                    damage->bryt = true;
                    break;
                case 5: // Artärblödning
                    crush.artery(damage);
                    break;
                case 6: // Omtöckning
                    crush.concussion(damage, 2);
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 1);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 0);
                    break;
                case 9: // Blödning
                    crush.bleeding(damage, 0);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Inälvor
                    damage->faller = true;
                case 2: // Inälvor
                case 3: // Inälvor
                    damage->areaSub.assign("Inälvor");
                    damage->addDamage(dmg/2, dmg/2, dmg);
                    damage->fast = true;
                    damage->inreSkada = true;
                    break;
                case 4: // Ryggrad
                    damage->areaSub.assign("Ryggrad");
                    damage->addDamage(dmg, dmg/2, dmg/10);
                    damage->bryt = true;
                    damage->fast = true;
                    break;
                case 5: // Pulsåder
                    damage->areaSub.assign("Pulsåder");
                    damage->addDamage(dmg/2, dmg/2, dmg*2);
                    damage->fast = true;
                    break;
                case 6: // Artärblödning
                    pierce.artery(damage, 1);
                    break;
                case 7: // Omtöckning
                    pierce.concussion(damage, 0);
                    break;
                case 8: // Blödning
                    pierce.bleeding(damage, 1);
                    break;
                case 9: // Blödning
                    pierce.bleeding(damage, 1);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

void HitTable::DamageTable::genital(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Könsorgan
                    damage->areaSub.assign("Könsorgan");
                    damage->addDamage(dmg/2, dmg/2, dmg/2);
                    damage->amp = true;
                    damage->men = true;
                    damage->tappar = true;
                    break;
                case 2: // Könsorgan
                    damage->areaSub.assign("Könsorgan");
                    damage->addDamage(dmg/2, dmg/2, dmg/2);
                    damage->amp = true;
                    damage->faller = true;
                    damage->men = true;
                    break;
                case 3: // Omtöckning
                    cut.concussion(damage, 2, true);
                    break;
                case 4: // Omtöckning
                    cut.concussion(damage, 2, true, true);
                    break;
                case 5: // Blödning
                    cut.bleeding(damage, 2);
                    break;
                case 6: // Blödning
                    cut.bleeding(damage, 2);
                    break;
                case 7: // Blödning
                    cut.bleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    cut.flesh(damage, 2);
                    break;
                case 9: // Köttsår
                    cut.flesh(damage, 1);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,3,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Könsorgan
                case 2: // Könsorgan
                    damage->tappar = true;
                case 3: // Könsorgan
                case 4: // Könsorgan
                    damage->areaSub.assign("Könsorgan");
                    damage->addDamage(dmg/2, dmg/2, 0);
                    damage->faller = true;
                    damage->men = true;
                    break;
                case 5: // Omtöckning
                case 6: // Omtöckning
                    crush.concussion(damage, 2, true);
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 1, true, true);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 0, true);
                    break;
                case 9: // Blödning
                    crush.bleeding(damage, 1);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,2,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Könsorgan
                    damage->areaSub.assign("Könsorgan");
                    damage->addDamage(dmg/2, dmg/2, dmg/2);
                    damage->fast = true;
                    damage->men = true;
                    damage->tappar = true;
                    break;
                case 2: // Könsorgan
                    damage->areaSub.assign("Könsorgan");
                    damage->addDamage(dmg/2, dmg/2, dmg/2);
                    damage->faller = true;
                    damage->men = true;
                    break;
                case 3: // Omtöckning
                    pierce.concussion(damage, 1, true);
                    break;
                case 4: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 5: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 6: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 7: // Blödning
                    pierce.bleeding(damage, 1);
                    break;
                case 8: // Blödning
                    pierce.bleeding(damage, 0);
                    break;
                case 9: // Köttsår
                    pierce.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

void HitTable::DamageTable::arm(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    cut.marrow(damage, 4, false);
                    break;
                case 2: // Benpipa
                    cut.marrow(damage, 3, false);
                    break;
                case 3: // Artärblödning
                    cut.artery(damage);
                    break;
                case 4: // Muskel/Senor
                    cut.muscle(damage, 3, false);
                    break;
                case 5: // Muskel/Senor
                    cut.muscle(damage, 2, false);
                    break;
                case 6: // Omtöckning
                    cut.concussion(damage, 2);
                    break;
                case 7: // Blödning
                    cut.bleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    cut.flesh(damage, 2);
                    break;
                case 9: // Köttsår
                    cut.flesh(damage, 1);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,2,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    crush.marrow(damage, 2);
                    break;
                case 2: // Benpipa
                    crush.marrow(damage, 2);
                    break;
                case 3: // Benpipa
                    crush.marrow(damage, 1);
                    break;
                case 4: // Muskel/Senor
                    crush.muscle(damage, 2);
                    break;
                case 5: // Muskel/Senor
                    crush.muscle(damage, 1);
                    break;
                case 6: // Omtöckning
                    crush.concussion(damage, 1);
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 1);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 0);
                    break;
                case 9: // Blödning
                    crush.bleeding(damage, 0);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    pierce.marrow(damage, 4, false);
                    break;
                case 2: // Artärblödning
                    pierce.artery(damage, 1);
                    break;
                case 3: // Muskel/Senor
                    pierce.muscle(damage, 3, false);
                    break;
                case 4: // Muskel/Senor
                    pierce.muscle(damage, 2, false);
                    break;
                case 5: // Muskel/Senor
                    pierce.muscle(damage, 1, false);
                    break;
                case 6: // Omtöckning
                    pierce.concussion(damage, 1);
                    break;
                case 7: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 8: // Blödning
                    pierce.bleeding(damage, 0);
                    break;
                case 9: // Köttsår
                    pierce.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

void HitTable::DamageTable::leg(Damage *damage){
    int dmg = damage->damageModified;
    if (damage->damageType == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    cut.marrow(damage, 4, true);
                    break;
                case 2: // Benpipa
                    cut.marrow(damage, 3, true);
                    break;
                case 3: // Artärblödning
                    cut.artery(damage);
                    break;
                case 4: // Omtöckning
                    cut.muscle(damage, 3, true);
                    break;
                case 5: // Blödning
                    cut.muscle(damage, 2, true);
                    break;
                case 6: // Omtöckning
                    cut.concussion(damage, 2, false, true);
                    break;
                case 7: // Blödning
                    cut.bleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    cut.flesh(damage, 2);
                    break;
                case 9: // Köttsår
                    cut.flesh(damage, 1);
                    break;
                case 10: // Köttsår
                    cut.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 'k'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(0,2,0);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    crush.marrow(damage, 2, true);
                    break;
                case 2: // Benpipa
                    crush.marrow(damage, 2, true);
                    break;
                case 3: // Benpipa
                    crush.marrow(damage, 1, true);
                    break;
                case 4: // Muskel/Senor
                    crush.muscle(damage, 3, true);
                    break;
                case 5: // Muskel/Senor
                    crush.muscle(damage, 2, true);
                    break;
                case 6: // Omtöckning
                    crush.concussion(damage, 1, false, true);
                    break;
                case 7: // Omtöckning
                    crush.concussion(damage, 1, false, true);
                    break;
                case 8: // Omtöckning
                    crush.concussion(damage, 0, false, true);
                    break;
                case 9: // Blödning
                    crush.bleeding(damage, 0);
                    break;
                case 10: // Köttsår
                    crush.flesh(damage, 0);
                    break;
            }
        }
    }
    if (damage->damageType == 's'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    pierce.marrow(damage, 4, true);
                    break;
                case 2: // Artärblödning
                    pierce.artery(damage, 1);
                    break;
                case 3: // Muskel/Senor
                    pierce.muscle(damage, 3, true);
                    break;
                case 4: // Muskel/Senor
                    pierce.muscle(damage, 2);
                    break;
                case 5: // Muskel/Senor
                    pierce.muscle(damage, 1);
                    break;
                case 6: // Omtöckning
                    pierce.concussion(damage, 1, false, true);
                    break;
                case 7: // Blödning
                    pierce.bleeding(damage, 2);
                    break;
                case 8: // Blödning
                    pierce.bleeding(damage, 0);
                    break;
                case 9: // Köttsår
                    pierce.flesh(damage, 2);
                    break;
                case 10: // Köttsår
                    pierce.flesh(damage, 0);
                    break;
            }
        }
    }
}

// -------------------------------------------- Cutting --------------------------------------------

void HitTable::DamageTable::Cut::marrow(Damage *damage, int type, bool fall){
    int dmg = damage->damageModified;
    // Benpipa
    damage->areaSub.assign("Benpipa");

    switch (type)
    {
        case 4:
            damage->fast = true;
        case 3: 
            damage->amp = true;
            damage->bryt = true;
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}

        default: damage->addDamage(dmg/10, dmg/2, dmg/10);
    }
}

void HitTable::DamageTable::Cut::muscle(Damage *damage, int type, bool fall){
    int dmg = damage->damageModified;
    // Muskel/Senor
    damage->areaSub.assign("Muskel/Senor");

    switch (type)
    {
        case 3: 
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}
        case 2:
            damage->amp = true;
            damage->bryt = true;

        default: damage->addDamage(dmg/2, dmg/10, dmg/10);
    }
}

void HitTable::DamageTable::Cut::artery(Damage *damage){
    int dmg = damage->damageModified;
    // Artärblödning
    damage->areaSub.assign("Artärblödning");

    damage->addDamage(dmg/10, dmg/10, dmg);
    damage->amp = true;
}

void HitTable::DamageTable::Cut::concussion(Damage *damage, int type, bool vital, bool fall){
    int dmg = damage->damageModified;
    // Omtöckning
    damage->areaSub.assign("Omtöckning");

    int x = 2;
    if (vital)  x = 1;

    switch (type)
    {
        case 3: damage->faller = true;
        case 2: 
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}
        case 1: damage->amp = true;
        default: damage->addDamage(dmg/10, dmg/x, dmg/10);
    }
}

void HitTable::DamageTable::Cut::bleeding(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Blödning
    damage->areaSub.assign("Blödning");

    switch (type)
    {
        case 2: damage->arr = true;
        case 1: damage->amp = true;
        default: damage->addDamage(dmg/10, dmg/10, dmg/2);
    }
}

void HitTable::DamageTable::Cut::flesh(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Köttsår
    damage->areaSub.assign("Köttsår");

    switch (type)
    {
        case 2: damage->arr = true;
        case 1: damage->amp = true;
        default: damage->addDamage(dmg/10, dmg/10, dmg/10);
    }
}

// -------------------------------------------- Crushing --------------------------------------------

void HitTable::DamageTable::Crush::marrow(Damage *damage, int type, bool fall){
    int dmg = damage->damageModified;
    // Benpipa
    damage->areaSub.assign("Benpipa");

    switch (type)
    {
        case 2:
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}
        case 1: damage->bryt = true;
        default: damage->addDamage(dmg/10, dmg/2, 0);
    }
}

void HitTable::DamageTable::Crush::muscle(Damage *damage, int type, bool fall){
    int dmg = damage->damageModified;
    // Muskel/Senor
    damage->areaSub.assign("Muskel/Senor");

    switch (type)
    {
        case 2: 
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}
        case 1:
            damage->men = true;

        default: damage->addDamage(dmg/2, dmg/10, 0);
    }
}

void HitTable::DamageTable::Crush::artery(Damage *damage){
    int dmg = damage->damageModified;
    // Artärblödning
    damage->areaSub.assign("Artärblödning");

    damage->addDamage(dmg/10, dmg/10, dmg);
}

void HitTable::DamageTable::Crush::concussion(Damage *damage, int type, bool vital, bool fall){
    int dmg = damage->damageModified;
    // Omtöckning
    damage->areaSub.assign("Omtöckning");

    int x = 2;
    if (vital)  x = 1;

    switch (type)
    {
        case 2: damage->faller = true;
        case 1: 
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}
        default: damage->addDamage(dmg/10, dmg/x, 0);
    }
}

void HitTable::DamageTable::Crush::bleeding(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Blödning
    damage->areaSub.assign("Blödning");

    switch (type)
    {
        default: damage->addDamage(dmg/10, dmg/10, dmg/2);
    }
}

void HitTable::DamageTable::Crush::flesh(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Köttsår
    damage->areaSub.assign("Köttsår");

    switch (type)
    {
        default: damage->addDamage(dmg/10, dmg/10, 0);
    }
}

// -------------------------------------------- Piercing --------------------------------------------

void HitTable::DamageTable::Pierce::marrow(Damage *damage, int type, bool fall){
    int dmg = damage->damageModified;
    // Benpipa
    damage->areaSub.assign("Benpipa");

    switch (type)
    {
        case 3:
            damage->fast = true;
            damage->bryt = true;
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}

        default: damage->addDamage(dmg/10, dmg/2, dmg/10);
    }
}

void HitTable::DamageTable::Pierce::muscle(Damage *damage, int type, bool fall){
    int dmg = damage->damageModified;
    // Muskel/Senor
    damage->areaSub.assign("Muskel/Senor");

    switch (type)
    {
        case 3: 
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}
        case 2: damage->fast = true;
        case 1: damage->men = true;

        default: damage->addDamage(dmg/2, dmg/10, dmg/10);
    }
}

void HitTable::DamageTable::Pierce::artery(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Artärblödning
    damage->areaSub.assign("Artärblödning");

    switch (type)
    {
        case 1: damage->fast = true;
        default: damage->addDamage(dmg/10, dmg/10, dmg);
    }
}

void HitTable::DamageTable::Pierce::concussion(Damage *damage, int type, bool vital, bool fall){
    int dmg = damage->damageModified;
    // Omtöckning
    damage->areaSub.assign("Omtöckning");

    int x = 2;
    if (vital)  x = 1;

    switch (type)
    {
        case 1: 
            if (fall)  {damage->faller = true;}
            if (!fall) {damage->tappar = true;}
        default: damage->addDamage(dmg/10, dmg/x, dmg/10);
    }
}

void HitTable::DamageTable::Pierce::bleeding(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Blödning
    damage->areaSub.assign("Blödning");

    switch (type)
    {
        case 2: damage->fast = true;
        case 1: damage->arr = true;
        default: damage->addDamage(dmg/10, dmg/10, dmg/2);
    }
}

void HitTable::DamageTable::Pierce::flesh(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Köttsår
    damage->areaSub.assign("Köttsår");

    switch (type)
    {
        case 2:
            damage->fast = true;
            damage->arr = true;
        default: damage->addDamage(dmg/10, dmg/10, dmg/10);
    }
}