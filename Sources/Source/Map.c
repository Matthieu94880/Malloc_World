/*
** Filename : Map.c
**
** Made by : Matthieu BARRIERE
**
** Description : Manages the Malloc_World map content
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

typedef struct {
    Element_Map     element;
    int             min;
}
MandatoryElement;

static struct {
    int beforeResourceReappear;
    int beforeMonsterReappear;
}
playerMoveCount;

static struct {
    int x;
    int y;
}
playerPosition;

/*****************************************************************************
** Returns a randomize number between min and max values
******************************************************************************/
int random(int min, int max) {

    int value;

    if (min >= max) {
        value = min;
    }
    else {
        value = rand();

        value = value % (max+1 - min);
        value = value + min;
    }

    return value;
}

/*****************************************************************************
** Setting a map element to a position.
** For a monster, value is between 12 and 98
** For the player, the zone is empty but the player position is memorized
******************************************************************************/
void setElement_Map(Map * map, int x, int y, Element_Map element) {

    if (map->height > y && y >= 0 &&
        map->width > x && x >= 0) {

        if (element == ELT_MONSTRE) {
            element = random(12, 98);
        }
        else if (element == ELT_JOUEUR) {
            playerPosition.x = x;
            playerPosition.y = y;

            element = ELT_ZONE_LIBRE;
        }

        map->alteredContain[x][y] = element;
    }
}

/*****************************************************************************
** Getting a map element from a position
******************************************************************************/
Element_Map getElement_Map(const Map * map, int x, int y) {

    if (map->height > y && y >= 0 &&
        map->width > x && x >= 0) {

        if (playerPosition.x == x &&
            playerPosition.y == y) {
            return ELT_JOUEUR;
        }

        return map->alteredContain[x][y];
    }

    return ELT_NULL;
}

/*****************************************************************************
** Setting optionals elements into the map
******************************************************************************/
static void setOptionalElements(Map * map) {

    int  elementCount;

    Element_Map optionalElementsZone1[] = {
                ELT_MONSTRE,
                ELT_INFRANCHISSABLE,
                ELT_ZONE_LIBRE,
                ELT_ROCHER_ZONE1,
                ELT_PLANTE_ZONE1,
                ELT_BOIS_ZONE1 };

    Element_Map optionalElementsZone2[] = {
                ELT_MONSTRE,
                ELT_INFRANCHISSABLE,
                ELT_ZONE_LIBRE,
                ELT_ROCHER_ZONE2,
                ELT_PLANTE_ZONE2,
                ELT_BOIS_ZONE2 };

    Element_Map optionalElementsZone3[] = {
                ELT_MONSTRE,
                ELT_INFRANCHISSABLE,
                ELT_ZONE_LIBRE,
                ELT_ROCHER_ZONE3,
                ELT_PLANTE_ZONE3,
                ELT_BOIS_ZONE3 };

    Element_Map * list;

    switch (map->zone) {

        case ZONE1: {
            list = optionalElementsZone1;
            elementCount = sizeof(optionalElementsZone1) / sizeof(Element_Map);
            break;
        }

        case ZONE2: {
            list = optionalElementsZone2;
            elementCount = sizeof(optionalElementsZone2) / sizeof(Element_Map);
            break;
        }

        default: {
            list = optionalElementsZone3;
            elementCount = sizeof(optionalElementsZone3) / sizeof(Element_Map);
        }
    }

    for (int x = 0; x < map->width; x++) {

        for (int y = 0; y < map->height; y++) {

            if (getElement_Map(map, x, y) == ELT_NULL) {

                int indexElt = random(0, elementCount - 1);

                setElement_Map(map, x, y, list[indexElt]);
                map->originalContain[x][y] = map->alteredContain[x][y];
            }
        }
    }
}

