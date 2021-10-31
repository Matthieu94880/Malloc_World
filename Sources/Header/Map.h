/*
** Filename : Map.h
**
** Made by : Matthieu BARRIERE
**
** Description : Manages the Malloc_World map content
*/

#ifndef Map_h_
#define Map_h_

typedef enum {
    ELT_NULL            = -9,

    ELT_PORTAIL_ZONE2_3 = -3,
    ELT_PORTAIL_ZONE1_2 = -2,
    ELT_INFRANCHISSABLE = -1,
    ELT_ZONE_LIBRE      = 0,
    ELT_JOUEUR          = 1,
    ELT_PNJ             = 2,
    ELT_PLANTE_ZONE1    = 3,
    ELT_ROCHER_ZONE1    = 4,
    ELT_BOIS_ZONE1      = 5,
    ELT_PLANTE_ZONE2    = 6,
    ELT_ROCHER_ZONE2    = 7,
    ELT_BOIS_ZONE2      = 8,
    ELT_PLANTE_ZONE3    = 9,
    ELT_ROCHER_ZONE3    = 10,
    ELT_BOIS_ZONE3      = 11,
    ELT_MONSTRE         = 12,
    ELT_BOSS            = 99
}
Element_Map;

typedef enum {
    ZONE1 = 1,
    ZONE2 = 2,
    ZONE3 = 3
}
Zone_Map;

typedef struct {
    Zone_Map        zone;
    int             width;
    int             height;
    Element_Map **  originalContain;  // contain at started game
    Element_Map **  alteredContain;   // contain after player moving
}
Map;

struct {
    int x;
    int y;
}
playerPosition;

/*****************************************************************************
** Map memory allocation and initialization
******************************************************************************/
Map *   create_Map(Zone_Map zone, int width, int height);

/*****************************************************************************
** Map memory release
******************************************************************************/
void    free_Map(Map * map);

/*****************************************************************************
** Setting elements into the map
******************************************************************************/
void    set_Map(Map * map);

/*****************************************************************************
** Setting a map element to a position.
** For a monster, value is between 12 and 98
******************************************************************************/
void    setElement_Map(Map * map, int x, int y, Element_Map element);

/*****************************************************************************
** Getting a map element from a position
******************************************************************************/
Element_Map getElement_Map(const Map * map, int x, int y);

/*****************************************************************************
** Reappear all original map resources
******************************************************************************/
void    reappearResources_Map(Map * map);

/*****************************************************************************
** Printing the map content
******************************************************************************/
void    print_Map(const Map * map);

#endif