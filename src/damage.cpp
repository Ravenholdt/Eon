#include "damage.h"

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
    }
    
    else if(roll <= 8){
        damage->area.assign("skallen");
    }

    else if(roll <= 10){
        damage->area.assign("halsen");
    }

    return 1;
}

int hitTableAbdomen(Damage *damage)
{
    int roll = dice(1, 10, false);

    if(roll <= 8){
        damage->area.assign("magen");
    }

    else if(roll <= 10){
        damage->area.assign("underlivet");
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

    return 1;
}