#include "character.h"

class combat
{
private:
    /* data */
public:
    Character *team1, *team2;
    Character *attacker, *defender;
    int vinit = 0;

    combat(Character *team1, Character *team2);
    ~combat();

    void nextTurn();
};