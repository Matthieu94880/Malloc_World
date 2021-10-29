//
// Created by theo on 20/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

/////////////////////////////////////////////////
//Structure of the itemList //
/////////////////////////////////////////////////

typedef struct itemList {
    int id;
    char name[20];
    char type[20];
    int damage;
    int resistance;
    int restoring;
    int durability;
    struct itemList *next;
}itemList;

itemList *newItem(int id, char name[], char type[], int damage, int resistance, int restoring, int durability);

itemList *initItemList();
itemList *printItemList(itemList *item);
itemList *printCategoryItem(itemList *item, char category[]);