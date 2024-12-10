#ifndef _DESTRUCTION_H_
#define _DESTRUCTION_H_

void est_deja_visiter(coordonne *est_visiter, int taille_visiter, coordonne coord);

void fusion_coord(coordonne *tcord1, coordonne *tcord2, int *taille1, int taille2);

int est_a_coter(poyo *p, grille *gr, coordonne *tcoord, coordonne *est_visiter, int taille_visite);

int recup_coord(poyo *p, grille *gr, coordonne *tcord);

int destruction(coordonne *tcord, grille *gr, int taille_t);

void chutte_destruction(grille *gr);

int post_destruction( grille *gr );

int chute_et_destruction(c_poyo *tpoyo, grille *gr );

#endif
