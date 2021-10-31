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

void create_MapGraphic(const Map * map);

void free_MapGraphic();

void display_MapGraphic(const Map * map);

void displayZone_MapGraphic(const Map * map, int x, int y);

#endif