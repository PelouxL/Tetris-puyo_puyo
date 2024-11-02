#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include <MLV/MLV_all.h>


void affiche_c_poyo(c_poyo * p){
  printf("voici la couleur %d le x %d et le y %d\n p2 %d %d et %d\n", p -> p1.couleur, p -> p1.x, p -> p1.y , p -> p2.couleur, p -> p2.x, p -> p2.y);
}

void initialisation_cpoyo(c_poyo * cp){
  /* 0 = vide , 1 = red, 2 = green, 3 = blue */
  cp -> p1.couleur = (rand()%3)+1;
  cp -> p2.couleur = (rand()%3)+1;
  cp -> p1.x = 0; 
  cp -> p1.y = 0;
  cp -> p1.pos = 0;
  cp -> p2.x = -1;
  cp -> p2.y = -1;
  cp -> p2.pos = 0;
  cp -> apparait = 0;

}

void ini_poyo_chaine(c_poyo *tpoyo, int n){
  int i;
  for(i = 0 ; i < n ; i++){
    initialisation_cpoyo(&tpoyo[i]);
  }
}


/* est appeler une fois lors de la premire apparition d'un poyo */
void apparition_piece(c_poyo * p, grille *gr){
  p -> p1.y = gr -> m/2;
  p -> p2.y = gr -> m/2;
  gr -> mat[p -> p1.x][p -> p1.y]= p -> p1.couleur;
}

/* verifie juste si il n'y a pas un poyo sous la case pour descendre */
int est_dessous(poyo p, grille gr){
  if(gr.mat[p.x+1][p.y] != 0 ){
    return 1;
  }
  return 0;
}

void actualisation_poyo(c_poyo *p, grille *gr){
  gr -> mat[p -> p1.x][p -> p1.y] = p -> p1.couleur;
  gr -> mat[p -> p2.x][p -> p2.y] = p -> p2.couleur;
} /* pas sur de l'utilité de cette, peux surement être supprimer pour en modif une autre */
  
void avancement_piece(c_poyo * p, grille *gr){
  if( est_dessous(p -> p1, *gr) == 0 && p -> p1.x <= gr -> m && p -> p1.pos == 0){
    gr -> mat[p -> p1.x][p -> p1.y] = 0;
    p -> p1.x += 1;
  }else{
    gr -> mat[p -> p1.x][p -> p1.y] = p -> p1.couleur;
    p -> p1.pos = 1;
  }
  
  if( est_dessous(p -> p2, *gr) == 0 && p -> p2.y < gr -> m && p -> p2.pos == 0 ){
    gr -> mat[p -> p2.x][p -> p2.y] = 0;
    p -> p2.x += 1;
  }else{
    p -> p2.pos = 1;
  }
}

/* alors, FONCTIONNE entre grosse guillement, il faut changer sa manière d'empecher qu'avec une pression 4 decalage se fasse */


/* a grandement optimiser, il faut gerer chaque poyo independament pour savoir si il peux bouger ( se cogner contreu mur) ou si l'un se separe de l'autre */

void deplacement(c_poyo *p,grille * gr){
  if(p -> p1.y < gr -> m - 1  && p -> p1.pos == 0 && gr -> mat[p -> p1.x][p -> p1.y+1] == 0){
    if(MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED ){
      gr -> mat[p -> p1.x][p -> p1.y] = 0;
      gr -> mat[p -> p2.x][p -> p2.y] = 0;
      p -> p1.y += 1;
      p -> p2.y += 1;
    }
  }
  if(p -> p1.y > 0 && p -> p1.pos == 0){
    if( MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED  && gr -> mat[p -> p1.x][p -> p1.y-1] == 0){
      gr -> mat[p -> p1.x][p -> p1.y] = 0;
      gr -> mat[p -> p2.x][p -> p2.y] = 0;
      p -> p1.y -= 1;
      p -> p2.y -= 1;
    }
  }
  while (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED ) {
    MLV_wait_milliseconds(10);
  }
}


