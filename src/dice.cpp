#include "dice.h"

int dice(int amount, int type, bool ob) // Antal, ob, typ
{

    int total = 0;
    
    for (int diceLeft = amount; diceLeft > 0; diceLeft --){
        int die = (rand() % type) + 1;

        //printf("Die: %d\n", die);

        if (ob && die == type){
            die = 0;
            diceLeft += 2;
        }

        total += die;
    }

    return total;
}