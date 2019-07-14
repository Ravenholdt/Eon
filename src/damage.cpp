#include "damage.h"

void Damage::addDamage(int trauma, int pain, int bleed, int blood){
    this->trauma += trauma;
    this->pain += pain;
    this->bleed += bleed;
    this->blood += blood;
}

int hitTable(Damage *damage)
{
    int roll = dice(1, 100, false);

    if(roll <= 20){ // Head
        hitTableHead(damage);
    }

    else if(roll <= 40){ // Left arm
        hitTableArm(damage, false);
    }
    
    else if(roll <= 60){ // Right arm
        hitTableArm(damage, true);
    }
    
    else if(roll <= 70){ // Chest
        damage->area.assign("bröstkorgen");
        damageTableChest(damage, 'h');
    }
    
    else if(roll <= 80){ // Abdomen 
        hitTableAbdomen(damage);
    }
    
    else if(roll <= 90){ // Left leg
        hitTableLeg(damage, false);
    }
    
    else if(roll <= 100){ // Right leg
        hitTableLeg(damage, true);
    }

    return 1;
}

int hitTableHead(Damage *damage)
{
    int roll = dice(1, 10, false);
    if(roll <= 4){
        damage->area.assign("ansiktet");
        damageTableFace(damage, 'h');
    }
    
    else if(roll <= 8){
        damage->area.assign("skallen");
        damageTableSkull(damage, 'h');
    }

    else if(roll <= 10){
        damage->area.assign("halsen");
        damageTableNeck(damage, 'h');
    }

    return 1;
}

int hitTableAbdomen(Damage *damage)
{
    int roll = dice(1, 10, false);

    if(roll <= 8){
        damage->area.assign("magen");
        damageTableStomach(damage, 'h');
    }

    else if(roll <= 10){
        damage->area.assign("underlivet");
        damageTableGenital(damage, 'h');
    }

    return 1;
}

int hitTableArm(Damage *damage, bool right=false)
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

    damageTableArm(damage, 'h');

    return 1;
}

int hitTableLeg(Damage *damage, bool right=false)
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

    damageTableLeg(damage, 'h');

    return 1;
}

