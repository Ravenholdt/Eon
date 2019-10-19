#include "character.h"

class Combat
{
private:
    /* data */
public:
    Character *team1, *team2;
    Character *attacker, *defender;
    int vinit = 0;

    int round = 0;

    Combat(Character *team1, Character *team2);
    ~Combat();

    bool nextTurn();
};