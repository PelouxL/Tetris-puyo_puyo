#ifndef TYPE_H
#define TYPE_H

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
}piece;

#endif
    
	      
