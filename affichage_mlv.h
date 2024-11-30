#ifndef AFFICHAGE_MLV_H
#define AFFICHAGE_MLV_H

void aff_etat(grille gr, joueur j, hms chrono);


void aff_poyos(c_poyo *tpoyo, c_poyo *sauvegarde);

void aff_1vs1_etat(grille gr1, grille gr2, joueur je1, joueur je2, hms chrono);

void aff_1vs1_poyos(c_poyo *tpoyo1, c_poyo *tpoyo2,  c_poyo *sauvegarde1, c_poyo *sauvegarde2);
  
#endif
