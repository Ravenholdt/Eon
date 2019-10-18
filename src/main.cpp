#include "main.h"
#include "combat.h"

int main()
{
    srand(time(0));
    //printf("Rolling: %d\n", dice());

    // Create people
    Character h1("Arne"), h2("Gunnar");

    int round = 0;

    while(1){
        round ++;

        std::cout << " " << round << std::endl;
        h1.attack(&h2);
        sleep(1);
        std::cout << "--------------------------------" << std::endl;
        h2.attack(&h1);
        sleep(2);
        std::cout << "------------------------------";
    }
    

    return 0;
}