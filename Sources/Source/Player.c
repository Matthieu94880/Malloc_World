//
// Created by theo on 20/10/2021.
//
#include <conio.h>
#include "player.h"
#include "item_list.h"

//init the player with beggining values
Player * init_Player() {
    Player *Hero = malloc(sizeof(Player));
    Hero->level = 1;
    Hero->xp = 0;
    Hero->xpNextLevel = 100;
    Hero->hpMax = 100;
    Hero->currHp = 100;
    Hero->currentStorage = NULL;

    for (int i = 0; i < INVENTORY_MAX_NUMBER; i++)
    {
        Hero->currentInventory[i].id = ITEM_AUCUN;
    }

    addInventoryItem_Player(Hero, ITEM_EPEE_BOIS);
    addInventoryItem_Player(Hero, ITEM_PIOCHE_BOIS);
    addInventoryItem_Player(Hero, ITEM_SERPE_BOIS);
    addInventoryItem_Player(Hero, ITEM_HACHE_BOIS);

    return Hero;
}

/*****************************************************************************
** Manages player level upgrade after a fight
******************************************************************************/
void manageLevelUpgrade_Player(Player * player) {
    if (player->xp >= player->xpNextLevel) {
        player->level++;

        switch (player->level) {
        case 2:  player->hpMax += 10; break;
        case 3:  player->hpMax += 20; break;
        case 4:  player->hpMax += 30; break;
        case 5:  player->hpMax += 40; break;
        case 6:  player->hpMax += 50; break;
        case 7:  player->hpMax += 50; break;
        case 8:  player->hpMax += 50; break;
        default: player->hpMax += 75; break;
        }

        player->xpNextLevel += 100; // common for all level
        player->currHp = player->hpMax;

        printf("\nNiveau %d atteint ! (vie=%d)", player->level, player->currHp);
    }
}

/*****************************************************************************
** Uses an item and sets a damage : returns 1 if success else 0
******************************************************************************/
int useDamagableItem_Player(Player * player, ItemId itemId, int damagePurcent) {
    int isUsed = 0;
    int isCancelled = 0;

    const itemList * item = getItem(itemId);

    if (item != NULL)
    {
        float damage = (item->durability * damagePurcent) / 100;

        for (int i = 0; i < INVENTORY_MAX_NUMBER && !isUsed && !isCancelled; i++) {

            if (player->currentInventory[i].id == itemId &&
                player->currentInventory[i].currentDurability >= damage) {

                printf("\nUtiliser %s (durabilite=%.2f dommage=%.2f) ? (o/n) ", item->name, player->currentInventory[i].currentDurability, damage);

                int reponse;
                
                do {
                    reponse = _getch();
                } while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N');

                if (reponse == 'o' || reponse == 'O') {
                    player->currentInventory[i].currentDurability -= damage;
                    isUsed = 1;
                }
                else {
                    isCancelled = 1;
                }
            }
        }
    }

    return isUsed;
}

/*****************************************************************************
** Uses a quantity of resource item
******************************************************************************/
void useResourceItem_Player(Player * player, ItemId itemId, int quantity) {

    for (int i = 0; i < INVENTORY_MAX_NUMBER && quantity > 0; i++) {

        if (player->currentInventory[i].id == itemId) {

            if (player->currentInventory[i].quantity > 0) {
                if (player->currentInventory[i].quantity >= quantity) {
                    player->currentInventory[i].quantity -= quantity;
                    quantity = 0;
                }
                else {
                    quantity -= player->currentInventory[i].quantity;
                    player->currentInventory[i].quantity = 0;
                }
            }
        }
    }
}

/*****************************************************************************
** Adds item into inventory : returns 1 if success else 0
******************************************************************************/
int addInventoryItem_Player(Player * player, ItemId itemId)
{
    int isAdded = 0;

    const itemList * item = getItem(itemId);

    if (item != NULL)
    {
        // try to complete craft into inventory (20 max)
        if (item->type == ITEMTYPE_CRAFT) {

            for (int i = 0; i < INVENTORY_MAX_NUMBER && !isAdded; i++) {

                if (player->currentInventory[i].id == item->id &&
                    player->currentInventory[i].quantity < INVENTORY_CRAFTMAX_NUMBER) {

                    isAdded = 1;
                    player->currentInventory[i].quantity++;
                }
            }
        }

        // try to add a new inventory item
        if (isAdded == 0) {

            for (int i = 0; i < INVENTORY_MAX_NUMBER && !isAdded; i++) {

                if (player->currentInventory[i].id == ITEM_AUCUN) {

                    isAdded = 1;
                    player->currentInventory[i].id = item->id;
                    player->currentInventory[i].currentDurability = item->durability;
                    player->currentInventory[i].quantity = 1;
                }
            }

        }
    }

    return isAdded;
}

/*****************************************************************************
** Returns 1 if item can be added into inventory else 0
******************************************************************************/
int canAddInventoryItem_Player(Player * player, ItemId itemId)
{
    int canAdd = 0;

    const itemList * item = getItem(itemId);

    if (item != NULL)
    {
        // try to complete craft into inventory (20 max)
        if (item->type == ITEMTYPE_CRAFT) {

            for (int i = 0; i < INVENTORY_MAX_NUMBER && !canAdd; i++) {

                if (player->currentInventory[i].id == item->id &&
                    player->currentInventory[i].quantity < INVENTORY_CRAFTMAX_NUMBER) {

                    canAdd = 1;
                }
            }
        }

        // try to add a new inventory item
        if (canAdd == 0) {

            for (int i = 0; i < INVENTORY_MAX_NUMBER && !canAdd; i++) {

                if (player->currentInventory[i].id == ITEM_AUCUN) {

                    canAdd = 1;
                }
            }

        }
    }

    return canAdd;
}

