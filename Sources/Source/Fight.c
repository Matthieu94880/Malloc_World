/*
** Filename : Fight.c
**
** Made by : Matthieu BARRIERE
**
** Description : Fighting between player and monster/boss
*/

#include "Fight.h"

/*****************************************************************************
** Do the fight. Returns 1 for victory else 0
******************************************************************************/
int do_fight(Player * player, Element_Map element) {

    int isThePlayerWon = 1;

    if (element == ELT_BOSS) {

        // todo : do the fight
        printf("\nCombat avec le boss");
    }
    else {

        // todo : do the fight
        printf("\nCombat avec un monstre");
    }

    return isThePlayerWon;
}
