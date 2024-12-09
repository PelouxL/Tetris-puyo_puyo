#ifndef AFFICHAGE_MLV_H
#define AFFICHAGE_MLV_H

int charger_img(MLV_Image *images[NUM_IMAGES]);

void liberer_images(MLV_Image* images[NUM_IMAGES]);

int charger_img_1vs1(MLV_Image *images[NUM_IMAGES]);

void liberer_images_1vs1(MLV_Image* images[NUM_IMAGES_1VS1]);

void aff_etat(grille gr, joueur j, hms chrono, c_poyo poyo, MLV_Image *images[NUM_IMAGES]);


void aff_poyos(c_poyo *tpoyo, c_poyo *sauvegarde, MLV_Image *images[NUM_IMAGES]);

void aff_1vs1_etat(grille gr1, grille gr2, joueur je1, joueur je2, hms chrono, c_poyo poyo1, c_poyo poyo2, MLV_Image *images[NUM_IMAGES]);

void aff_1vs1_poyos(c_poyo *tpoyo1, c_poyo *tpoyo2,  c_poyo *sauvegarde1, c_poyo *sauvegarde2, MLV_Image *images[NUM_IMAGES_1VS1]);
  
#endif
