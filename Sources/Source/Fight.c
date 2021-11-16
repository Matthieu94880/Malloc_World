/*
** Filename : Fight.c
**
** Made by : Matthieu BARRIERE
**
** Description : Fighting between player and monster/boss
*/

#include <conio.h>

#include "Monster.h"
#include "Fight.h"

/*****************************************************************************
** Receive an attack
******************************************************************************/
static void defense(Player * player, Monster * monster) {

    int damage = random(1, monster->damageMax);

    printf("\n  -> %s attaque ! Le joueur recoit %d de degat", monster->name, damage);

    player->currHp -= damage;

    if (player->currHp < 0) {
        player->currHp = 0;
    }
}

/*****************************************************************************
** Do an attack
******************************************************************************/
static void attack(Player * player, Monster * monster) {

    int weaponCount = 0;

    printf("\nCHOISIR UNE ARME :");

    for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

        if (player->currentInventory[i].id != ITEM_AUCUN) {

            const itemList * item = getItem(player->currentInventory[i].id);

            if (item != NULL && item->type == ITEMTYPE_ARME && player->currentInventory[i].currentDurability > 0) {
                weaponCount++;
                printf("\nF%d - Utiliser %s (durabilite=%.2f degatMax=%d)", weaponCount, item->name, player->currentInventory[i].currentDurability, item->damage);
            }
        }
    }

    if (weaponCount == 0) {
        printf("\n  -> Vous n'avez plus d'arme");
    }
    else {
        int keypress;

        do {
            keypress = _getch();
        }
        while (keypress < 59 || keypress >= 59 + weaponCount);

        int weaponNumber = keypress - 59;

        weaponCount = 0;

        for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

            if (player->currentInventory[i].id != ITEM_AUCUN) {

                const itemList * item = getItem(player->currentInventory[i].id);

                if (item != NULL && item->type == ITEMTYPE_ARME && player->currentInventory[i].currentDurability > 0) {
                    if (weaponNumber == weaponCount) {

                        int damage = random(1, item->damage);

                        printf("\n  -> Le joueur inflige %d de dommage a %s", damage, monster->name);

                        monster->currHp -= damage;
                        player->currentInventory[i].currentDurability--;

                        if (monster->currHp <= 0) {
                            monster->currHp = 0;
                        }
                        else {
                            defense(player, monster);
                        }
                        break;
                    }
                    else {
                        weaponCount++;
                    }
                }
            }
        }
    }
}

/*****************************************************************************
** Seek player
******************************************************************************/
static void seek(Player * player, Monster * monster) {

    int potionCount = 0;

    if (player->currHp >= player->hpMax) {
        printf("\n  -> Vie maximale deja atteinte (%d/%d)", player->currHp, player->hpMax);
        return;
    }

    printf("\nCHOISISSEZ UNE POTION :");

    for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

        if (player->currentInventory[i].id != ITEM_AUCUN) {

            const itemList * item = getItem(player->currentInventory[i].id);

            if (item != NULL && item->type == ITEMTYPE_SOIN && player->currentInventory[i].quantity > 0) {

                potionCount++;
                printf("\nF%d - Utiliser %s (reste=%d)", potionCount, item->name, player->currentInventory[i].quantity);
            }
        }
    }

    if (potionCount == 0) {
        printf("\n  -> Vous n'avez plus de potion pour vous soigner");
    }
    else {
        int potionUsed = 0;
        int keypress;

        while (potionUsed == 0) {

            keypress = _getch();

            if (keypress >= 59 && keypress < 59 + potionCount) {

                int potionNumber = keypress - 59;

                potionCount = 0;

                for (int i = 0; i < INVENTORY_MAX_NUMBER; i++) {

                    if (player->currentInventory[i].id != ITEM_AUCUN) {

                        const itemList * item = getItem(player->currentInventory[i].id);

                        if (item != NULL && item->type == ITEMTYPE_SOIN && player->currentInventory[i].quantity > 0) {

                            if (potionCount == potionNumber) {

                                player->currHp += item->restoring;

                                if (player->currHp > player->hpMax) {
                                    player->currHp = player->hpMax;
                                }

                                player->currentInventory[i].quantity--;

                                printf("\n  -> Soin effectue avec %s (+%d) : vie=%d/%d\n", item->name, item->restoring, player->currHp, player->hpMax);

                                defense(player, monster);
                                potionUsed = 1;
                                break;
                            }
                            else {
                                potionCount++;
                            }
                        }
                    }
                }
            }
        }
    }
}

/*****************************************************************************
** Do the fight. Returns 1 for victory else 0
******************************************************************************/
int do_fight(Player * player, Element_Map element) {

    int keypress;
    int isThePlayerWon = 1;
    int fightEnded = 0;
    int printCommand = 1;

    Monster monster = getMonster(element);

    printf("\n-------------------------------");
    printf("\nCOMBAT AVEC %s (hp=%d xp=%d)", monster.name, monster.currHp, monster.xp);
    printf("\n-------------------------------");

    do {

        if (printCommand) {
            printf("\n\nQUE VOULEZ VOUS FAIRE (vie : JOUEUR=%d %s=%d) ?", player->currHp, monster.name, monster.currHp);
            printf("\nF1  - attaquer %s", monster.name);
            printf("\nF2  - utiliser une potion de soin");
            printf("\nF12 - etat du joueur");
            printf("\nESC - fuire");
        }

        keypress = _getch();

        printCommand = 1;

        switch (keypress) {

        case 59: // F1
            attack(player, &monster);

            if (!isAlive_Player(player)) {
                isThePlayerWon = 0;
                fightEnded = 1;
            }
            else if (monster.currHp == 0) {
                isThePlayerWon = 1;
                fightEnded = 1;
                player->xp += monster.xp;
                printf("\n  -> VICTOIRE ! xp=%d (+%d) !\n", player->xp, monster.xp);

                manageLevelUpgrade_Player(player);
            }

            break;

        case 60: // F2
            seek(player, &monster);
            break;

        case 27: // ESC
            if (random(1, 10) <= 3) { // 30% de chance de partir
                isThePlayerWon = 0;
                fightEnded = 1;
                printf("\n  -> COMBAT ABANDONNE ...\n");
            }
            else {
                printf("\n  -> FUITE RATEE !");
                defense(player, &monster);
            }
            break;

        case 134: // F12 : etat du joueur
            print_Player(player);
            break;

        default:
            printCommand = 0;
        }
    }
    while (!fightEnded);

    return isThePlayerWon;
}
