
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

/////////////////////////////////////////////////
//Structure of the Player's inventory//
/////////////////////////////////////////////////

typedef struct inventory {
    int id;                         //The id of the item
    char name[20];                 //The name of the item
    char type[20];                 //The type of the item(weapon,tools,armor,crafting ressource,heal)
    int damage;                     //the damage of the item(only for type  weapon)
    int resistance;                 //the percentage of damage reduction (only for type armor)
    int restoring;                  //the number of HP that the item restore (only for type heal)
    int durabilityMax;              //the number of use of an item ( only for type weapon and tools)
    int currentDurability;          //the current durability of the item ( only for type weapon and tools)
    int quantity;                   //the quantity of a crafting ressource (only for crafting ressoruce)
}inventory;

/////////////////////////////////////////////////
//Structure of the Player//
/////////////////////////////////////////////////

typedef struct Player {
    int level;                      //the level of the player
    float xp;                       //the quantity of xp
    int xpNextLevel;                //the quantity of xp needed for a level up
    int hpMax;                      //the maximum quantity of life that the player can reach
    float currHp;                   //the current quantity of life of the player
    int movingCount;
    inventory CurrentInventory;     //the inventory of the player

}
Player;

Player *    init_Player();

void        initializeMovingCount_Player(Player * player);
void        incrementMovingCount_Player(Player * player);
int         getMovingCount_Player(const Player * player);

int         isAlive_Player(Player * player);

#endif Player_h_