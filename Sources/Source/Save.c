/*
** Filename : Save.c
**
** Made by : Matthieu BARRIERE
**
** Description : Save or Load a game
*/

#include <stdio.h>
#include <stdlib.h>
#include "Save.h"

/*****************************************************************************
** Saving a map
******************************************************************************/
void saveMap(const Map * map, FILE * fd) {

    for (int y = 0; y < map->height; y++) {

        for (int x = 0; x < map->width; x++) {

            fprintf(fd, "%d ", getElement_Map(map, x, y));
        }

        fprintf(fd, "\n");
    }
}

/*****************************************************************************
** Saving all maps and player datas
******************************************************************************/
void save(const Map * map1, const Map * map2, const Map * map3, const Player * player) {

    FILE * fd;

    printf("\nSauvegarde de la partie");

    fopen_s(&fd, "Malloc_World.sav", "w");

    fprintf(fd, "=== MAP ===\n");

    fprintf(fd, "-- ZONE 1 --\n");
    saveMap(map1, fd);

    fprintf(fd, "-- ZONE 2 --\n");
    saveMap(map2, fd);

    fprintf(fd, "-- ZONE 3 --\n");
    saveMap(map3, fd);

    fprintf(fd, "=== PLAYER ===\n");
    fprintf(fd, "{LEVEL}\n");
    fprintf(fd, "{%d}/{%d}\n", player->xp, player->xpNextLevel);
    fprintf(fd, "{%d}/{%d}\n", player->currHp, player->hpMax);

    fprintf(fd, "-- INVENTORY --\n");
    for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

        if (player->currentInventory[i].id == ITEM_AUCUN) {
            fprintf(fd, "{0}@{0}@{0}\n");
        }
        else {
            const itemList * item = getItem(player->currentInventory[i].id);

            if (item != NULL) {

                if (item->durability == -1) {
                    fprintf(fd, "{%d}@{%d}@{0}\n", player->currentInventory[i].quantity, player->currentInventory[i].id);
                }
                else {
                    fprintf(fd, "{%d}@{%d}@{%.2f}\n", player->currentInventory[i].quantity, player->currentInventory[i].id, player->currentInventory[i].currentDurability);
                }
            }
        }
    }

    fprintf(fd, "-- STORAGE --\n");
    storage * storedItem = player->currentStorage;
    while (storedItem != NULL) {

        fprintf(fd, "{%d}@{%d}\n", storedItem->quantity, storedItem->id);
        storedItem = storedItem->next;
    }

    fclose(fd);

    printf(" : OK");
}

/*****************************************************************************
** Loading a map
******************************************************************************/
void loadMap(Map * map, FILE * fd) {

    for (int y = 0; y < map->height; y++) {

        for (int x = 0; x < map->width; x++) {

            Element_Map element;
            fscanf_s(fd, "%d ", &element);
            setElement_Map(map, x, y, element);
            map->originalContain[x][y] = map->alteredContain[x][y];
        }
    }
}

/*****************************************************************************
** Loading all maps and player from saving files
** Returns 1 if loaded else 0
******************************************************************************/
int load(Map * map1, Map * map2, Map * map3, Player * player) {

    FILE * fd;

    printf("\nChargement de la partie");

    fopen_s(&fd, "Malloc_World.sav", "r");

    if (fd == NULL)
    {
        printf(" : sauvegarde introuvable");
        return 0;
    }
    else
    {
        char chaineLue[65535];

        fgets(chaineLue, 65535, fd); // MAP Header

        fgets(chaineLue, 65535, fd); // ZONE1 Header
        loadMap(map1, fd);

        fgets(chaineLue, 65535, fd); // ZONE2 Header
        loadMap(map2, fd);

        fgets(chaineLue, 65535, fd); // ZONE3 Header
        loadMap(map3, fd);

        fgets(chaineLue, 65535, fd); // PLAYER Header

        fgets(chaineLue, 65535, fd); // LEVEL Header
        fscanf_s(fd, "{%d}/{%d}\n", &player->xp, &player->xpNextLevel);
        fscanf_s(fd, "{%d}/{%d}\n", &player->currHp, &player->hpMax);

        fgets(chaineLue, 65535, fd); // INVENTORY Header

        for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {
            fscanf_s(fd, "{%d}@{%d}@{%f}\n", &player->currentInventory[i].quantity,
                                             &player->currentInventory[i].id,
                                             &player->currentInventory[i].currentDurability);
        }

        fgets(chaineLue, 65535, fd); // STORAGE Header

        int quantity;
        int objectId;
        while (fscanf_s(fd, "{%d}@{%d}\n", &quantity, &objectId) == 2) {

            storage * storedItem = player->currentStorage;

            while (storedItem != NULL && storedItem->id != objectId) {
                storedItem = storedItem->next;
            }

            if (storedItem != NULL) {
                storedItem->quantity = quantity;
            }
            else {
                storedItem = malloc(sizeof(storage));

                storedItem->id = objectId;
                storedItem->quantity = quantity;
                storedItem->next = player->currentStorage;
                player->currentStorage = storedItem;
            }
        }

        fclose(fd);

        printf(" : OK");
        return 1;
    }
}
