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
#include "Save.h"
#include "Map.h"
#include "MapGraphic.h"
#include "Fight.h"
#include "PNJ.h"
#include "MallocWorld.h"

static Map * mapZone1 = NULL;
static Map * mapZone2 = NULL;
static Map * mapZone3 = NULL;
static Map * currentMap = NULL;

/*****************************************************************************
** Fighting with a monster or a boss
******************************************************************************/
static void fight(Player * player, Element_Map element, int x, int y) {

    int isThePlayerWon;

    isThePlayerWon = do_fight(player, element);

    if (isThePlayerWon) {

        int oldPlayerPosX = getPlayerPositionX_Map();
        int oldPlayerPosY = getPlayerPositionY_Map();

        setPlayerPosition_Map(x, y);

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
** Travel between zone 1 and 2 : returns 1 if travel is done else 0
******************************************************************************/
static int changeZone1_2(Player * player) {

    int isTravelDone = 1;

    if (currentMap == mapZone1) {

        printf("\nPortail zone 1 -> 2");

        if (getLevel_Player(player) < 3) {

            printf(" : le niveau 3 est recommande. Voyager quand meme ? (o/n)");

            int reponse;

            do {
                reponse = _getch();
            } while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N');

            if (reponse == 'n' || reponse == 'N') {
                isTravelDone = 0;
            }
        }

        if (isTravelDone) {
            currentMap = mapZone2;
        }
    }
    else {

        printf("\nPortail zone 2 -> 1");

        currentMap = mapZone1;
    }

    if (isTravelDone) {

        Element_Map elt = ELT_NULL;

        for (int x = 0; x < currentMap->width && elt != ELT_PORTAIL_ZONE1_2; x++) {

            for (int y = 0; y < currentMap->height && elt != ELT_PORTAIL_ZONE1_2; y++) {

                elt = getElement_Map(currentMap, x, y);

                if (elt == ELT_PORTAIL_ZONE1_2) {

                    setPlayerPosition_Map(x, y);
                }
            }
        }

        initializeMoveCount_Map();
        reappearElement_Map(currentMap, 1);
        display_MapGraphic(currentMap);
    }

    return isTravelDone;
}

/*****************************************************************************
** Travel between zone 2 and 3 : returns 1 if travel is done else 0
******************************************************************************/
static int changeZone2_3(Player * player)
{
    int isTravelDone = 1;

    if (currentMap == mapZone2) {

        printf("\nPortail zone 2 -> 3");

        if (getLevel_Player(player) < 7) {

            printf(" : le niveau 7 est obligatoire");
            isTravelDone = 0;
        }

        if (isTravelDone) {
            currentMap = mapZone3;
        }
    }
    else {

        printf("\nPortail zone 3 -> 2");

        currentMap = mapZone2;
    }

    if (isTravelDone) {

        Element_Map elt = ELT_NULL;

        for (int x = 0; x < currentMap->width && elt != ELT_PORTAIL_ZONE2_3; x++) {

            for (int y = 0; y < currentMap->height && elt != ELT_PORTAIL_ZONE2_3; y++) {

                elt = getElement_Map(currentMap, x, y);

                if (elt == ELT_PORTAIL_ZONE2_3) {

                    setPlayerPosition_Map(x, y);
                }
            }
        }

        initializeMoveCount_Map();
        reappearElement_Map(currentMap, 1);
        display_MapGraphic(currentMap);
    }

    return isTravelDone;
}

/*****************************************************************************
** Interaction with non playable character
******************************************************************************/
static void interactPNJ(Player * player, int x, int y) {

    interact_PNJ(player, currentMap->zone);

    int oldPlayerPosX = getPlayerPositionX_Map();
    int oldPlayerPosY = getPlayerPositionY_Map();

    setPlayerPosition_Map(x, y);

    displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);
    displayZone_MapGraphic(currentMap, x, y);
}

/*****************************************************************************
** Getting rock resource : returns 1 if getted else 0
******************************************************************************/
static int getRock(Player * player, int x, int y) {

    ItemId  itemToAdd = ITEM_AUCUN;
    int     isGetted = 0;

    if (currentMap->zone == ZONE1) {

        printf("\nRecolte pierre : ");
        itemToAdd = ITEM_PIERRE;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_PIOCHE_BOIS, 10)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_PIOCHE_PIERRE, 10)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_PIOCHE_FER, 10)) {
                isGetted = 1;
            }
        }
    }
    else if (currentMap->zone == ZONE2) {

        printf("\nRecolte fer : ");
        itemToAdd = ITEM_FER;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_PIOCHE_PIERRE, 20)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_PIOCHE_FER, 20)) {
                isGetted = 1;
            }
        }
    }
    else {

        printf("\nRecolte diamant : ");
        itemToAdd = ITEM_DIAMANT;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_PIOCHE_FER, 40)) {
                isGetted = 1;
            }
        }
    }

    if (isGetted) {

        int maxItemCount = random(1, 4);
        int itemCount = 0;

        for (int i = 0; i < maxItemCount; i++) {

            if (addInventoryItem_Player(player, itemToAdd)) {
                itemCount++;
            }
        }

        int oldPlayerPosX = getPlayerPositionX_Map();
        int oldPlayerPosY = getPlayerPositionY_Map();

        setPlayerPosition_Map(x, y);

        setElement_Map(currentMap, x, y, ELT_ZONE_LIBRE);
        displayZone_MapGraphic(currentMap, x, y);
        displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);

        printf("=> obtenue (x%d)", itemCount);
    }
    else {

        printf("=> non obtenue");
    }

    return isGetted;
}

