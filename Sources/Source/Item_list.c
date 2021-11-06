//
// Created by theo on 20/10/2021.
//
#include "../header/item_list.h"
//add an element in the itemList

static itemList * list = NULL;

itemList *newItem(ItemId id, ItemType type, char name[], char typeLabel[], int damage, int resistance, int restoring, float durability) {
    itemList *temp = malloc(sizeof(itemList));
    temp->id = id;
    temp->type = type;
    int i;
    for (i = 0; name[i] != '\0'; ++i) {
        temp->name[i] = name[i];

    }
    temp->name[i] = name[i];
    for (i = 0; typeLabel[i] != '\0'; ++i) {
        temp->typeLabel[i] = typeLabel[i];
    }
    temp->typeLabel[i] = typeLabel[i];
    temp->damage = damage;
    temp->resistance = resistance;
    temp->restoring = restoring;
    temp->durability = durability;
    temp->next = NULL;
    return temp;
}

//init the itemList
itemList *initItemList() {
    itemList *tmp;
    itemList *head = newItem(ITEM_EPEE_BOIS, ITEMTYPE_ARME, "Epee en bois", "Arme", 1, -1, -1, 10);
    tmp = head;
    head->next = newItem(ITEM_PIOCHE_BOIS, ITEMTYPE_OUTIL, "Pioche en bois", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_SERPE_BOIS, ITEMTYPE_OUTIL, "Serpe en bois", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_HACHE_BOIS, ITEMTYPE_OUTIL, "Hache en bois", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_SAPIN, ITEMTYPE_CRAFT, "Sapin", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_PIERRE, ITEMTYPE_CRAFT, "Pierre", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_HERBE, ITEMTYPE_CRAFT, "Herbe", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_EPEE_PIERRE, ITEMTYPE_ARME, "Epee en pierre", "Arme", 2, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_LANCE_PIERRE, ITEMTYPE_ARME, "Lance en pierre", "Arme", 3, -1, -1, 8);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_MARTEAU_PIERRE, ITEMTYPE_ARME, "Marteau en pierre", "Arme", 4, -1, -1, 5);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_PLASTRON_PIERRE, ITEMTYPE_ARMURE, "Plastron en pierre", "Armure", -1, 10, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_PIOCHE_PIERRE, ITEMTYPE_OUTIL, "Pioche en pierre", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_SERPE_PIERRE, ITEMTYPE_OUTIL, "Serpe en pierre", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_HACHE_PIERRE, ITEMTYPE_OUTIL, "Hache en pierre", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_POTION_VIE1, ITEMTYPE_SOIN, "Potion de vie I", "Soin", -1, -1, 30, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_HETRE, ITEMTYPE_CRAFT, "Hetre", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_FER, ITEMTYPE_CRAFT, "Fer", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_LAVANDE, ITEMTYPE_CRAFT, "Lavande", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_EPEE_FER, ITEMTYPE_ARME, "Epee en fer", "Arme", 5, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_LANCE_FER, ITEMTYPE_ARME, "Lance en fer", "Arme", 7, -1, -1, 8);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_MARTEAU_FER, ITEMTYPE_ARME, "Marteau en fer", "Arme", 10, -1, -1, 5);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_PLASTRON_FER, ITEMTYPE_ARMURE, "Plastron en fer", "Armure", -1, 20, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_PIOCHE_FER, ITEMTYPE_OUTIL, "Pioche en fer", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_SERPE_FER, ITEMTYPE_OUTIL, "Serpe en fer", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_HACHE_FER, ITEMTYPE_OUTIL, "Hache en fer", "Outil", -1, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_POTION_VIE2, ITEMTYPE_SOIN, "Potion de vie II", "Soin", -1, -1, 80, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_CHENE, ITEMTYPE_CRAFT, "Chene", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_DIAMANT, ITEMTYPE_CRAFT, "Diamant", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_CHANVRE, ITEMTYPE_CRAFT, "Chanvre", "Ressource de craft", -1, -1, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_EPEE_DIAMANT, ITEMTYPE_ARME, "Epee en diamant", "Arme", 10, -1, -1, 10);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_LANCE_DIAMANT, ITEMTYPE_ARME, "Lance en diamant", "Arme", 15, -1, -1, 8);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_MARTEAU_DIAMANT, ITEMTYPE_ARME, "Marteau en diamant", "Arme", 20, -1, -1, 5);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_PLASTRON_DIAMANT, ITEMTYPE_ARMURE, "Plastron en diamant", "Armure", -1, 40, -1, -1);
    tmp = tmp->next;
    tmp->next = newItem(ITEM_POTION_VIE3, ITEMTYPE_SOIN, "Potion de vie III", "Soin", -1, -1, 200, -1);
    return head;
};

//print the item
void printItem(itemList *item) {
    printf("\n-------------------------------------------------------------------\n\n");
    printf("cet item est le numero %d de la liste \n", item->id);
    printf("cet item s'appelle: %s", item->name);
    printf("\ncet item est du type: %s ", item->typeLabel);
    if (item->type == ITEMTYPE_ARME) {
        printf("\ncet item fait %d de degat\n", item->damage);
        printf("cet item a %f de durabilite maximum\n", item->durability);
    }
    else if (item->type == ITEMTYPE_OUTIL) {
        printf("\ncet item a %f de durabilite maximum\n", item->durability);
    }
    else if (item->type == ITEMTYPE_CRAFT) {
        printf("\n");
    }
    else if (item->type == ITEMTYPE_ARMURE) {
        printf("\ncet item permet de resister a %d %% de degat maximum\n", item->resistance);
    }
    else if (item->type == ITEMTYPE_SOIN) {
        printf("\ncet item permet de soigner un maximum de %d de HP\n", item->restoring);
    }
    else {
        printf("\nPas de type trouver a cette item\n");
    }
}

//print the item list
itemList *printItemList(itemList *item) {
    while (item != NULL) {
        printItem(item);
        item = item->next;
    }
    printf("\n-------------------------------------------------------------------\n\n");

	return NULL;
}

//print the item list filtered by a category
itemList *printCategoryItem(itemList *item, ItemType category) {
    int compteur = 0;
    while (item != NULL) {
        if (item->type == category) {
            printItem(item);
        }
        compteur += 1;
        item = item->next;
    }
    printf("Nombre trouve = %d", compteur);
    printf("\n-------------------------------------------------------------------\n\n");

	return NULL;
}

/*****************************************************************************
** Returns an item from id
******************************************************************************/
const itemList * getItem(ItemId itemId)
{
    if (list == NULL) {

        list = initItemList();
    }

    itemList * item = list;

    while (item != NULL && item->id != itemId) {
        item = item->next;
    }

    return item;
}