/*
** Filename : Fight.c
**
** Made by : Matthieu BARRIERE
**
** Description : Fighting between player and monster/boss
*/

#ifndef Fight_h_
#define Fight_h_

#include "Map.h"
#include "Player.h"

/*****************************************************************************
** Do the fight. Returns 1 for victory else 0
******************************************************************************/
int do_fight(Player * player, Element_Map element);

#endif