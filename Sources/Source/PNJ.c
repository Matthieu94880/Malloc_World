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

    ItemId itemAvailable[ITEMID_COUNT];
    int itemIdNumber;
    int fin = 0;

    do {
        itemIdNumber = 0;

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_EPEE_BOIS;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 2) && haveItem_Player(player, ITEM_PIERRE, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_EPEE_PIERRE;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_HETRE, 2) && haveItem_Player(player, ITEM_FER, 4) && currentZone > 1) {
            itemAvailable[itemIdNumber++] = ITEM_EPEE_FER;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_CHENE, 2) && haveItem_Player(player, ITEM_DIAMANT, 5) && currentZone > 2) {
            itemAvailable[itemIdNumber++] = ITEM_EPEE_DIAMANT;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 3) && haveItem_Player(player, ITEM_PIERRE, 4)) {
            itemAvailable[itemIdNumber++] = ITEM_LANCE_PIERRE;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_HETRE, 3) && haveItem_Player(player, ITEM_FER, 5) && currentZone > 1) {
            itemAvailable[itemIdNumber++] = ITEM_LANCE_FER;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_CHENE, 3) && haveItem_Player(player, ITEM_DIAMANT, 6) && currentZone > 2) {
            itemAvailable[itemIdNumber++] = ITEM_LANCE_DIAMANT;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 2) && haveItem_Player(player, ITEM_PIERRE, 6)) {
            itemAvailable[itemIdNumber++] = ITEM_MARTEAU_PIERRE;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_HETRE, 2) && haveItem_Player(player, ITEM_FER, 7) && currentZone > 1) {
            itemAvailable[itemIdNumber++] = ITEM_MARTEAU_FER;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_CHENE, 2) && haveItem_Player(player, ITEM_DIAMANT, 8) && currentZone > 2) {
            itemAvailable[itemIdNumber++] = ITEM_MARTEAU_DIAMANT;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_PIERRE, 10)) {
            itemAvailable[itemIdNumber++] = ITEM_PLASTRON_PIERRE;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_FER, 12) && currentZone > 1) {
            itemAvailable[itemIdNumber++] = ITEM_PLASTRON_FER;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_DIAMANT, 16) && currentZone > 2) {
            itemAvailable[itemIdNumber++] = ITEM_PLASTRON_DIAMANT;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_PIOCHE_BOIS;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 2) && haveItem_Player(player, ITEM_PIERRE, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_PIOCHE_PIERRE;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_HETRE, 2) && haveItem_Player(player, ITEM_FER, 4) && currentZone > 1) {
            itemAvailable[itemIdNumber++] = ITEM_PIOCHE_FER;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_HACHE_BOIS;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 2) && haveItem_Player(player, ITEM_PIERRE, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_HACHE_PIERRE;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_HETRE, 2) && haveItem_Player(player, ITEM_FER, 4) && currentZone > 1) {
            itemAvailable[itemIdNumber++] = ITEM_HACHE_FER;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_SERPE_BOIS;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_SAPIN, 2) && haveItem_Player(player, ITEM_PIERRE, 3)) {
            itemAvailable[itemIdNumber++] = ITEM_SERPE_PIERRE;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_HETRE, 2) && haveItem_Player(player, ITEM_FER, 4) && currentZone > 1) {
            itemAvailable[itemIdNumber++] = ITEM_SERPE_FER;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_HERBE, 2)) {
            itemAvailable[itemIdNumber++] = ITEM_POTION_VIE1;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_LAVANDE, 2)) {
            itemAvailable[itemIdNumber++] = ITEM_POTION_VIE2;
        }

        if (canAddInventoryItem_Player(player, ITEM_EPEE_BOIS) && haveItem_Player(player, ITEM_CHANVRE, 2)) {
            itemAvailable[itemIdNumber++] = ITEM_POTION_VIE3;
        }

        if (itemIdNumber == 0) {
            printf("\n  -> Impossible de creer un autre element\n");
            fin = 1;
        }
        else {

            printf("\nQUE VOULEZ VOUS CREER ?");

            printf("\n0 - SORTIR");

            for (int i = 0; i < itemIdNumber; i++) {

                const itemList * item = getItem(itemAvailable[i]);

                if (item != NULL) {
                    printf("\n%d - %s", i+1, item->name);
                }
            }

            printf("\nChoix : ");

            int numberEntered = 0;
            
            scanf_s("%d", &numberEntered);

            if (numberEntered == 0) {
                fin = 1;
            }
            else if (numberEntered <= itemIdNumber) {
                if (addInventoryItem_Player(player, itemAvailable[numberEntered-1]) == 1) {

                    const itemList * item = getItem(itemAvailable[numberEntered-1]);

                    if (item != NULL) {
                        printf("\n  -> %s ajoute dans l'inventaire", item->name);
                    }

                    switch (itemAvailable[numberEntered - 1]) {

                    case ITEM_EPEE_BOIS:
                        useResourceItem_Player(player, ITEM_SAPIN, 3);
                        break;

                    case ITEM_EPEE_PIERRE:
                        useResourceItem_Player(player, ITEM_SAPIN, 2);
                        useResourceItem_Player(player, ITEM_PIERRE, 3);
                        break;

                    case ITEM_EPEE_FER:
                        useResourceItem_Player(player, ITEM_HETRE, 2);
                        useResourceItem_Player(player, ITEM_FER, 4);
                        break;

                    case ITEM_EPEE_DIAMANT:
                        useResourceItem_Player(player, ITEM_CHENE, 2);
                        useResourceItem_Player(player, ITEM_DIAMANT, 5);
                        break;

                    case ITEM_LANCE_PIERRE:
                        useResourceItem_Player(player, ITEM_SAPIN, 3);
                        useResourceItem_Player(player, ITEM_PIERRE, 4);
                        break;

                    case ITEM_LANCE_FER:
                        useResourceItem_Player(player, ITEM_HETRE, 3);
                        useResourceItem_Player(player, ITEM_FER, 5);
                        break;

                    case ITEM_LANCE_DIAMANT:
                        useResourceItem_Player(player, ITEM_CHENE, 3);
                        useResourceItem_Player(player, ITEM_DIAMANT, 6);
                        break;

                    case ITEM_MARTEAU_PIERRE:
                        useResourceItem_Player(player, ITEM_SAPIN, 2);
                        useResourceItem_Player(player, ITEM_PIERRE, 6);
                        break;

                    case ITEM_MARTEAU_FER:
                        useResourceItem_Player(player, ITEM_HETRE, 2);
                        useResourceItem_Player(player, ITEM_FER, 7);
                        break;

                    case ITEM_MARTEAU_DIAMANT:
                        useResourceItem_Player(player, ITEM_CHENE, 2);
                        useResourceItem_Player(player, ITEM_DIAMANT, 8);
                        break;

                    case ITEM_PLASTRON_PIERRE:
                        useResourceItem_Player(player, ITEM_PIERRE, 10);
                        break;

                    case ITEM_PLASTRON_FER:
                        useResourceItem_Player(player, ITEM_FER, 12);
                        break;

                    case ITEM_PLASTRON_DIAMANT:
                        useResourceItem_Player(player, ITEM_DIAMANT, 16);
                        break;

                    case ITEM_PIOCHE_BOIS:
                        useResourceItem_Player(player, ITEM_SAPIN, 3);
                        break;

                    case ITEM_PIOCHE_PIERRE:
                        useResourceItem_Player(player, ITEM_SAPIN, 2);
                        useResourceItem_Player(player, ITEM_PIERRE, 3);
                        break;

                    case ITEM_PIOCHE_FER:
                        useResourceItem_Player(player, ITEM_HETRE, 2);
                        useResourceItem_Player(player, ITEM_FER, 4);
                        break;

                    case ITEM_HACHE_BOIS:
                        useResourceItem_Player(player, ITEM_SAPIN, 3);
                        break;

                    case ITEM_HACHE_PIERRE:
                        useResourceItem_Player(player, ITEM_SAPIN, 2);
                        useResourceItem_Player(player, ITEM_PIERRE, 3);
                        break;

                    case ITEM_HACHE_FER:
                        useResourceItem_Player(player, ITEM_HETRE, 2);
                        useResourceItem_Player(player, ITEM_FER, 4);
                        break;

                    case ITEM_SERPE_BOIS:
                        useResourceItem_Player(player, ITEM_SAPIN, 3);
                        break;

                    case ITEM_SERPE_PIERRE:
                        useResourceItem_Player(player, ITEM_SAPIN, 2);
                        useResourceItem_Player(player, ITEM_PIERRE, 3);
                        break;

                    case ITEM_SERPE_FER:
                        useResourceItem_Player(player, ITEM_HETRE, 2);
                        useResourceItem_Player(player, ITEM_FER, 4);
                        break;

                    case ITEM_POTION_VIE1:
                        useResourceItem_Player(player, ITEM_HERBE, 2);
                        break;

                    case ITEM_POTION_VIE2:
                        useResourceItem_Player(player, ITEM_LAVANDE, 2);
                        break;

                    case ITEM_POTION_VIE3:
                        useResourceItem_Player(player, ITEM_CHANVRE, 2);
                        break;
                    }
                }
                else {
                    printf("\n  -> Ajout impossible : inventaire plein");
                }
            }
        }
    }
    while (!fin);

    printf("\n");
}

