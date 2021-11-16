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
    ELT_MONSTRE1        = 12,
    ELT_MONSTRE2        = 13,
    ELT_MONSTRE3        = 14,
    ELT_MONSTRE4        = 15,
    ELT_MONSTRE5        = 16,
    ELT_MONSTRE6        = 17,
    ELT_MONSTRE7        = 18,
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
    Element_Map **  originalContain;  // contain at started of game (used for reappears)
    Element_Map **  alteredContain;   // contain after player moving
}
Map;

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
** Initializes player move count on the map
******************************************************************************/
void    initializeMoveCount_Map();

/*****************************************************************************
** Increment player move count on the map
******************************************************************************/
void    incrementMoveCount_Map();

/*****************************************************************************
** Reappear all original map resources or monsters from move count value
** If isForced is 1, all elements reappear (map travel)
** Returns 1 if at least one element as reappeared, else 0
******************************************************************************/
int     reappearElement_Map(Map * map, int isForced);

/*****************************************************************************
** Returns the player position on the map (X value)
******************************************************************************/
int     getPlayerPositionX_Map();

/*****************************************************************************
** Returns the player position on the map (Y value)
******************************************************************************/
int     getPlayerPositionY_Map();

/*****************************************************************************
** Sets the player position on the map
******************************************************************************/
void    setPlayerPosition_Map(int x, int y);

/*****************************************************************************
** Printing the map content
******************************************************************************/
void    print_Map(const Map * map);

/*****************************************************************************
** Returns a randomize number between min and max values
******************************************************************************/
int     random(int min, int max);

#endif