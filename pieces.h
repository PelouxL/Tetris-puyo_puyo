#ifndef PIECES_H
#define PIECES_H


void apparition_piece(c_poyo * p, grille *gr);

/* met a chaque coordonne de chaque poyo dans la grille */
void actualisation_poyo(c_poyo *p, grille *gr);

/* permet de savoir la disposition des poyo dans un meme piece */
int disposition(c_poyo p);

/* permet de faire chutter les pieces et vide les coordonne precedentes*/
void avancement_piece(c_poyo * p, grille *gr);

/* ces 3 fonctions permettent de verifier si la pieces peux bien se deplacer*/

int peux_bouger_gauche(poyo p, grille gr);

int peux_bouger_droite(poyo p, grille gr);

int peux_bouger_bas(poyo p, grille gr);


/* ---- fonction de deplacement ------- */

void pivot_gauche(c_poyo *p, grille *gr);

void pivot_droit(c_poyo *p, grille *gr);

void deplacement_droit( c_poyo *p, grille *gr);

void deplacement_gauche( c_poyo *p, grille *gr);

void deplacement_bas( c_poyo *p, grille *gr);

void deplacement(c_poyo *p, grille *gr);

/* --------------------------------- */

/* permet de mouvoir une piece */
void deplacement(c_poyo * p, grille *gr);

/* sauvegarde une piece en appyant sur espace */
c_poyo sauvegarde_poyos(c_poyo *tpoyo, c_poyo poyo_sauvegarde, grille *gr, int *est_save);


#endif
