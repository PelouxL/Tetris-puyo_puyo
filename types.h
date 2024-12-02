#ifndef TYPE_H
#define TYPE_H

#define LX 900
#define LY 800
#define N 100
#define M 100
#define TAILLE_PSEUDO 10

typedef struct{
  int mat[N][M];
  int n;
  int m;
  int niveau;
}grille;

typedef struct{
  int couleur;
  int x;
  int y;
  int pos;
  int fantome;
}poyo;

typedef struct{
  poyo p1;
  poyo p2;
  int apparait;
}c_poyo;


typedef struct{
  char pseudo[TAILLE_PSEUDO];
  int score;
}joueur;

typedef joueur tjoueur[10];

typedef struct{
  int x;
  int y;
}coordonne;

typedef struct{
  int heures;
  int minutes;
  int secondes;
  int milis;
}hms;

#endif
    
	      
