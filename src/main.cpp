#include <stdio.h>
#include <iostream>

#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

#include <string> //Strings

#include "main.h"

int dice(int amount = 3, int type = 6, bool ob = true) // Antal, ob, typ
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

class Creature
{
    public:
        std::string name;
        int id = 0;

        int utmattning = 0;

        int undvik = 12;
        int vapen = 12;

        int smarta = 0;
        int trauma = 0;

        Creature(std::string name) 
        {
            this->name = name;
        }

        void attack(Creature enemy)
        {
            std::cout << this->name << " attackerar " << enemy.name << "." << std::endl;

            if (vapen >= dice()){ // Attacker hits
                if (!enemy.defence()) // Defender fails
                {
                    std::cout << this->name << " träffar " << enemy.name << " i " << std::endl;
                    hitTable();
                }
                else
                {
                    std::cout << enemy.name << " lyckas unvika " << this->name << "s attack." << std::endl;
                }
            }
            else
            {
                std::cout << this->name << " missar totalt." << std::endl;
            }
        }

        bool defence()
        {
            if (undvik >= dice()) return true;

            return false;
        }
};

int hitTable()
{
    int roll = dice(1, 100, false);

    if(roll <= 20){ 
        printf("Huvud\n"); 
        {
            int roll = dice(1, 10, false);
            if(roll <= 4){
                printf("Ansikte\n");
            }
            
            else if(roll <= 8){
                printf("Skalle\n");
            }

            else if(roll <= 10){
                printf("Hals\n");
            }
        }
    }

    else if(roll <= 40){ 
        printf("Vänster Arm\n");
        {
            int roll = dice(1, 10, false);

            if(roll <= 2){
                printf("Skuldra\n");
            }

            else if(roll <= 4){
                printf("Överarm\n");
            }

            else if(roll <= 5){
                printf("Armbåge\n");
            }

            else if(roll <= 8){
                printf("Underarm\n");
            }

            else if(roll <= 10){
                printf("Hand\n");
            }
        }
    }
    
    else if(roll <= 60){ 
        printf("Höger Arm\n"); 
        {
            int roll = dice(1, 10, false);

            if(roll <= 2){
                printf("Skuldra\n");
            }

            else if(roll <= 4){
                printf("Överarm\n");
            }

            else if(roll <= 5){
                printf("Armbåge\n");
            }

            else if(roll <= 8){
                printf("Underarm\n");
            }

            else if(roll <= 10){
                printf("Hand\n");
            }
        }
    }
    
    else if(roll <= 70){ 
        printf("Bröstkorg\n"); 
    }
    
    else if(roll <= 80){ 
        printf("Buk\n"); 
        {
            int roll = dice(1, 10, false);

            if(roll <= 8){
                printf("Mage\n");
            }

            else if(roll <= 10){
                printf("Underliv\n");
            }
        }
    }
    
    else if(roll <= 90){ 
        printf("Vänster Ben\n"); 
        {
            int roll = dice(1, 10, false);

            if(roll <= 2){
                printf("Höft\n");
            }

            else if(roll <= 4){
                printf("Lår\n");
            }

            else if(roll <= 6){
                printf("Knä\n");
            }

            else if(roll <= 9){
                printf("Vad\n");
            }

            else if(roll <= 10){
                printf("Fot\n");
            }
        }
    }
    
    else if(roll <= 100){ 
        printf("Höger Ben\n"); 
    }

    return 1;
}

int main()
{
    srand(time(0));
    //printf("Rolling: %d\n", dice());

    // Create people
    Creature h1("Arne"), h2("Gunnar");

    h1.attack(h2);

    //hitTable();

    return 0;
}