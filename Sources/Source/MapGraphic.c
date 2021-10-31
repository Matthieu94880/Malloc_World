/*
** Filename : MapGraphic.c
**
** Made by : Matthieu BARRIERE
**
** Description : Display the Malloc_World map with SDL graphic library
*/

#include <stdio.h>
#include "SDL.h"
#include "Map.h"
#include "MapGraphic.h"

#define PICTURE_WIDTH    34
#define PICTURE_HEIGHT   34

static SDL_Window * pWindow = NULL;

typedef struct {
    Element_Map   element;
    char *        fileName;
    SDL_Surface * pSurface;
}
ElementPicture;

static ElementPicture elementPicture[] = {

    ELT_PORTAIL_ZONE2_3, ".\\Images\\PORTAIL_Z2_3.BMP", NULL,
    ELT_PORTAIL_ZONE1_2, ".\\Images\\PORTAIL_Z1_2.BMP", NULL,
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

static int picturesCount = sizeof(elementPicture) / sizeof(ElementPicture);

/*****************************************************************************
** Loads an element picture
******************************************************************************/
static void loadPictures() {

    for (int i = 0; i < picturesCount; i++) {
        if (elementPicture[i].pSurface == NULL) {
            elementPicture[i].pSurface = SDL_LoadBMP(elementPicture[i].fileName);
        }
    }
}

/*****************************************************************************
** Returns the loaded picture for an element or NULL if not found
******************************************************************************/
static SDL_Surface * getSurface(Element_Map element) {

    for (int i = 0; i < picturesCount; i++) {
        if (elementPicture[i].element == element) {
            return elementPicture[i].pSurface;
        }
    }

    return NULL;
}

/*****************************************************************************
** Displays a specific map zone
******************************************************************************/
static void displayZone(const Map * map, int x, int y) {

    if (y < map->height && x < map->width) {
        Element_Map element = getElement_Map(map, x, y);

        // patch a virer : remet tous les monstres de 12 a 98 a 12 pour avoir le meme fichier
        if (element >= 12 && element <= 98) {
            element = ELT_MONSTRE;
        }

        SDL_Surface * pSurface = getSurface(element);

        if (pSurface != NULL) {
            SDL_Rect dest;

            dest.x = x * PICTURE_WIDTH;
            dest.y = y * PICTURE_HEIGHT;
            dest.w = 0;
            dest.h = 0;

            SDL_BlitSurface(pSurface, NULL, SDL_GetWindowSurface(pWindow), &dest);
        }
    }
}

/*****************************************************************************
** Displays a specific map zone and refresh the window
******************************************************************************/
void displayZone_MapGraphic(const Map * map, int x, int y) {

    if (x < map->width && y < map->height) {

        displayZone(map, x, y);

        int returnCode = SDL_UpdateWindowSurface(pWindow);

        if (returnCode < 0) {
            printf("\nERROR - SDL_UpdateWindowSurface : %d", returnCode);
        }
        else {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {  // poll until all events are handled!
            }
        }
    }
}

/*****************************************************************************
** Displays all the map
******************************************************************************/
void display_MapGraphic(const Map * map) {

    if (pWindow != NULL) {

        for (int x = 0; x < map->width; x++) {

            for (int y = 0; y < map->height; y++) {

                displayZone(map, x, y);
            }
        }

        SDL_SetWindowTitle(pWindow, map->zone == ZONE1 ? "MALLOC_WORLD : ZONE1" :
                                    map->zone == ZONE2 ? "MALLOC_WORLD : ZONE2" :
                                                         "MALLOC_WORLD : ZONE3");

        int returnCode = SDL_UpdateWindowSurface(pWindow);

        if (returnCode < 0) {
            printf("\nERROR - SDL_UpdateWindowSurface : %d", returnCode);
        }
        else {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {  // poll until all events are handled!
            }
        }
    }
}

/*****************************************************************************
** SDL memory allocation. Loading pictures and create main graphic window
******************************************************************************/
void create_MapGraphic(const Map * map) {

    if (pWindow == NULL) {

        SDL_Init(0);

        pWindow = SDL_CreateWindow("",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   PICTURE_WIDTH * map->width,
                                   PICTURE_HEIGHT * map->height, SDL_WINDOW_OPENGL);

        loadPictures();

        SDL_Surface * mainPicture = SDL_LoadBMP(".\\Images\\Fond.bmp");

        if (mainPicture != NULL) {

            SDL_Rect pos;

            pos.x = 0;
            pos.y = 0;

            SDL_BlitSurface(mainPicture, NULL, SDL_GetWindowSurface(pWindow), &pos);
        }
    }
}

/*****************************************************************************
** SDL memory release
******************************************************************************/
void free_MapGraphic() {

    if (pWindow != NULL) {
        SDL_Quit();

        pWindow = NULL;
    }
}