/*****************************************************************************
** Getting grass resource : returns 1 if getted else 0
******************************************************************************/
static int getGrass(Player * player, int x, int y) {

    ItemId  itemToAdd = ITEM_AUCUN;
    int     isGetted = 0;

    if (currentMap->zone == ZONE1) {

        printf("\nRecolte herbe : ");
        itemToAdd = ITEM_HERBE;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_SERPE_BOIS, 10)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_SERPE_PIERRE, 10)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_SERPE_FER, 10)) {
                isGetted = 1;
            }
        }
    }
    else if (currentMap->zone == ZONE2) {

        printf("\nRecolte lavande : ");
        itemToAdd = ITEM_LAVANDE;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_SERPE_PIERRE, 20)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_SERPE_FER, 20)) {
                isGetted = 1;
            }
        }
    }
    else {

        printf("\nRecolte chanvre : ");
        itemToAdd = ITEM_CHANVRE;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_SERPE_FER, 40)) {
                isGetted = 1;
            }
        }
    }

    if (isGetted) {

        int maxItemCount = random(1, 4);
        int itemCount = 0;

        for (int i = 0; i < maxItemCount; i++) {

            if (addInventoryItem_Player(player, itemToAdd)) {
                itemCount++;
            }
        }

        int oldPlayerPosX = getPlayerPositionX_Map();
        int oldPlayerPosY = getPlayerPositionY_Map();

        setPlayerPosition_Map(x, y);

        setElement_Map(currentMap, x, y, ELT_ZONE_LIBRE);
        displayZone_MapGraphic(currentMap, x, y);
        displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);

        printf("=> obtenue (x%d)", itemCount);
    }
    else {

        printf("=> non obtenue");
    }

    return isGetted;
}

