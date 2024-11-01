#ifndef PIECES_H
#define PIECES_H

void initialisation_cpoyo(c_poyo * cp);

void apparition_piece(c_poyo * p, grille *gr);


/* regarde si un poyo poser est présent dessous */
int est_dessous(poyo p, grille gr); 

void avancement_piece(c_poyo * p, grille *gr);

#endif
