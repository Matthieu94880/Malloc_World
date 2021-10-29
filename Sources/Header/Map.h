
#ifndef Map_h_
#define Map_h_

typedef enum
{
    ELT_DEFAULT         = -9,

    ELT_PORTAIL_ZONE3   = -3,
    ELT_PORTAIL_ZONE2   = -2,
    ELT_INFRANCHISSABLE = -1,
    ELT_ZONE_LIBRE      = 0,
    ELT_JOUEUR          = 1,
    ELT_PNJ             = 2,
    ELT_PLANTE_ZONE1    = 3,
    ELT_ROCHER_ZONE1    = 4,
    ELT_BOIS_ZONE1      = 5,
    ELT_PLANTE_ZONE2    = 6,
    ELT_ROCHER_ZONE2    = 7,
    ELT_BOIS_ZONE2      = 8,
    ELT_PLANTE_ZONE3    = 9,
    ELT_ROCHER_ZONE3    = 10,
    ELT_BOIS_ZONE3      = 11,
    ELT_MONSTRE         = 12,
    ELT_BOSS            = 99
}
Element_Map;

typedef enum
{
    ZONE1 = 1,
    ZONE2 = 2,
    ZONE3 = 3
}
Zone_Map;

typedef struct
{
    Zone_Map        zone;
    int             largeur;
    int             hauteur;
    Element_Map **  contenu;
}
Map;

/*****************************************************************************
** Alloue la map et l'initialise
******************************************************************************/
Map *   Creer_Map(Zone_Map zone, int hauteur, int largeur);

/*****************************************************************************
** Rempli la map aleatoirement
******************************************************************************/
void    Remplir_Map(Map * map);

/*****************************************************************************
** Retourne l'element de la zone de la map
******************************************************************************/
Element_Map LireElement_Map(const Map * map, int hauteur, int largeur);

/*****************************************************************************
** Desalloue la map
******************************************************************************/
void    Detruire_Map(Map * map);

/*****************************************************************************
** Affiche la map vers la console
******************************************************************************/
void    Afficher_Map(const Map * map);

#endif