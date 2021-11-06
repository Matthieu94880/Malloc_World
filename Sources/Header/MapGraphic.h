/*
** Filename : MapGraphic.h
**
** Made by : Matthieu BARRIERE
**
** Description : Display the Malloc_World map with SDL graphic library
*/

#ifndef MapGraphic_h_
#define MapGraphic_h_

#include "Map.h"

/*****************************************************************************
** SDL memory allocation. Loading pictures and create main graphic window
******************************************************************************/
void create_MapGraphic(const Map * map);

/*****************************************************************************
** SDL memory release
******************************************************************************/
void free_MapGraphic();

/*****************************************************************************
** Displays all the map
******************************************************************************/
void display_MapGraphic(const Map * map);

/*****************************************************************************
** Displays a specific map zone and refresh the window
******************************************************************************/
void displayZone_MapGraphic(const Map * map, int x, int y);

#endif