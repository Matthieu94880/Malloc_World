#include "SDL.h"
#include "Map.h"
#include "MapGraphic.h"

#define LARGEUR_IMAGE    34
#define HAUTEUR_IMAGE    34

static SDL_Window * pWindow = NULL;

typedef struct
{
    Element_Map   element;
    char *        nomFichierImage;
    SDL_Surface * pImage;
}
ImageParElement;

static ImageParElement imageParElement[] =
{
    ELT_PORTAIL_ZONE3,   ".\\Images\\PORTAIL_Z3.BMP", NULL,
    ELT_PORTAIL_ZONE2,   ".\\Images\\PORTAIL_Z2.BMP", NULL,
    ELT_INFRANCHISSABLE, ".\\Images\\INFRANCHISSABLE.BMP", NULL,
    ELT_ZONE_LIBRE,      ".\\Images\\ZONE_LIBRE.BMP", NULL,
    ELT_JOUEUR,          ".\\Images\\JOUEUR.BMP", NULL,
    ELT_PNJ,             ".\\Images\\PNJ.BMP", NULL,
    ELT_PLANTE_ZONE1,    ".\\Images\\PLANTE_Z1.BMP", NULL,
    ELT_ROCHER_ZONE1,    ".\\Images\\ROCHER_Z1.BMP", NULL,
    ELT_BOIS_ZONE1,      ".\\Images\\BOIS_Z1.BMP", NULL,
    ELT_PLANTE_ZONE2,    ".\\Images\\PLANTE_Z2.BMP", NULL,
    ELT_ROCHER_ZONE2,    ".\\Images\\ROCHER_Z2.BMP", NULL,
    ELT_BOIS_ZONE2,      ".\\Images\\BOIS_Z2.BMP", NULL,
    ELT_PLANTE_ZONE3,    ".\\Images\\PLANTE_Z3.BMP", NULL,
    ELT_ROCHER_ZONE3,    ".\\Images\\ROCHER_Z3.BMP", NULL,
    ELT_BOIS_ZONE3,      ".\\Images\\BOIS_Z3.BMP", NULL,
    ELT_MONSTRE,         ".\\Images\\MONSTRE.BMP", NULL,
    ELT_BOSS,            ".\\Images\\BOSS.BMP", NULL
};

static int nombreImage = sizeof(imageParElement) / sizeof(ImageParElement);

/*****************************************************************************
** Charge les images avec la librairie SDL pour chaque element si pas deja fait
******************************************************************************/
static void chargerImages()
{
    for (int i = 0; i < nombreImage; i++)
    {
        if (imageParElement[i].pImage == NULL)
        {
            imageParElement[i].pImage = SDL_LoadBMP(imageParElement[i].nomFichierImage);
        }
    }
}

/*****************************************************************************
** Recupere l'image chargee pour un element (ou NULL si non trouvee)
******************************************************************************/
static SDL_Surface * lireImage(Element_Map element)
{
    for (int i = 0; i < nombreImage; i++)
    {
        if (imageParElement[i].element == element)
        {
            return imageParElement[i].pImage;
        }
    }

    return NULL;
}

/*****************************************************************************
** Affiche l'image chargee d'un element vers une partie de la map
******************************************************************************/
static void AfficherUneZone(Map * map, int idxHauteur, int idxLargeur)
{
    if (idxHauteur < map->hauteur && idxLargeur < map->largeur)
    {
        Element_Map element = LireElement_Map(map, idxHauteur, idxLargeur);

        // patch a virer : remet tous les monstres de 12 a 98 a 12 pour avoir le meme fichier
        if (element >= 12 && element <= 98)
        {
            element = ELT_MONSTRE;
        }

        SDL_Surface * pImage = lireImage(element);

        if (pImage != NULL)
        {
            SDL_Rect dest;

            dest.x = idxLargeur * LARGEUR_IMAGE;
            dest.y = idxHauteur * HAUTEUR_IMAGE;
            dest.w = 0;
            dest.h = 0;

            SDL_BlitSurface(pImage, NULL, SDL_GetWindowSurface(pWindow), &dest);
        }
    }
}

/*****************************************************************************
** Affiche tous les elements de la map
******************************************************************************/
void Afficher_MapGraphic(Map * map)
{
    if (pWindow != NULL)
    {
        for (int idxHauteur = 0; idxHauteur < map->hauteur; idxHauteur++)
        {
            for (int idxLargeur = 0; idxLargeur < map->largeur; idxLargeur++)
            {
                AfficherUneZone(map, idxHauteur, idxLargeur);
            }
        }
    }

    SDL_UpdateWindowSurface(pWindow);
}

/*****************************************************************************
** Initialise la SDL, charge toutes les images et cree la fenetre principale
******************************************************************************/
void Creer_MapGraphic(int largeur, int hauteur)
{
    if (pWindow == NULL)
    {
        SDL_Init(0);

        pWindow = SDL_CreateWindow("MALLOC_WORLD",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    LARGEUR_IMAGE * largeur,
                                    HAUTEUR_IMAGE * hauteur, SDL_WINDOW_SHOWN| SDL_WINDOW_ALWAYS_ON_TOP);

        chargerImages();

        SDL_Surface * imageDeFond = SDL_LoadBMP(".\\Images\\Fond.bmp");

        if (imageDeFond != NULL)
        {
            SDL_Rect positionFond;

            positionFond.x = 0;
            positionFond.y = 0;

            SDL_BlitSurface(imageDeFond, NULL, SDL_GetWindowSurface(pWindow), &positionFond);
        }
    }
}

/*****************************************************************************
** Detruit la SDL
******************************************************************************/
void Terminer_MapGraphic()
{
    if (pWindow != NULL)
    {
        SDL_Quit();

        pWindow = NULL;
    }
}