int damageTableFace(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
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
                    damage->areaSub.assign("Käke");
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
                    damageTableCutConcussion(damage, 3);
                    break;
                case 7: // Blödning
                    damageTableCutBleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    damageTableCutFlesh(damage, 2);
                    break;
                case 9: // Köttsår
                    damageTableCutFlesh(damage, 1);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

int damageTableSkull(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
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
                    damageTableCutConcussion(damage, 3);
                    break;
                case 7: // Omtöckning
                    damageTableCutConcussion(damage, 2);
                    break;
                case 8: // Bleeding
                    damageTableCutBleeding(damage, 1);
                    break;
                case 9: // Köttsår
                    damageTableCutFlesh(damage, 2);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

int damageTableNeck(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
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
                case 3: // Skalle
                    damage->fast = true;
                case 4: // Nackkotor
                    damage->areaSub.assign("Nackkotor");
                    damage->addDamage(dmg/2, dmg/2, dmg/10);
                    damage->amp = true;
                    damage->bryt = true;
                case 5: // Pulsåder
                    damage->areaSub.assign("Pulsåder");
                    damage->addDamage(dmg/2, dmg/2, dmg*2);
                    damage->amp = true;
                    break;
                case 6: // Artärblödning
                    damageTableCutArtary(damage);
                    break;
                case 7: // Omtöckning
                    damageTableCutConcussion(damage, 2);
                    break;
                case 8: // Blödning
                    damageTableCutBleeding(damage, 1);
                    break;
                case 9: // Köttsår
                    damageTableCutFlesh(damage, 2);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

int damageTableChest(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
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
                    damageTableCutConcussion(damage, 1);
                    break;
                case 9: // Blödning
                    damageTableCutBleeding(damage, 2);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

int damageTableStomach(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
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
                    break;
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
                    damageTableCutArtary(damage);
                    break;
                case 6: // Omtöckning
                    damageTableCutConcussion(damage, 1);
                    break;
                case 7: // Blödning
                    damageTableCutBleeding(damage, 2);
                    break;
                case 8: // Blödning
                    damageTableCutBleeding(damage, 1);
                    break;
                case 9: // Köttsår
                    damageTableCutFlesh(damage, 2);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

int damageTableGenital(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
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
                    damageTableCutConcussion(damage, 3);
                    break;
                case 4: // Omtöckning
                    damageTableCutConcussion(damage, 2);
                    break;
                case 5: // Blödning
                    damageTableCutBleeding(damage, 2);
                    break;
                case 6: // Blödning
                    damageTableCutBleeding(damage, 2);
                    break;
                case 7: // Blödning
                    damageTableCutBleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    damageTableCutFlesh(damage, 2);
                    break;
                case 9: // Köttsår
                    damageTableCutFlesh(damage, 1);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

int damageTableArm(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    damageTableCutMarrow(damage, 4, false);
                    break;
                case 2: // Benpipa
                    damageTableCutMarrow(damage, 3, false);
                    break;
                case 3: // Artärblödning
                    damageTableCutArtary(damage);
                    break;
                case 4: // Omtöckning
                    damageTableCutMuscle(damage, 3, false);
                    break;
                case 5: // Blödning
                    damageTableCutMuscle(damage, 2, false);
                    break;
                case 6: // Omtöckning
                    damageTableCutConcussion(damage, 2);
                    break;
                case 7: // Blödning
                    damageTableCutBleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    damageTableCutFlesh(damage, 2);
                    break;
                case 9: // Köttsår
                    damageTableCutFlesh(damage, 1);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

int damageTableLeg(Damage *damage, char type){
    int dmg = damage->damageModified;
    if (type == 'h'){
        if ( dmg < 10){
            // Ytlig skada
            damage->areaSub.assign("Ytlig skada");
            damage->addDamage(1,1,1);

        } else { // Serious damage
            int roll = dice(1, 10, false);
            switch (roll)
            {
                case 1: // Benpipa
                    damageTableCutMarrow(damage, 4, true);
                    break;
                case 2: // Benpipa
                    damageTableCutMarrow(damage, 3, true);
                    break;
                case 3: // Artärblödning
                    damageTableCutArtary(damage);
                    break;
                case 4: // Omtöckning
                    damageTableCutMuscle(damage, 3, true);
                    break;
                case 5: // Blödning
                    damageTableCutMuscle(damage, 2, true);
                    break;
                case 6: // Omtöckning
                    damageTableCutConcussion(damage, 2);
                    break;
                case 7: // Blödning
                    damageTableCutBleeding(damage, 1);
                    break;
                case 8: // Köttsår
                    damageTableCutFlesh(damage, 2);
                    break;
                case 9: // Köttsår
                    damageTableCutFlesh(damage, 1);
                    break;
                case 10: // Köttsår
                    damageTableCutFlesh(damage, 0);
                    break;
            }
        }

        return 1;
    }

    return 0;
}

void damageTableCutMarrow(Damage *damage, int type, bool leg){
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
            if (leg)  {damage->faller = true;}
            if (!leg) {damage->tappar = true;}

        default: damage->addDamage(dmg/10, dmg/2, dmg/10);
    }
}

void damageTableCutMuscle(Damage *damage, int type, bool leg){
    int dmg = damage->damageModified;
    // Muskel/Senor
    damage->areaSub.assign("Muskel/Senor");

    switch (type)
    {
        case 3: 
            if (leg)  {damage->faller = true;}
            if (!leg) {damage->tappar = true;}
        case 2:
            damage->amp = true;
            damage->bryt = true;

        default: damage->addDamage(dmg/2, dmg/10, dmg/10);
    }
}

void damageTableCutArtary(Damage *damage){
    int dmg = damage->damageModified;
    // Artärblödning
    damage->areaSub.assign("Artärblödning");

    damage->addDamage(dmg/10, dmg/10, dmg);
    damage->amp = true;
}

void damageTableCutConcussion(Damage *damage, int type){
    int dmg = damage->damageModified;
    // Omtöckning
    damage->areaSub.assign("Omtöckning");

    switch (type)
    {
        case 3: damage->faller = true;
        case 2: damage->tappar = true;
        case 1: damage->amp = true;
        default: damage->addDamage(dmg/10, dmg, dmg/10);
    }
}

void damageTableCutBleeding(Damage *damage, int type){
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

void damageTableCutFlesh(Damage *damage, int type){
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