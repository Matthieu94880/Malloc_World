/*
** Filename : MallocWorld.c
**
** Made by : Matthieu BARRIERE
**
** Description : Contains the MallocWorld game engine
*/

#include <stdio.h>
#include <conio.h>
#include "Player.h"
#include "Map.h"
#include "MapGraphic.h"
#include "MallocWorld.h"

static Map * mapZone1 = NULL;
static Map * mapZone2 = NULL;
static Map * mapZone3 = NULL;
static Map * currentMap = NULL;

/*****************************************************************************
** Fighting with a monster or a boss
******************************************************************************/
static void fight(Player * player, Element_Map element, int x, int y) {

    int isThePlayerWon = 1;

    if (element == ELT_BOSS) {

        // todo : do the fight
        printf("\nCombat avec le boss");
    }
    else {

        // todo : do the fight
        printf("\nCombat avec un monstre");
    }

    if (isThePlayerWon) {

        int oldPlayerPosX = playerPosition.x;
        int oldPlayerPosY = playerPosition.y;

        playerPosition.x = x;
        playerPosition.y = y;

        setElement_Map(currentMap, x, y, ELT_ZONE_LIBRE);
        displayZone_MapGraphic(currentMap, x, y);
        displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);

        printf(" : victoire !");
    }
    else {

        printf(" : joueur mort");
        _getch();
    }
}

/*****************************************************************************
** Travel between zone 1 and 2
******************************************************************************/
static void changeZone1_2(Player * player) {

    if (currentMap == mapZone1) {

        printf("\nPortail zone 1 -> 2");

        currentMap = mapZone2;
    }
    else {

        printf("\nPortail zone 2 -> 1");

        currentMap = mapZone1;
    }

    Element_Map elt = ELT_NULL;

    for (int x = 0; x < currentMap->width && elt != ELT_PORTAIL_ZONE1_2; x++) {

        for (int y = 0; y < currentMap->height && elt != ELT_PORTAIL_ZONE1_2; y++) {

            elt = getElement_Map(currentMap, x, y);

            if (elt == ELT_PORTAIL_ZONE1_2) {

                playerPosition.x = x;
                playerPosition.y = y;
            }
        }
    }

    initializeMovingCount_Player(player);
    display_MapGraphic(currentMap);
}

/*****************************************************************************
** Travel between zone 2 and 3
******************************************************************************/
static void changeZone2_3(Player * player)
{
    if (currentMap == mapZone2) {

        printf("\nPortail zone 2 -> 3");

        currentMap = mapZone3;
    }
    else {

        printf("\nPortail zone 3 -> 2");

        currentMap = mapZone2;
    }

    Element_Map elt = ELT_NULL;

    for (int x = 0; x < currentMap->width && elt != ELT_PORTAIL_ZONE2_3; x++) {

        for (int y = 0; y < currentMap->height && elt != ELT_PORTAIL_ZONE2_3; y++) {

            elt = getElement_Map(currentMap, x, y);

            if (elt == ELT_PORTAIL_ZONE2_3) {

                playerPosition.x = x;
                playerPosition.y = y;
            }
        }
    }

    initializeMovingCount_Player(player);
    display_MapGraphic(currentMap);
}

/*****************************************************************************
** Interaction with non playable character
******************************************************************************/
static void interactPNJ(Player * player, int x, int y) {

    printf("\nPersonnage Non Joueur (PNJ)");

    // todo : do the interaction

    int oldPlayerPosX = playerPosition.x;
    int oldPlayerPosY = playerPosition.y;

    playerPosition.x = x;
    playerPosition.y = y;

    displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);
    displayZone_MapGraphic(currentMap, x, y);
}

/*****************************************************************************
** Getting rock resource
******************************************************************************/
static void getRock(Player * player, int x, int y) {

    int isGetted = 1;

    printf("\nRecolte pierre");

    // todo : getting the rock

    if (isGetted) {

        int oldPlayerPosX = playerPosition.x;
        int oldPlayerPosY = playerPosition.y;

        playerPosition.x = x;
        playerPosition.y = y;

        setElement_Map(currentMap, x, y, ELT_ZONE_LIBRE);
        displayZone_MapGraphic(currentMap, x, y);
        displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);

        printf(" : obtenue");
    }
    else {

        printf(" : non obtenue");
    }
}

/*****************************************************************************
** Getting grass resource
******************************************************************************/
static void getGrass(Player * player, int x, int y) {

    int isGetted = 1;

    printf("\nRecolte herbe");

    // todo : getting the grass

    if (isGetted) {

        int oldPlayerPosX = playerPosition.x;
        int oldPlayerPosY = playerPosition.y;

        playerPosition.x = x;
        playerPosition.y = y;

        setElement_Map(currentMap, x, y, ELT_ZONE_LIBRE);
        displayZone_MapGraphic(currentMap, x, y);
        displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);

        printf(" : obtenue");
    }
    else {

        printf(" : non obtenue");
    }
}

