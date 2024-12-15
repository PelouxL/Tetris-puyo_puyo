#ifndef _SCORE_H_
#define _SCORE_H_

int calcule_score(int destruction, joueur *je, hms chrono);

int echange_joueur_score(joueur *j1, joueur *j2);

int recup_score( char *nom, tjoueur je_score );

int tri_insertion( char *nom, joueur score, tjoueur tabscore );

void creation_malus(c_poyo poyo_piege, grille *gr_adverse);

void decalage(int absisse, grille *gr, c_poyo *poyo);

void appliquer_malus(int score, grille *gr, c_poyo *poyo);

#endif
