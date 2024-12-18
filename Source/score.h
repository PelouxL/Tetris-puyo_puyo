#ifndef _SCORE_H_
#define _SCORE_H_

/* permet de calculer le score max par rapport au temps */
int calcule_score(int destruction, joueur *je, hms chrono);

/* permet de recupperer le score dans un tableau tjoueur */
int echange_joueur_score(joueur *j1, joueur *j2);

/* fonction de permutation de deux variable joueur */
int recup_score( char *nom, tjoueur je_score );

/* tri la liste des score et renvoie 1 ou -1 en cas d'erreurs */
int tri_insertion( char *nom, joueur score, tjoueur tabscore );

/* initialise une piece malus */
void creation_malus(c_poyo poyo_piege, grille *gr_adverse);

/* on fait decaler tout les poyos de la ligne du malus vers le haut*/
void decalage(int absisse, grille *gr, c_poyo *poyo);

/* applique au joueur adverse */
void appliquer_malus(int score, grille *gr, c_poyo *poyo);

#endif
