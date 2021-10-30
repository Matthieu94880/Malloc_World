#include <stdio.h>
#include <conio.h>
#include "MapGraphic.h"
#include "Action.h"

static void Combattre(Player * player, Element_Map element)
{
    printf("\nCombat");
}

static void FranchirPortailZone1_2(Player * player)
{
    printf("\nPortail zone 1<->2");
}

static void FranchirPortailZone2_3(Player * player)
{
    printf("\nPortail zone 2<->3");
}

static void InteragirAvecPNJ(Player * player)
{
    printf("\nPersonnage Non Joueur (PNJ)");
}

static void RecolterPierre(Player * player)
{
    printf("\nRecolte pierre");
}

static void RecolterHerbe(Player * player)
{
    printf("\nRecolte herbe");
}

static void RecolterBois(Player * player)
{
    printf("\nRecolte bois");
}

int InteragirAvecElement(Player * player, Element_Map element)
{
    int interactionPossible = 1;

    // Monstre ?
    if (element >= 12 && element <= 98)
    {
        Combattre(player, element);
    }
    else
    {
        switch (element)
        {
        case ELT_PORTAIL_ZONE1_2:
            FranchirPortailZone1_2(player);
            break;

        case ELT_PORTAIL_ZONE2_3:
            FranchirPortailZone2_3(player);
            break;

        case ELT_PNJ:
            InteragirAvecPNJ(player);
            break;

        case ELT_ROCHER_ZONE1:
        case ELT_ROCHER_ZONE2:
        case ELT_ROCHER_ZONE3:
            RecolterPierre(player);
            break;

        case ELT_PLANTE_ZONE1:
        case ELT_PLANTE_ZONE2:
        case ELT_PLANTE_ZONE3:
            RecolterHerbe(player);
            break;

        case ELT_BOIS_ZONE1:
        case ELT_BOIS_ZONE2:
        case ELT_BOIS_ZONE3:
            RecolterBois(player);
            break;

        case ELT_BOSS:
            Combattre(player, element);
            break;

        case ELT_ZONE_LIBRE:
            break;

        case ELT_INFRANCHISSABLE:
        default:
            printf("\nZone infranchissable");
            interactionPossible = 0;
        }
    }

    return interactionPossible;
}

void Jouer_Action(Map * map, Player * player)
{
    int keyPressed;

    printf("\n****** COMMANDES ******");
    printf("\nFleches : deplacer le joueur");
    printf("\nQ       : quitter la partie");
    printf("\n***********************");

    printf("\nChoisir le deplacement du joueur :");

    do
    {
        Element_Map     nextElement = ELT_NULL;
        int             x = playerPosition.x;
        int             y = playerPosition.y;

        keyPressed = _getch();

        switch (keyPressed)
        {
        case 72: // up
            nextElement = LireElement_Map(map, --y, x);
            break;

        case 80: // down
            nextElement = LireElement_Map(map, ++y, x);
            break;

        case 75: // left
            nextElement = LireElement_Map(map, y, --x);
            break;

        case 77: // right
            nextElement = LireElement_Map(map, y, ++x);
            break;
        }

        if (nextElement != ELT_NULL)
        {
            if (InteragirAvecElement(player, nextElement) == 1)
            {
                EcrireElement_Map(map, playerPosition.y, playerPosition.x, ELT_ZONE_LIBRE);
                AfficherZone_MapGraphic(map, playerPosition.y, playerPosition.x);

                EcrireElement_Map(map, y, x, ELT_JOUEUR);
                AfficherZone_MapGraphic(map, y, x);

                playerPosition.x = x;
                playerPosition.y = y;
            }
        }
    }
    while (keyPressed != 'Q' && keyPressed != 'q');
}