/*****************************************************************************
** Getting wood resource : returns 1 if getted else 0
******************************************************************************/
static int getWood(Player * player, int x, int y) {

    ItemId  itemToAdd = ITEM_AUCUN;
    int     isGetted = 0;

    if (currentMap->zone == ZONE1) {

        printf("\nRecolte sapin : ");
        itemToAdd = ITEM_SAPIN;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_HACHE_BOIS, 10)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_HACHE_PIERRE, 10)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_HACHE_FER, 10)) {
                isGetted = 1;
            }
        }
    }
    else if (currentMap->zone == ZONE2) {

        printf("\nRecolte hetre : ");
        itemToAdd = ITEM_HETRE;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_HACHE_PIERRE, 20)) {
                isGetted = 1;
            }
            else if (useDamagableItem_Player(player, ITEM_HACHE_FER, 20)) {
                isGetted = 1;
            }
        }
    }
    else {

        printf("\nRecolte chene : ");
        itemToAdd = ITEM_CHENE;

        if (canAddInventoryItem_Player(player, itemToAdd)) {

            if (useDamagableItem_Player(player, ITEM_HACHE_FER, 40)) {
                isGetted = 1;
            }
        }
    }

    if (isGetted) {

        int maxItemCount = random(1, 4);
        int itemCount = 0;

        for (int i = 0; i < maxItemCount; i++) {

            if (addInventoryItem_Player(player, itemToAdd)) {
                itemCount++;
            }
        }

        int oldPlayerPosX = getPlayerPositionX_Map();
        int oldPlayerPosY = getPlayerPositionY_Map();

        setPlayerPosition_Map(x, y);

        setElement_Map(currentMap, x, y, ELT_ZONE_LIBRE);
        displayZone_MapGraphic(currentMap, x, y);
        displayZone_MapGraphic(currentMap, oldPlayerPosX, oldPlayerPosY);

        printf("=> obtenue (x%d)", itemCount);
    }
    else {

        printf("=> non obtenue");
    }

    return isGetted;
}

/*****************************************************************************
** Moving to free zone
******************************************************************************/
static void moveFreeZone(Player * player, int x, int y) {

    int oldPlayerPosX = getPlayerPositionX_Map();
    int oldPlayerPosY = getPlayerPositionY_Map();

    setPlayerPosition_Map(x, y);

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

        int hasMoved = 1;

        if (nextElement >= 12 && nextElement <= 98) {

            fight(player, nextElement, x, y);
        }
        else switch (nextElement) {

        case ELT_PORTAIL_ZONE1_2:
            hasMoved = changeZone1_2(player);
            break;

        case ELT_PORTAIL_ZONE2_3:
            hasMoved = changeZone2_3(player);
            break;

        case ELT_PNJ:
            interactPNJ(player, x, y);
            break;

        case ELT_ROCHER_ZONE1:
        case ELT_ROCHER_ZONE2:
        case ELT_ROCHER_ZONE3:
            hasMoved = getRock(player, x, y);
            break;

        case ELT_PLANTE_ZONE1:
        case ELT_PLANTE_ZONE2:
        case ELT_PLANTE_ZONE3:
            hasMoved = getGrass(player, x, y);
            break;

        case ELT_BOIS_ZONE1:
        case ELT_BOIS_ZONE2:
        case ELT_BOIS_ZONE3:
            hasMoved = getWood(player, x, y);
            break;

        case ELT_BOSS:
            fight(player, nextElement, x, y);
            break;

        case ELT_ZONE_LIBRE:
            moveFreeZone(player, x, y);
            break;

        default:
            hasMoved = 0;
        }

        if (hasMoved)
        {
            incrementMoveCount_Map();

            if (reappearElement_Map(currentMap, 0) == 1)
            {
                display_MapGraphic(currentMap);
            }
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
    printf("\nF4      : etat du joueur");
    printf("\nF9      : charger sauvegarde");
    printf("\nF10     : sauvegarder");
    printf("\nF12     : aide");
    printf("\nESC     : quitter la partie");
    printf("\n****************************");
}

/*****************************************************************************
** Run the game
******************************************************************************/
void play_MallocWorld() {

    int keyPressed;

    Player * player = init_Player();

    initializeMoveCount_Map();

    mapZone1 = create_Map(ZONE1, 10, 10);
    mapZone2 = create_Map(ZONE2, 10, 20);
    mapZone3 = create_Map(ZONE3, 20, 20);

    set_Map(mapZone1);
    set_Map(mapZone2);
    set_Map(mapZone3);

    currentMap = mapZone1;

    create_MapGraphic(currentMap);
    display_MapGraphic(currentMap);

    printHelp();

    do {

        Element_Map     nextElement = ELT_NULL;
        int             x = getPlayerPositionX_Map();
        int             y = getPlayerPositionY_Map();

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

        case 62: // F4
            print_Player(player);
            break;

        case 67: // F9
            if (load(mapZone1, mapZone2, mapZone3, player) == 1)
            {
                display_MapGraphic(currentMap);
            }
            break;

        case 68: // F10
            save(mapZone1, mapZone2, mapZone3, player);
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