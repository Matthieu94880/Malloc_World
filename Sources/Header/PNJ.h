/*
** Filename : PNJ.h
**
** Made by : Matthieu BARRIERE
**
** Description : Non playable character
*/

#ifndef PNJ_h_
#define PNJ_h_

#include "Player.h"
#include "Map.h"

/*****************************************************************************
** Interaction with non playable character
******************************************************************************/
void interact_PNJ(Player * player, Zone_Map currentZone);

#endif