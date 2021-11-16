
#ifndef Player_h_
#define Player_h_

//
// Created by theo on 20/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <Item_List.h>

#define INVENTORY_MAX_NUMBER      10
#define INVENTORY_CRAFTMAX_NUMBER 20
#define INVENTORY_NONE_ID          0

/////////////////////////////////////////////////
//Structure of the Player's inventory//
/////////////////////////////////////////////////

typedef struct inventory {
    ItemId id;                      //The id of the item
    float  currentDurability;       //the current durability of the item ( only for type weapon and tools)
    int    quantity;                //the quantity of a crafting ressource (only for crafting ressoruce)
}inventory;

typedef struct storage {
    ItemId id;                      //The id of the item
    int    quantity;                //the quantity of item
    struct storage * next;          //next item (or NULL)
}storage;

/////////////////////////////////////////////////
//Structure of the Player//
/////////////////////////////////////////////////

typedef struct Player {
    int level;                    //the level of the player
    int xp;                       //the quantity of xp
    int xpNextLevel;              //the quantity of xp needed for a level up
    int hpMax;                    //the maximum quantity of life that the player can reach
    int currHp;                   //the current quantity of life of the player
    inventory currentInventory[INVENTORY_MAX_NUMBER]; //the inventory of the player
    storage * currentStorage;     //the item storage of the player
}
Player;

Player *    init_Player();
void        print_Player(const Player * player);
int         isAlive_Player(const Player * player);
int         getLevel_Player(const Player * player);

int         useDamagableItem_Player(Player * player, ItemId itemId, int damagePurcent);
void        useResourceItem_Player(Player * player, ItemId itemId, int quantity);
int         addInventoryItem_Player(Player * player, ItemId itemId);
int         canAddInventoryItem_Player(Player * player, ItemId itemId);
int         haveItem_Player(Player * player, ItemId itemId, int quantity);

void        storeItem_Player(Player * player, ItemId itemId);

void        manageLevelUpgrade_Player(Player * player);

#endif Player_h_