/*****************************************************************************
** Setting mandatory elements into the map
** Each elements contains :
** - a minimum number into the map
** - a player for the first zone only (for the others zone, player will be on
**   the portal zone
******************************************************************************/
static void setMandatoryElements(Map * map) {

    int  elementCount;

    MandatoryElement mandatoryElementsZone1[] = {
        /* TYPE                 MIN */
           ELT_MONSTRE        , 10,
           ELT_JOUEUR         ,  1,
           ELT_ROCHER_ZONE1   ,  3,
           ELT_PLANTE_ZONE1   ,  3,
           ELT_BOIS_ZONE1     ,  3,
           ELT_PNJ            ,  1,
           ELT_PORTAIL_ZONE1_2,  1
    };

    MandatoryElement mandatoryElementsZone2[] = {
        /* TYPE                 MIN */
           ELT_MONSTRE        , 10,
           ELT_ROCHER_ZONE2   ,  3,
           ELT_PLANTE_ZONE2   ,  3,
           ELT_BOIS_ZONE2     ,  3,
           ELT_PNJ            ,  1,
           ELT_PORTAIL_ZONE1_2,  1,
           ELT_PORTAIL_ZONE2_3,  1
    };

    MandatoryElement mandatoryElementsZone3[] = {
        /* TYPE                 MIN */
           ELT_MONSTRE        , 10,
           ELT_ROCHER_ZONE3   ,  3,
           ELT_PLANTE_ZONE3   ,  3,
           ELT_BOIS_ZONE3     ,  3,
           ELT_PNJ            ,  1,
           ELT_PORTAIL_ZONE2_3,  1,
           ELT_BOSS           ,  1
    };

    MandatoryElement * list;
        
    switch (map->zone) {

        case ZONE1: {
            list = mandatoryElementsZone1;
            elementCount = sizeof(mandatoryElementsZone1) / sizeof(MandatoryElement);
            break;
        }

        case ZONE2: {
            list = mandatoryElementsZone2;
            elementCount = sizeof(mandatoryElementsZone2) / sizeof(MandatoryElement);
            break;
        }

        default: {
            list = mandatoryElementsZone3;
            elementCount = sizeof(mandatoryElementsZone3) / sizeof(MandatoryElement);
        }
    }

    int freeZoneCount = map->height * map->width;

    for (int idxList = 0; idxList < elementCount; idxList++) {

        for (int idxElt = 0; idxElt < list[idxList].min; idxElt++) {

            /* positionnement aléatoire de l'element dans une des cases restantes de la map */

            char    isZoneFound = 0;
            int     indexFreeZone = 0;
            int     indexSelectedFreeZone = random(0, freeZoneCount - 1);

            for (int x = 0; !isZoneFound && x < map->width; x++) {

                for (int y = 0; !isZoneFound && y < map->height; y++) {

                    if (getElement_Map(map, x, y) == ELT_NULL) {

                        if (indexFreeZone == indexSelectedFreeZone) {

                            setElement_Map(map, x, y, list[idxList].element);
                            map->originalContain[x][y] = map->alteredContain[x][y];
                            isZoneFound = 1;
                            freeZoneCount--;
                        }
                        else {

                            indexFreeZone++;
                        }
                    }
                }
            }
        }
    }
}

/*****************************************************************************
** Setting elements into the map
******************************************************************************/
void set_Map(Map * map) {

    setMandatoryElements(map);
    setOptionalElements(map);
}

/*****************************************************************************
** Map memory allocation and initialization
******************************************************************************/
Map * create_Map(Zone_Map zone, int width, int height) {

    Map * map = (Map*)malloc(sizeof(Map));

    map->zone   = zone;
    map->width  = width;
    map->height = height;

    map->originalContain = malloc(sizeof(Element_Map*) * map->width);
    map->alteredContain  = malloc(sizeof(Element_Map*) * map->width);

    for (int x = 0; x < map->width; x++) {

        map->originalContain[x] = malloc(sizeof(Element_Map) * map->height);
        map->alteredContain[x]  = malloc(sizeof(Element_Map) * map->height);
    }

    for (int x = 0; x < map->width; x++) {

        for (int y = 0; y < map->height; y++) {

            setElement_Map(map, x, y, ELT_NULL);
            map->originalContain[x][y] = map->alteredContain[x][y];
        }
    }

    // Initialisation de la graine par rapport a la date en cours pour les fonctions rand()
    srand((unsigned int)time(NULL));
    
    setPlayerPosition_Map(-1, -1);

    return map;
}

/*****************************************************************************
** Map memory release
******************************************************************************/
void free_Map(Map * map) {

    for (int x = 0; x < map->width; x++) {

        free(map->originalContain[x]);
        free(map->alteredContain[x]);
    }

    free(map->originalContain);
    free(map->alteredContain);
    free(map);

    map = NULL;
}

