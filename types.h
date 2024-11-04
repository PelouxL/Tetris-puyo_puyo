#ifndef TYPE_H
#define TYPE_H

#define LX 900
#define LY 800
#define N 100
#define M 100

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
}poyo;

typedef struct{
  poyo p1;
  poyo p2;
  int apparait;
}c_poyo;


typedef struct{
  char *pseudo;
  int score;
}joueur;

typedef struct{
  int x;
  int y;
}coordonne;

#endif
    
	      
