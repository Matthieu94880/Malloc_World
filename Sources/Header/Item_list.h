//
// Created by theo on 20/10/2021.
//

#ifndef Item_List_h_
#define Item_List_h_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    ITEM_AUCUN = 0,
    ITEM_EPEE_BOIS,
    ITEM_PIOCHE_BOIS,
    ITEM_SERPE_BOIS,
    ITEM_HACHE_BOIS,
    ITEM_SAPIN,
    ITEM_PIERRE,
    ITEM_HERBE,
    ITEM_EPEE_PIERRE,
    ITEM_LANCE_PIERRE,
    ITEM_MARTEAU_PIERRE,
    ITEM_PLASTRON_PIERRE,
    ITEM_PIOCHE_PIERRE,
    ITEM_SERPE_PIERRE,
    ITEM_HACHE_PIERRE,
    ITEM_POTION_VIE1,
    ITEM_HETRE,
    ITEM_FER,
    ITEM_LAVANDE,
    ITEM_EPEE_FER,
    ITEM_LANCE_FER,
    ITEM_MARTEAU_FER,
    ITEM_PLASTRON_FER,
    ITEM_PIOCHE_FER,
    ITEM_SERPE_FER,
    ITEM_HACHE_FER,
    ITEM_POTION_VIE2,
    ITEM_CHENE,
    ITEM_DIAMANT,
    ITEM_CHANVRE,
    ITEM_EPEE_DIAMANT,
    ITEM_LANCE_DIAMANT,
    ITEM_MARTEAU_DIAMANT,
    ITEM_PLASTRON_DIAMANT,
    ITEM_POTION_VIE3
}
ItemId;

typedef enum {
    ITEMTYPE_ARME,
    ITEMTYPE_ARMURE,
    ITEMTYPE_OUTIL,
    ITEMTYPE_SOIN,
    ITEMTYPE_CRAFT
}
ItemType;

/////////////////////////////////////////////////
//Structure of the itemList //
/////////////////////////////////////////////////

typedef struct itemList {
    ItemId              id;
    ItemType            type;
    char                name[20];
    char                typeLabel[20];
    int                 damage;
    int                 resistance;
    int                 restoring;
    float               durability;
    struct itemList *   next;
}itemList;

itemList *newItem(ItemId id, ItemType type, char name[], char typeLabel[], int damage, int resistance, int restoring, float durability);

itemList *initItemList();
itemList *printItemList(itemList *item);
itemList *printCategoryItem(itemList *item, ItemType category);

const itemList *getItem(ItemId itemId);

#endif