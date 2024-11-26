#ifndef _SCORE_H_
#define _SCORE_H_

int calcule_score(int destruction, joueur *je, hms chrono);

int recup_score( char *nom, int *score[10] );

int tri_insertion( int score, int *tabscore[10] );

#endif
