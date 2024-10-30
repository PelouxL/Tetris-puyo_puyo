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
  int gauche;
  int droit;
  int larg;
  int haut;
  int x;
  int y;
}piece;

typedef struct{
  char *pseudo;
  int score;
}joueur;

#endif
    
	      
