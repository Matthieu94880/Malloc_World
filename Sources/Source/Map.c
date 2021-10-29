#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

typedef struct
{
    Element_Map     element;
    int             min;
}
ElementObligatoire;

/*****************************************************************************
** Retourne un nombre aléatoire entre un intervalle
** - appel de la fonction systeme de nombre aleatoire
** - on ramene ensuite la valeur obtenue pour qu'elle soit dans l'intervalle
******************************************************************************/
static int random(int valeurMin, int valeurMax)
{
    int valeur;

    if (valeurMin >= valeurMax)
    {
        valeur = valeurMin;
    }
    else
    {
        valeur = rand();

        valeur = valeur % (valeurMax+1 - valeurMin);
        valeur = valeur + valeurMin;
    }

    return valeur;
}

/*****************************************************************************
** Ecrit un element dans la zone de la map
** Pour un monstre, la valeur varie entre 12 et 98
******************************************************************************/
static void EcrireElementMap(Map * map, Element_Map element, int hauteur, int largeur)
{
    if (map->hauteur > hauteur && map->largeur > largeur)
    {
        if (element == ELT_MONSTRE)
        {
            element = random(12, 98);
        }

        map->contenu[hauteur][largeur] = element;
    }
}

/*****************************************************************************
** Retourne l'element de la zone de la map
******************************************************************************/
Element_Map LireElement_Map(const Map * map, int hauteur, int largeur)
{
    if (map->hauteur > hauteur && map->largeur > largeur)
    {
        return map->contenu[hauteur][largeur];
    }

    return ELT_DEFAULT;
}

/*****************************************************************************
** Complete le remplissage de la map avec les éléments facultatifs
** La liste des élements acceptés depend de la zone
******************************************************************************/
static void PositionnerElementsFacultatifs(Map * map)
{
    int  nombreEltListe;

    Element_Map elementsFacultatifsZone1[] = {
                ELT_MONSTRE,
                ELT_INFRANCHISSABLE,
                ELT_ZONE_LIBRE,
                ELT_ROCHER_ZONE1,
                ELT_PLANTE_ZONE1,
                ELT_BOIS_ZONE1 };

    Element_Map elementsFacultatifsZone2[] = {
                ELT_MONSTRE,
                ELT_INFRANCHISSABLE,
                ELT_ZONE_LIBRE,
                ELT_ROCHER_ZONE2,
                ELT_PLANTE_ZONE2,
                ELT_BOIS_ZONE2 };

    Element_Map elementsFacultatifsZone3[] = {
                ELT_MONSTRE,
                ELT_INFRANCHISSABLE,
                ELT_ZONE_LIBRE,
                ELT_ROCHER_ZONE3,
                ELT_PLANTE_ZONE3,
                ELT_BOIS_ZONE3 };

    Element_Map * liste;

    switch (map->zone)
    {
        case ZONE1:
        {
            liste = elementsFacultatifsZone1;
            nombreEltListe = sizeof(elementsFacultatifsZone1) / sizeof(Element_Map);
            break;
        }

        case ZONE2:
        {
            liste = elementsFacultatifsZone2;
            nombreEltListe = sizeof(elementsFacultatifsZone2) / sizeof(Element_Map);
            break;
        }

        default:
        {
            liste = elementsFacultatifsZone3;
            nombreEltListe = sizeof(elementsFacultatifsZone3) / sizeof(Element_Map);
        }
    }

    for (int idxHauteur = 0; idxHauteur < map->hauteur; idxHauteur++)
    {
        for (int idxLargeur = 0; idxLargeur < map->largeur; idxLargeur++)
        {
            if (LireElement_Map(map, idxHauteur, idxLargeur) == ELT_DEFAULT)
            {
                int indexElt = random(0, nombreEltListe - 1);

                EcrireElementMap(map, liste[indexElt], idxHauteur, idxLargeur);
            }
        }
    }
}

