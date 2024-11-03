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


void actualisation_poyo(c_poyo *p, grille *gr){
  gr -> mat[p -> p1.x][p -> p1.y] = p -> p1.couleur;
  gr -> mat[p -> p2.x][p -> p2.y] = p -> p2.couleur;
} /* pas sur de l'utilité de cette, peux surement être supprimer pour en modif une autre */


int peux_bouger_droite(poyo p, grille gr){
  if( gr.mat[p.x][p.y-1] == 0 && p.y < gr.m-1 ){
    return 1;
  }
  return 0;
}

int peux_bouger_gauche(poyo p, grille gr){
  if( gr.mat[p.x][p.y+1] == 0 && p.y > 0 ){
    return 1;
  }
  return 0;
}

int peux_bouger_bas(poyo p, grille gr){
  if( gr.mat[p.x+1][p.y] == 0 && p.x < gr.n-1 ){
    return 1;
  }
  return 0;
}


int disposition(c_poyo p){
  if( p.p1.x >= p.p2.x ){
    if( p.p1.y < p.p2.y ){ /* p2 a gauche de p1 */
      return 1;
    }
    if( p.p1.y == p.p2.y ){ /* p2 au dessus de p1 */
      return 2;
    }
    else{
      return 3; /* p2 a droite de p1 */
    }
  }
  return 4; /* p2 en dessous de p1 */
}


/* ATTENTION cette fontion ou la fonction de deplacement permet de laisser un poyo seul
   juste en la cognant contre un mur !!! surement a cause du wait mlv mais a CORRIGER */

void avancement_piece(c_poyo * p, grille *gr){
  if( peux_bouger_bas(p -> p1, *gr) == 1 && p -> p1.pos == 0 ){
    gr -> mat[p -> p1.x][p -> p1.y] = 0;
    p -> p1.x += 1;
  }else{
    gr -> mat[p -> p1.x][p -> p1.y] = p -> p1.couleur;
    p -> p1.pos = 1;
  }
  
  if( peux_bouger_bas(p -> p2, *gr) == 1 && p -> p2.pos == 0 ){
    gr -> mat[p -> p2.x][p -> p2.y] = 0;
    p -> p2.x += 1;
  }else{
    p -> p2.pos = 1;
  }
}


/* ------------------------------- definition des fonction de deplacement ---------------------------- */


void pivot(c_poyo *p, grille *gr){
  int d;
  d = disposition(*p);
  if( p -> p1.pos == 0 && p -> p2.pos == 0 ){
    switch ( d )
      {
      case 1:
	if( peux_bouger_bas( p -> p1, *gr)){
	  gr -> mat[p -> p2.x][p -> p2.y] = 0;
	  p -> p2.x = p -> p1.x + 1;
	  p -> p2.y = p -> p1.y;
	}
	break;
      case 2:
	if( peux_bouger_droite( p -> p1, *gr)){
	  gr -> mat[p -> p2.x][p -> p2.y] = 0;
	  p -> p2.x = p -> p1.x;
	  p -> p2.y = p -> p1.y + 1;
	}
	break;
      case 3:
	gr -> mat[p -> p2.x][p -> p2.y] = 0;
	p -> p2.x = p -> p1.x - 1;
	p -> p2.y = p -> p1.y;
	break;
      case 4:
	if( peux_bouger_gauche( p -> p1, *gr)){
	  gr -> mat[p -> p2.x][p -> p2.y] = 0;
	  p -> p2.x = p -> p1.x;
	  p -> p2.y = p -> p1.y - 1;
	}
	break;
      }
  }
}





void deplacement_droit( c_poyo *p, grille *gr){
  int d;
  poyo *ptmp = &p -> p1;

  if( MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED ){
    if ( p -> p1.pos == 0 && p -> p2.pos == 0 ){
      d = disposition(*p);
      switch ( d%2 )
	{
	case 0 :
	  if( peux_bouger_droite( p->p2, *gr) == 1 &&  peux_bouger_droite( p->p1, *gr) == 1 ){
	    gr -> mat[p -> p1.x][p -> p1.y] = 0;
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.y += 1;
	    p -> p1.y += 1;
	  }
	  break;
	case 1 :
	  if( d == 3){
	    ptmp = &p -> p2;
	  }
	  if( peux_bouger_droite( *ptmp, *gr) == 1 ){
	    gr -> mat[p -> p1.x][p -> p1.y] = 0;
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p1.y += 1;
	    p -> p2.y += 1;
	  
	  }
	  break;
	}
    }else{
      if( p -> p1.pos == 1 && p -> p2.pos == 0 ){
	ptmp = &p -> p2;
      }
      if( peux_bouger_droite( *ptmp, *gr) == 1 ){
	gr -> mat[ptmp -> x][ptmp -> y] = 0;
	ptmp -> y += 1;
      }
    }
  }
  while ( MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED ){
     MLV_wait_milliseconds(5);
  }
}	



