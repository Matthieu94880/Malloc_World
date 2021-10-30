//
// Created by theo on 20/10/2021.
//
#include "../header/player.h"
#include "../header/item_list.h"
//init the player with beggining values
Player *initPlayer() {
    Player *Hero = malloc(sizeof(Player));
    Hero->level = 1;
    Hero->xp = 0;
    Hero->xpNextLevel=100;
    Hero->hpMax = 100;
    Hero->currHp = 100;

    return Hero;
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