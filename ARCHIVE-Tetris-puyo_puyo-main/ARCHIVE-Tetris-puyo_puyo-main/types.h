#ifndef TYPE_H
#define TYPE_H

#define LX 1200
#define LY 1000
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
  char pseudo[100];
  int score;
}joueur;

typedef struct{
  int x;
  int y;
}coordonne;

/* Menu */
#define L 50
#define X 90

typedef struct{
  int x;
  int y;
  int hauteur;
  int largeur;
  int valeur;
  char txt[L];
} bouton;

typedef struct{
  int niveau;
  joueur j;
  grille gr;
} save;
typedef save tsave[N];

#endif
    
	      