/*****************************************************************************
** Rempli la map avec les éléments obligatoires
** Chaque éléments contient :
** - un élement et un nombre minimum a placer dans la map pour cet élement
******************************************************************************/
static void PositionnerElementsObligatoires(Map * map)
{
    int  nombreTypeListe;

    ElementObligatoire listeObligatoireZone1[] =
    {
        /* TYPE               MIN */
           ELT_MONSTRE      , 10,
           ELT_ROCHER_ZONE1 ,  3,
           ELT_PLANTE_ZONE1 ,  3,
           ELT_BOIS_ZONE1   ,  3,
           ELT_JOUEUR       ,  1,
           ELT_PNJ          ,  1,
           ELT_PORTAIL_ZONE2,  1
    };

    ElementObligatoire listeObligatoireZone2[] =
    {
        /* TYPE               MIN */
           ELT_MONSTRE      , 10,
           ELT_ROCHER_ZONE2 ,  3,
           ELT_PLANTE_ZONE2 ,  3,
           ELT_BOIS_ZONE2   ,  3,
           ELT_JOUEUR       ,  1,
           ELT_PNJ          ,  1,
           ELT_PORTAIL_ZONE2,  1,
           ELT_PORTAIL_ZONE3,  1
    };

    ElementObligatoire listeObligatoireZone3[] =
    {
        /* TYPE               MIN */
           ELT_MONSTRE      , 10,
           ELT_ROCHER_ZONE3 ,  3,
           ELT_PLANTE_ZONE3 ,  3,
           ELT_BOIS_ZONE3   ,  3,
           ELT_JOUEUR       ,  1,
           ELT_PNJ          ,  1,
           ELT_PORTAIL_ZONE3,  1,
           ELT_BOSS         ,  1
    };

    ElementObligatoire * liste;
        
    switch (map->zone)
    {
        case ZONE1:
        {
            liste = listeObligatoireZone1;
            nombreTypeListe = sizeof(listeObligatoireZone1) / sizeof(ElementObligatoire);
            break;
        }

        case ZONE2:
        {
            liste = listeObligatoireZone2;
            nombreTypeListe = sizeof(listeObligatoireZone2) / sizeof(ElementObligatoire);
            break;
        }

        default:
        {
            liste = listeObligatoireZone3;
            nombreTypeListe = sizeof(listeObligatoireZone3) / sizeof(ElementObligatoire);
        }
    }

    int nombreCaseRestant = map->hauteur * map->largeur;

    for (int idxListe = 0; idxListe < nombreTypeListe; idxListe++)
    {
        for (int idxElt = 0; idxElt < liste[idxListe].min; idxElt++)
        {
            /* positionnement aléatoire de l'element dans une des cases restantes de la map */

            char    estTrouveCase = 0;
            int     indexCaseLibre = 0;
            int     indexCaseMapLibreChoisi = random(0, nombreCaseRestant - 1);

            for (int idxHauteur = 0; !estTrouveCase && idxHauteur < map->hauteur; idxHauteur++)
            {
                for (int idxLargeur = 0; !estTrouveCase && idxLargeur < map->largeur; idxLargeur++)
                {
                    if (LireElement_Map(map, idxHauteur, idxLargeur) == ELT_DEFAULT)
                    {
                        if (indexCaseLibre == indexCaseMapLibreChoisi)
                        {
                            EcrireElementMap(map, liste[idxListe].element, idxHauteur, idxLargeur);
                            estTrouveCase = 1;
                        }
                        else
                        {
                            indexCaseLibre++;
                        }
                    }
                }
            }
        }
    }
}

/*****************************************************************************
** Rempli la map aleatoirement
******************************************************************************/
void Remplir_Map(Map * map)
{
    PositionnerElementsObligatoires(map);
    PositionnerElementsFacultatifs(map);
}

/*****************************************************************************
** Alloue la map et l'initialise
******************************************************************************/
Map * Creer_Map(Zone_Map zone, int hauteur, int largeur)
{
    Map * map = (Map*)malloc(sizeof(Map));

    map->zone    = zone;
    map->largeur = hauteur;
    map->hauteur = largeur;

    map->contenu = malloc(sizeof(Element_Map*) * map->hauteur);

    for (int idxHauteur = 0; idxHauteur < map->hauteur; idxHauteur++)
    {
        map->contenu[idxHauteur] = malloc(sizeof(Element_Map) * map->largeur);
    }

    for (int idxHauteur = 0; idxHauteur < map->hauteur; idxHauteur++)
    {
        for (int idxLargeur = 0; idxLargeur < map->largeur; idxLargeur++)
        {
            EcrireElementMap(map, ELT_DEFAULT, idxHauteur, idxLargeur);
        }
    }

    // Initialisation de la graine par rapport a la date en cours pour les fonctions rand()
    srand((unsigned int)time(NULL));

    return map;
}

/*****************************************************************************
** Desalloue la map
******************************************************************************/
void Detruire_Map(Map * map)
{
    for (int idxHauteur = 0; idxHauteur < map->hauteur; idxHauteur++)
    {
        free(map->contenu[idxHauteur]);
    }

    free(map->contenu);
    free(map);

    map = NULL;
}

/*****************************************************************************
** Affiche la map vers la console
******************************************************************************/
void Afficher_Map(const Map * map)
{
    printf("\n*******************\n");
    printf("Zone : %d (%dx%d)\n", map->zone, map->hauteur, map->largeur);
    printf("*******************\n");

    printf("PORTAIL_ZONE3   = -3\n");
    printf("PORTAIL_ZONE2   = -2\n");
    printf("INFRANCHISSABLE = -1\n");
    printf("ZONE_LIBRE      =  0\n");
    printf("JOUEUR          =  1\n");
    printf("PNJ             =  2\n");
    printf("PLANTE_ZONE1    =  3\n");
    printf("ROCHER_ZONE1    =  4\n");
    printf("BOIS_ZONE1      =  5\n");
    printf("PLANTE_ZONE2    =  6\n");
    printf("ROCHER_ZONE2    =  7\n");
    printf("BOIS_ZONE2      =  8\n");
    printf("PLANTE_ZONE3    =  9\n");
    printf("ROCHER_ZONE3    = 10\n");
    printf("BOIS_ZONE3      = 11\n");
    printf("MONSTRE         = 12\n");
    printf("BOSS            = 99\n\n");

    for (int idxHauteur = 0; idxHauteur < map->hauteur; idxHauteur++)
    {
        for (int idxLargeur = 0; idxLargeur < map->largeur; idxLargeur++)
        {
            Element_Map elt = LireElement_Map(map, idxHauteur, idxLargeur);

            if (elt == ELT_DEFAULT)
                printf("-- ");
            else if (elt < 0)
            {
                printf("%d ", LireElement_Map(map, idxHauteur, idxLargeur));
            }
            else
            {
                printf("%2d ", LireElement_Map(map, idxHauteur, idxLargeur));
            }
        }

        printf("\n");
    }
}