/*****************************************************************************
** Adds an item into storage
******************************************************************************/
void storeItem_Player(Player * player, ItemId itemId) {

    int isAdd = 0;

    const itemList * item = getItem(itemId);

    if (item != NULL) {

        if (item->type == ITEMTYPE_CRAFT) {

            for (int i = 0; i < INVENTORY_MAX_NUMBER && !isAdd; i++) {

                if (player->currentInventory[i].id == itemId &&
                    player->currentInventory[i].quantity > 0) {

                    player->currentInventory[i].quantity--;

                    if (player->currentInventory[i].quantity == 0) {
                        player->currentInventory[i].id = ITEM_AUCUN;
                    }
                    isAdd = 1;
                }
            }
        }
        else {

            for (int i = 0; i < INVENTORY_MAX_NUMBER && !isAdd; i++) {

                if (player->currentInventory[i].id == itemId) {
                    player->currentInventory[i].id = ITEM_AUCUN;
                    isAdd = 1;
                }
            }
        }
    }

    if (isAdd) {

        printf("\n  -> Stockage de %s\n", item->name);

        storage * storedItem = player->currentStorage;

        while (storedItem != NULL && storedItem->id != itemId) {
            storedItem = storedItem->next;
        }

        if (storedItem != NULL) {
            storedItem->quantity++;
        }
        else {
            storedItem = malloc(sizeof(storage));

            storedItem->id = itemId;
            storedItem->quantity = 1;
            storedItem->next = player->currentStorage;
            player->currentStorage = storedItem;
        }
    }
}

/*****************************************************************************
** Returns 1 if the player have a quantity of item into current inventory
******************************************************************************/
int haveItem_Player(Player * player, ItemId itemId, int quantity) {

    int haveItem = 1;

    for (int i = 0; i < INVENTORY_MAX_NUMBER && quantity > 0; i++) {

        if (player->currentInventory[i].id == itemId) {
            quantity -= player->currentInventory[i].quantity;
        }
    }

    if (quantity > 0) {
        haveItem = 0;
    }

    return haveItem;
}

/*****************************************************************************
** Print the current player status
******************************************************************************/
void print_Player(const Player * player) {
    printf("\nETAT DU JOUEUR : xp=%d/%d hp=%d/%d level=%d", player->xp, player->xpNextLevel, player->currHp, player->hpMax, player->level);

    for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

        if (player->currentInventory[i].id == ITEM_AUCUN) {
            printf("\n - Inventaire %d : aucun", i+1);
        }
        else {

            const itemList * item = getItem(player->currentInventory[i].id);

            if (item != NULL) {
                if (item->type == ITEMTYPE_CRAFT || item->type == ITEMTYPE_SOIN) {
                    printf("\n - Inventaire %d : %s [%s] quantite=%d", i + 1, item->name, item->typeLabel, player->currentInventory[i].quantity);
                }
                else {
                    printf("\n - Inventaire %d : %s [%s] durabilite=%.1f", i + 1, item->name, item->typeLabel, player->currentInventory[i].currentDurability);
                }
            }
        }
    }

    storage * storedItem = player->currentStorage;

    while (storedItem != NULL) {
        const itemList * item = getItem(storedItem->id);

        if (item != NULL) {
            if (storedItem->quantity > 0) {
                printf("\n - Stockage : %d x %s [%s]", storedItem->quantity, item->name, item->typeLabel);
            }
            storedItem = storedItem->next;
        }
    }
    printf("\n");
}

/*****************************************************************************
** Returns 1 if the player is still alive
******************************************************************************/
int isAlive_Player(const Player * player) {
    return player->currHp == 0 ? 0 : 1;
}

/*****************************************************************************
** Returns the player level
******************************************************************************/
int getLevel_Player(const Player * player) {
    return player->level;
}

//modify the armor of the Player
Player modifyArmor(Player *Hero, int idArmor, itemList *item) {
    /*if (idArmor == 0) {
        Hero->currentArmor = idArmor;
        Hero->armorName[0] = '\0';
    } else {
        int test;
        while (item != NULL || test != 1) {
            if (idArmor == item->id) {
                int i;
                Hero->currentArmor = idArmor;
                for (i = 0; item->name[i] != '\0'; ++i) {
                    Hero->armorName[i] = item->name[i];
                }
                Hero->armorName[i] = item->name[i];
                test = 1;
            }
            item = item->next;
        }
    }*/

    return *Hero;
}


//print the actual armor of the Player
void printArmor(Player *hero) {
    /*
    if (hero->currentArmor == 0) {
        printf("Le glandu la il a pas d'armure  bahahaha\n");
    } else {
        printf("LE PREUX CHEVALIER A CETTE ARMURE: ");
        for (int i = 0; hero->armorName[i] != '\0'; ++i) {
            printf("%c", hero->armorName[i]);
        }
        printf("\n");
    }
     */
}