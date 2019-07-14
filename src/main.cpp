#include "main.h"

int main()
{
    srand(time(0));
    //printf("Rolling: %d\n", dice());

    // Create people
    Creature h1("Arne"), h2("Gunnar");

    h1.attack(h2);

    return 0;
}