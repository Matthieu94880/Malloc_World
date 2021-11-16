/*
** Filename : Monster.c
**
** Made by : Matthieu BARRIERE
**
** Description : Manages monster
*/

#include "Monster.h"

static Monster monsterList[] = {
  // ELT    NAME        HP   XP DAMAGE
    { 12, "BOUSTIFLOR",  2,  10,  2 },
    { 13, "NOADKOKO",    5,  20,  7 },
    { 14, "MYSTHERBE",   1,   6,  1 },
    { 15, "VACILYS",     4,  15,  5 },
    { 16, "PARAS",       1,   5,  1 },
    { 17, "KECLEON",     4,  12,  6 },
    { 18, "OBALIE",      4,  14,  7 },
    { 98, "ARBOK",      20, 100, 20 }
};

static int monsterCount = sizeof(monsterList) / sizeof(Monster);

/*****************************************************************************
** Returns monster properties from map element number
******************************************************************************/
Monster getMonster(Element_Map element) {

    for (int i = 0; i < monsterCount; i++) {
        if (element == monsterList[i].elementNumber) {
            return monsterList[i];
        }
    }

    return monsterList[0];
}

/*****************************************************************************
** Returns 1 if map element is a monster, otherwise 0
******************************************************************************/
int isMonster(Element_Map element) {

    if (element >= 12 && element <= 98) {
        return 1;
    }

    return 0;
}
