#include <stdio.h>
#include <conio.h>
#include "Map.h"
#include "MapGraphic.h"
#include "Player.h"
#include "Action.h"

static Map * ConstruireZone(Zone_Map zone, int largeur, int hauteur)
{
	Map * map = Creer_Map(zone, largeur, hauteur);

    Creer_MapGraphic(largeur, hauteur);

	Remplir_Map(map);

	Afficher_Map(map);
	Afficher_MapGraphic(map);

    return map;
}

static void DetruireZone(Map * map)
{
    Detruire_Map(map);
    Terminer_MapGraphic();
}

int main()
{
	int hauteur = 20;
	int largeur = 20;

    Player * player = initPlayer();

    Map * map = ConstruireZone(ZONE1, largeur, hauteur);

    Jouer_Action(map, player);

    DetruireZone(map);
}


