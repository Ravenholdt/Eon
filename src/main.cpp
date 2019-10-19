#include "main.h"
#include "combat.h"

int main()
{
    srand(time(0));
    //printf("Rolling: %d\n", dice());

    // Create people
    Character h1("Arne"), h2("Gunnar");
    Combat combat(&h1, &h2);

    bool fight = true;
    while(fight){
        fight = combat.nextTurn();
        sleep(2);
    }

    std::cout << "Simulation has ended." << std::endl;
    

    return 0;
}