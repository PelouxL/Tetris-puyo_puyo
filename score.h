#ifndef _SCORE_H_
#define _SCORE_H_

int calcule_score(int destruction, joueur *je, hms chrono);

int echange_joueur_score(joueur *j1, joueur *j2);

int recup_score( char *nom, tjoueur *je_score );

int tri_insertion( char *nom, int score, int *tabscore[10] );

#endif