/*****************************************************************************
** Getting wood resource
******************************************************************************/
static void getWood(Player * player, int x, int y) {

    int isGetted = 1;

    printf("\nRecolte bois");

    // todo : getting the wood

    if (isGetted) {

        int oldPlayerPosX = playerPosition.x;
        int oldPlayerPosY = playerPosition.y;

        playerPosition.x = x;
        playerPosition.y = y;

        setElement_Map(currentMap, x, y, ELT_ZONE_LIBRE);
        displayZone_MapGraphic(currentMap, x, y);
        displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);

        printf(" : obtenue");
    }
    else {

        printf(" : non obtenue");
    }
}

/*****************************************************************************
** Moving to free zone
******************************************************************************/
static void moveFreeZone(Player * player, int x, int y) {

    int oldPlayerPosX = playerPosition.x;
    int oldPlayerPosY = playerPosition.y;

    playerPosition.x = x;
    playerPosition.y = y;

    displayZone_MapGraphic(currentMap, x, y);
    displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);
}

/*****************************************************************************
** Move the player to a new position on the current map
******************************************************************************/
static void movePlayer(Player * player, int x, int y) {

    Element_Map nextElement = getElement_Map(currentMap, x, y);

    if (nextElement == ELT_INFRANCHISSABLE) {

        printf("\nZone infranchissable");
    }
    else {

        incrementMovingCount_Player(player);

        if (nextElement >= 12 && nextElement <= 98) {

            fight(player, nextElement, x, y);
        }
        else switch (nextElement) {

        case ELT_PORTAIL_ZONE1_2:
            changeZone1_2(player);
            break;

        case ELT_PORTAIL_ZONE2_3:
            changeZone2_3(player);
            break;

        case ELT_PNJ:
            interactPNJ(player, x, y);
            break;

        case ELT_ROCHER_ZONE1:
        case ELT_ROCHER_ZONE2:
        case ELT_ROCHER_ZONE3:
            getRock(player, x, y);
            break;

        case ELT_PLANTE_ZONE1:
        case ELT_PLANTE_ZONE2:
        case ELT_PLANTE_ZONE3:
            getGrass(player, x, y);
            break;

        case ELT_BOIS_ZONE1:
        case ELT_BOIS_ZONE2:
        case ELT_BOIS_ZONE3:
            getWood(player, x, y);
            break;

        case ELT_BOSS:
            fight(player, nextElement, x, y);
            break;

        case ELT_ZONE_LIBRE:
            moveFreeZone(player, x, y);
            break;
        }

        if (getMovingCount_Player(player) == 10) {

            initializeMovingCount_Player(player);
            reappearResources_Map(currentMap);
            display_MapGraphic(currentMap);
        }
    }
}

/*****************************************************************************
** Display the help menu
******************************************************************************/
void printHelp() {

    printf("\n******** COMMANDES *********");
    printf("\nFleches : deplacer le joueur");
    printf("\nF1      : afficher la zone 1");
    printf("\nF2      : afficher la zone 2");
    printf("\nF3      : afficher la zone 3");
    printf("\nF12     : aide");
    printf("\nESC     : quitter la partie");
    printf("\n****************************");
}

/*****************************************************************************
** Run the game
******************************************************************************/
void play_MallocWorld() {

    int keyPressed;
    int height = 20;
    int width  = 20;

    Player * player = init_Player();

    mapZone1 = create_Map(ZONE1, width, height);
    mapZone2 = create_Map(ZONE2, width, height);
    mapZone3 = create_Map(ZONE3, width, height);

    set_Map(mapZone1);
    set_Map(mapZone2);
    set_Map(mapZone3);

    currentMap = mapZone1;

    create_MapGraphic(currentMap);
    display_MapGraphic(currentMap);

    printHelp();

    do {

        Element_Map     nextElement = ELT_NULL;
        int             x = playerPosition.x;
        int             y = playerPosition.y;

        keyPressed = _getch();

        switch (keyPressed) {

        case 72: // up
            movePlayer(player, x, --y);
            break;

        case 80: // down
            movePlayer(player, x, ++y);
            break;

        case 75: // left
            movePlayer(player, --x, y);
            break;

        case 77: // right
            movePlayer(player, ++x, y);
            break;

        case 59: // F1
            print_Map(mapZone1);
            break;

        case 60: // F2
            print_Map(mapZone2);
            break;

        case 61: // F3
            print_Map(mapZone3);
            break;

        case 134: // F12
            printHelp();
            break;
        }
    }
    while (keyPressed != 27 && isAlive_Player(player));

    free_MapGraphic();

    free_Map(mapZone3);
    free_Map(mapZone2);
    free_Map(mapZone1);
}