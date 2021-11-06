/*
** Filename : PNJ.c
**
** Made by : Matthieu BARRIERE
**
** Description : Non playable character
*/

#include <conio.h>
#include "Player.h"
#include "PNJ.h"

/*****************************************************************************
** Creates item
******************************************************************************/
void createItems(Player * player, Zone_Map currentZone) {

    printf("\nQue voulez vous creer ?");

    // todo
}

/*****************************************************************************
** Stores item
******************************************************************************/
void storeItems(Player * player) {

    int keypress;

    do {
        printf("\nQuel objet voulez vous stocker ? (ESC=sortir)");

        for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

            if (player->currentInventory[i].id != ITEM_AUCUN) {

                const itemList * item = getItem(player->currentInventory[i].id);

                if (item != NULL) {

                    printf("\nF%d - %s (quantite=%d)", i+1, item->name, player->currentInventory[i].quantity);
                }
            }
        }

        printf("\nF12 - etat du joueur");
        printf("\nChoix : ");

        keypress = _getch();

        if (keypress == 134) { // F12 : etat du joueur
            print_Player(player);
        }
        else {
            int index = keypress - 59;

            if (index >= 0 && index < INVENTORY_MAX_NUMBER) {
                storeItem_Player(player, player->currentInventory[index].id);
            }
        }

    } while (keypress != 27);
}

/*****************************************************************************
** Unstores item
******************************************************************************/
void unstoreItems(Player * player) {

    int keypress;

    do {
        printf("\nQue voulez vous reprendre ? (ESC=sortir)");

        storage * storedItem = player->currentStorage;
        int itemNumber = 0;

        while (storedItem != NULL) {

            if (storedItem->id != ITEM_AUCUN && storedItem->quantity > 0) {

                const itemList * item = getItem(storedItem->id);

                if (item != NULL) {

                    printf("\nF%d - %s (quantite=%d)", itemNumber + 1, item->name, storedItem->quantity);
                    itemNumber++;
                }
            }

            storedItem = storedItem->next;
        }

        printf("\nF12 - etat du joueur");
        printf("\nChoix : ");

        keypress = _getch();

        if (keypress == 134) { // F12 : etat du joueur
            print_Player(player);
        }
        else {
            int index = keypress - 59;

            storedItem = player->currentStorage;

            itemNumber = 0;

            while (storedItem != NULL) {

                if (storedItem->id != ITEM_AUCUN && storedItem->quantity > 0) {
                    const itemList * item = getItem(storedItem->id);

                    if (item != NULL) {
                        if (itemNumber == index) {
                            if (addInventoryItem_Player(player, item->id) == 1) {
                                storedItem->quantity--;
                                printf("\nItem %s mis dans l'inventaire", item->name);
                                break;
                            }
                        }
                        itemNumber++;
                    }
                }

                storedItem = storedItem->next;
            }
        }
    } while (keypress != 27);
}

/*****************************************************************************
** Interaction with non playable character
******************************************************************************/
void interact_PNJ(Player * player, Zone_Map currentZone) {

    int keypress;

    printf("\nPNJ : Bienvenue !");

    do {
        printf("\nQue voulez vous faire ? (ESC=sortir)");
        printf("\nF1 - creer objet");
        printf("\nF2 - stocker objet");
        printf("\nF3 - reprendre objet");
        printf("\nF12 - etat du joueur");


        keypress = _getch();

        switch (keypress) {

        case 59: // F1
            createItems(player, currentZone);
            break;

        case 60: // F2
            storeItems(player);
            break;

        case 61: // F3
            unstoreItems(player);
            break;

        case 134: // F12 : etat du joueur
            print_Player(player);
        }
    } while (keypress != 27);

    printf("\nPNJ : A bientot");
}