void deplacement_gauche( c_poyo *p, grille *gr){
  int d;
  poyo *ptmp = &p -> p1;

  if( MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED ){
    if ( p -> p1.pos == 0 && p -> p2.pos == 0 ){
      d = disposition(*p);
      switch ( d%2 )
	{
	case 0 :
	  if( peux_bouger_gauche( p->p2, *gr) == 1 &&  peux_bouger_gauche( p->p1, *gr) == 1 ){
	    gr -> mat[p -> p1.x][p -> p1.y] = 0;
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.y -= 1;
	    p -> p1.y -= 1;
	  }
	  break;
	case 1 :
	  if( d == 3){
	    ptmp = &p -> p2;
	  }
	  if( peux_bouger_gauche( *ptmp, *gr) == 1 ){
	    gr -> mat[p -> p1.x][p -> p1.y] = 0;
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p1.y -= 1;
	    p -> p2.y -= 1;
	  
	  }
	  break;
	}
    }else{
      if( p -> p1.pos == 1 && p -> p2.pos == 0 ){
	ptmp = &p -> p2;
      }
      if( peux_bouger_gauche( *ptmp, *gr) == 1 ){
	gr -> mat[ptmp -> x][ptmp -> y] = 0;
	ptmp -> y -= 1;
      }
    }
  }
  while ( MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED ){
     MLV_wait_milliseconds(5);
  }
}	


void deplacement_bas( c_poyo *p, grille *gr){
  int d;
  poyo *ptmp = &p -> p1;

  if( MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED ){
    if ( p -> p1.pos == 0 && p -> p2.pos == 0 ){
      d = disposition(*p);
      switch ( d%2 )
	{
	case 0 :
	  if( d == 4 ){
	    ptmp = &p -> p2;
	  }
	  if( peux_bouger_bas( *ptmp, *gr) == 1 ){
	    gr -> mat[p -> p1.x][p -> p1.y] = 0;
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.x += 1;
	    p -> p1.x += 1;
	  }
	  break;
	case 1 :
	  if( peux_bouger_bas( p -> p1, *gr) == 1 &&  peux_bouger_bas( p -> p2, *gr) == 1 ){
	    gr -> mat[p -> p1.x][p -> p1.y] = 0;
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p1.x += 1;
	    p -> p2.x += 1;
	  
	  }
	  break;
	}
    }else{
      if( p -> p1.pos == 1 && p -> p2.pos == 0 ){
	ptmp = &p -> p2;
      }
      if( peux_bouger_bas( *ptmp, *gr) == 1 ){
	gr -> mat[ptmp -> x][ptmp -> y] = 0;
	ptmp -> x += 1;
      }
    }
  }
  while ( MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED ){
     MLV_wait_milliseconds(5);
  }
}


/* -------------------------------- fin des definition de deplacement -------------------------------------*/

/* alors, FONCTIONNE entre grosse guillement, il faut changer sa manière d'empecher qu'avec une pression 4 decalage se fasse */

/* a grandement optimiser, il faut gerer chaque poyo independament pour savoir si il peux bouger ( se cogner contreu mur) ou si l'un se separe de l'autre */

void deplacement(c_poyo *p,grille * gr){
  
  if( p -> p1.pos == 0 && p -> p2.pos == 0 ){
    if( p -> p1.y < gr -> m - 1  && p -> p1.pos == 0 && gr -> mat[p -> p1.x][p -> p1.y+1] == 0 ){
      if( MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED ){
	gr -> mat[p -> p1.x][p -> p1.y] = 0;
	gr -> mat[p -> p2.x][p -> p2.y] = 0;
	p -> p1.y += 1;
	p -> p2.y += 1;
      }
    }
    if( p -> p1.y > 0 && p -> p1.pos == 0 ){
      if( MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED  && gr -> mat[p -> p1.x][p -> p1.y-1] == 0){
	gr -> mat[p -> p1.x][p -> p1.y] = 0;
	gr -> mat[p -> p2.x][p -> p2.y] = 0;
	p -> p1.y -= 1;
	p -> p2.y -= 1;
      }
    }
    if( p -> p1.x < gr -> n-1 && p -> p1.pos == 0 && gr -> mat[p -> p1.x+1][p -> p1.y] == 0 ){
      if( MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED  && gr -> mat[p -> p1.x][p -> p1.y-1] == 0 ){
	gr -> mat[p -> p1.x][p -> p1.y] = 0;
	gr -> mat[p -> p2.x][p -> p2.y] = 0;
	p -> p1.x += 1;
	p -> p2.x += 1;
      }
    }
  
    if( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED ){
      pivot(p, gr);
    }
    /*----------- si un poyo est déjà poser alors ---------------*/

    while ( MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED ||  MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED ){
      MLV_wait_milliseconds(5);
    }
  } 
}


