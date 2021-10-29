#include <stdio.h>
#include "Map.h"
#include "MapGraphic.h"

static void ConstruireZone(Zone_Map zone, int largeur, int hauteur)
{
	Map * map = Creer_Map(zone, largeur, hauteur);

	Remplir_Map(map);

	Afficher_Map(map);
	Afficher_MapGraphic(map);

	Detruire_Map(map);
}

int main()
{
	int hauteur = 20;
	int largeur = 20;
	Creer_MapGraphic(largeur, hauteur);

	ConstruireZone(ZONE1, largeur, hauteur);

	printf("\n< Appuyer sur une touche >");
	getchar();

	Terminer_MapGraphic();
}


