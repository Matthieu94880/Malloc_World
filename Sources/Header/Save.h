/*
** Filename : Save.c
**
** Made by : Matthieu BARRIERE
**
** Description : Save or Load a game
*/

#ifndef Save_h_
#define Save_h_

#include "Map.h"
#include "Player.h"

/*****************************************************************************
** Saving all maps and player datas
******************************************************************************/
void save(const Map * map1, const Map * map2, const Map * map3, const Player * player);

/*****************************************************************************
** Loading all maps and player from saving files
** Returns 1 if loaded else 0
******************************************************************************/
int  load(Map * map1, Map * map2, Map * map3, Player * player);

#endif