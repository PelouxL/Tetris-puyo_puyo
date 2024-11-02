#ifndef PIECES_H
#define PIECES_H

void affiche_c_poyo(c_poyo * cp);

void ini_poyo_chaine(c_poyo *tpoyo, int n);

void initialisation_cpoyo(c_poyo * cp);

void apparition_piece(c_poyo * p, grille *gr);


/* regarde si un poyo poser est présent dessous */
int est_dessous(poyo p, grille gr); 

/* met a chaque coordonne de chaque poyo dans la grille */
void actualisation_poyo(c_poyo *p, grille *gr);

/* permet de faire chutter les pieces et vide les coordonne precedentes*/
void avancement_piece(c_poyo * p, grille *gr);

/* permet de mouvoir une piece */
void deplacement(c_poyo * p, grille *gr);

#endif
