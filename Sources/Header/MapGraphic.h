
#ifndef MapGraphic_h_
#define MapGraphic_h_

#include "Map.h"

void Creer_MapGraphic(int largeur, int hauteur);

void Terminer_MapGraphic();

void Afficher_MapGraphic(Map * map);

void AfficherZone_MapGraphic(Map * map, int idxHauteur, int idxLargeur);

#endif