/*****************************************************************************
** Stores item
******************************************************************************/
void storeItems(Player * player) {

    int keypress;
    int afficherMenu = 1;

    do {
        if (afficherMenu) {

            printf("\nQUE VOULEZ VOUS STOCKER ?");

            for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

                if (player->currentInventory[i].id != ITEM_AUCUN) {

                    const itemList * item = getItem(player->currentInventory[i].id);

                    if (item != NULL) {

                        printf("\nF%d  - %s (x%d)", i + 1, item->name, player->currentInventory[i].quantity);
                    }
                }
            }

            printf("\nF12 - Etat du joueur");
            printf("\nESC - Sortir\n");
        }

        keypress = _getch();

        afficherMenu = 0;

        if (keypress == 134) { // F12 : etat du joueur
            print_Player(player);
            afficherMenu = 1;
        }
        else {
            int index = keypress - 59;

            if (index >= 0 && index < INVENTORY_MAX_NUMBER) {
                storeItem_Player(player, player->currentInventory[index].id);
                afficherMenu = 1;
            }
        }

    } while (keypress != 27);
}

/*****************************************************************************
** Unstores item
******************************************************************************/
void unstoreItems(Player * player) {

    storage * storedItem;
    int itemNumber = 0;
    int keypress;
    int printCommand = 1;

    do {
        if (printCommand) {

            printf("\nQUE VOULEZ VOUS REPRENDRE ?");

            storedItem = player->currentStorage;
            itemNumber = 0;

            while (storedItem != NULL) {

                if (storedItem->id != ITEM_AUCUN && storedItem->quantity > 0) {

                    const itemList * item = getItem(storedItem->id);

                    if (item != NULL) {

                        printf("\nF%d  - %s (quantite=%d)", itemNumber + 1, item->name, storedItem->quantity);
                        itemNumber++;
                    }
                }

                storedItem = storedItem->next;
            }

            printf("\nF12 - Etat du joueur");
            printf("\nESC - Sortir\n");
        }

        keypress = _getch();

        printCommand = 0;

        if (keypress == 134) { // F12 : etat du joueur
            print_Player(player);
            printCommand = 1;
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
                                printf("\n  -> Reprise de %s\n", item->name);
                                printCommand = 1;
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

    printf("\n");
}

/*****************************************************************************
** Repairs all items
******************************************************************************/
void repairItems(Player * player) {

    for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

        if (player->currentInventory[i].id != ITEM_AUCUN) {

            const itemList * item = getItem(player->currentInventory[i].id);

            if (item != NULL) {

                if (player->currentInventory[i].currentDurability < item->durability)
                {
                    player->currentInventory[i].currentDurability = item->durability;
                    printf("\n  -> Reparation de %s", item->name);
                }
            }
        }
    }

    printf("\n  -> Tous les outils sont repares\n");
}

/*****************************************************************************
** Interaction with non playable character
******************************************************************************/
void interact_PNJ(Player * player, Zone_Map currentZone) {

    int keypress;
    int printCommand = 1;

    printf("\n-------------");
    printf("\nMAISON DU PNJ");
    printf("\n-------------");

    do {
        if (printCommand) {

            printf("\nQUE VOULEZ VOUS FAIRE ?");
            printf("\nF1  - creer objet");
            printf("\nF2  - stocker objet");
            printf("\nF3  - reprendre objet");
            printf("\nF4  - reparer les objets");
            printf("\nF12 - etat du joueur");
            printf("\nESC - quitter le PNJ\n");
        }

        keypress = _getch();

        printCommand = 1;

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

        case 62: // F4
            repairItems(player);
            break;

        case 134: // F12 : etat du joueur
            print_Player(player);
            break;

        default:
            printCommand = 0;
        }
    } while (keypress != 27);

    printf("\nA BIENTOT !\n");
}