/*****************************************************************************
** Reappear all original map resources
******************************************************************************/
void reappearResources(Map * map) {

    printf("\nReapparition des ressources");

    for (int y = 0; y < map->height; y++) {

        for (int x = 0; x < map->width; x++) {

            switch (map->originalContain[x][y]) {

            case ELT_PLANTE_ZONE1:
            case ELT_PLANTE_ZONE2:
            case ELT_PLANTE_ZONE3:
            case ELT_ROCHER_ZONE1:
            case ELT_ROCHER_ZONE2:
            case ELT_ROCHER_ZONE3:
            case ELT_BOIS_ZONE1:
            case ELT_BOIS_ZONE2:
            case ELT_BOIS_ZONE3:
                map->alteredContain[x][y] = map->originalContain[x][y];
            }
        }
    }
}

/*****************************************************************************
** Reappear all original map monsters
******************************************************************************/
void reappearMonsters(Map * map) {

    printf("\nReapparition des monstres");

    for (int y = 0; y < map->height; y++) {

        for (int x = 0; x < map->width; x++) {

            if (map->originalContain[x][y] >= 12 && map->originalContain[x][y] <= 98) {
                map->alteredContain[x][y] = map->originalContain[x][y];
            }
        }
    }
}

/*****************************************************************************
** Reappear all original map resources or monsters from move count value
** If isForced is 1, all elements reappear.
** Returns 1 if at least one element as reappeared, else 0
******************************************************************************/
int reappearElement_Map(Map * map, int isForced) {

    int oneElementReappeared = 0;

    if (playerMoveCount.beforeMonsterReappear == 0 || isForced == 1) {
        playerMoveCount.beforeMonsterReappear = 15;
        reappearMonsters(map);
        oneElementReappeared = 1;
    }

    if (playerMoveCount.beforeResourceReappear == 0 || isForced == 1) {
        playerMoveCount.beforeResourceReappear = 10;
        reappearResources(map);
        oneElementReappeared = 1;
    }

    return oneElementReappeared;
}

/*****************************************************************************
** Initializes player move count on the map
******************************************************************************/
void initializeMoveCount_Map() {

    playerMoveCount.beforeMonsterReappear  = 15;
    playerMoveCount.beforeResourceReappear = 10;
}

/*****************************************************************************
** Increment player move count on the map
******************************************************************************/
void incrementMoveCount_Map() {

    playerMoveCount.beforeMonsterReappear--;
    playerMoveCount.beforeResourceReappear--;
}

/*****************************************************************************
** Returns the player position on the map (X value)
******************************************************************************/
int getPlayerPositionX_Map() {

    return playerPosition.x;
}

/*****************************************************************************
** Returns the player position on the map (Y value)
******************************************************************************/
int getPlayerPositionY_Map() {

    return playerPosition.y;
}

/*****************************************************************************
** Sets the player position on the map
******************************************************************************/
void setPlayerPosition_Map(int x, int y) {

    playerPosition.x = x;
    playerPosition.y = y;
}

/*****************************************************************************
** Printing the map content
******************************************************************************/
void print_Map(const Map * map) {

    printf("\n*******************\n");
    printf("Zone : %d (%dx%d)\n", map->zone, map->height, map->width);
    printf("*******************\n");

    printf("PORTAIL_ZONE3   = -3\n");
    printf("PORTAIL_ZONE2   = -2\n");
    printf("INFRANCHISSABLE = -1\n");
    printf("ZONE_LIBRE      =  0\n");
    printf("JOUEUR          =  1\n");
    printf("PNJ             =  2\n");
    printf("PLANTE_ZONE1    =  3\n");
    printf("ROCHER_ZONE1    =  4\n");
    printf("BOIS_ZONE1      =  5\n");
    printf("PLANTE_ZONE2    =  6\n");
    printf("ROCHER_ZONE2    =  7\n");
    printf("BOIS_ZONE2      =  8\n");
    printf("PLANTE_ZONE3    =  9\n");
    printf("ROCHER_ZONE3    = 10\n");
    printf("BOIS_ZONE3      = 11\n");
    printf("MONSTRE         = 12\n");
    printf("BOSS            = 99\n\n");

    for (int y = 0; y < map->height; y++) {

        for (int x = 0; x < map->width; x++) {

            Element_Map elt = getElement_Map(map, x, y);

            if (elt == ELT_NULL) {

                printf("-- ");
            }
            else if (elt < 0) {

                printf("%d ", getElement_Map(map, x, y));
            }
            else {

                printf("%2d ", getElement_Map(map, x, y));
            }
        }

        printf("\n");
    }
}
