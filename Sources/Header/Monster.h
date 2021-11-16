/*
** Filename : Monster.h
**
** Made by : Matthieu BARRIERE
**
** Description : Manages monster
*/

#ifndef Monster_h_
#define Monster_h_

#include "Map.h"

typedef struct {
    Element_Map elementNumber;
    char *      name;
    int         currHp;
    int         xp;
    int         damageMax;
}
Monster;

/*****************************************************************************
** Returns monster properties from map element number
******************************************************************************/
Monster getMonster(Element_Map element);

/*****************************************************************************
** Returns 1 if map element is a monster, otherwise 0
******************************************************************************/
int isMonster(Element_Map element);

#endif