#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "ini_poyo.h"
#include <MLV/MLV_all.h>


/* est appeler une fois lors de la premire apparition d'un poyo */
void apparition_piece(c_poyo * p, grille *gr){
  p -> p1.y = gr -> m/2;
  p -> p2.y = gr -> m/2;
  p -> apparait = 1;
}


void actualisation_poyo(c_poyo *p, grille *gr){
  if( p -> apparait == 1){
    gr -> mat[p -> p1.x][p -> p1.y] = p -> p1.couleur;
    if( p -> p2.y != -1 ){
      gr -> mat[p -> p2.x][p -> p2.y] = p -> p2.couleur;
    }
  }
  
} /* pas sur de l'utilité de cette, peux surement être supprimer pour en modif une autre */

int peux_bouger_droite(poyo p, grille gr){
  if( gr.mat[p.x][p.y+1] == 0 && p.y < gr.m-1 ){
    return 1;
  }
  return 0;
}

int peux_bouger_gauche(poyo p, grille gr){
  if( gr.mat[p.x][p.y-1] == 0 && p.y > 0 ){
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


void avancement_piece(c_poyo * p, grille *gr){
  int d = -1;
  
  if( p -> p1.pos == 0 && p -> p2.pos == 0){ /* si poyo est seul alors pas connaitre disposition */
    d = disposition(*p);
  }
  if( ( peux_bouger_bas(p -> p1, *gr) == 1  || ( peux_bouger_bas(p -> p1, *gr) == 0  && peux_bouger_bas(p -> p2, *gr) == 1 && d == 4 ) ) &&  p -> p1.pos == 0 ){
    gr -> mat[p -> p1.x][p -> p1.y] = 0;
    p -> p1.x += 1;
  }else{
    if( d%2 == 0){
      p -> p2.pos = 1;
    }
    p -> p1.pos = 1;
  }

  if( peux_bouger_bas(p -> p2, *gr) == 1 && p -> p2.pos == 0 ){
    gr -> mat[p -> p2.x][p -> p2.y] = 0;
    p -> p2.x += 1;
  }else{
    if( d%2 == 0 ){
      p -> p1.pos = 1;
    }
    p -> p2.pos = 1;
  }
}


/* --------------------------- definition des fonction de deplacement ------------------------- */

void pivot_droit(c_poyo *p, grille *gr){
  int d;
  d = disposition(*p);
  if( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED ){
    if( p -> p1.pos == 0 && p -> p2.pos == 0 ){
      switch ( d )
	{
	case 1:
	  if( peux_bouger_bas( p -> p1, *gr) == 1 ){
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.x = p -> p1.x + 1;
	    p -> p2.y = p -> p1.y;
	  }
	  break;
	case 2:
	  if( peux_bouger_droite( p -> p1, *gr) == 1 ){
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
	  if( peux_bouger_gauche( p -> p1, *gr ) == 1 ){
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.x = p -> p1.x;
	    p -> p2.y = p -> p1.y - 1;
	  }
	  break;
	}
    }
  }
}

void pivot_gauche(c_poyo *p, grille *gr){
  int d;
  d = disposition(*p);
  if( MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED ){
    if( p -> p1.pos == 0 && p -> p2.pos == 0 ){
      switch ( d )
	{
	case 1:
	  gr -> mat[p -> p2.x][p -> p2.y] = 0;
	  p -> p2.x = p -> p1.x - 1;
	  p -> p2.y = p -> p1.y;
	  break;
	case 2:
	  if( peux_bouger_gauche( p -> p1, *gr) == 1){
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.x = p -> p1.x;
	    p -> p2.y = p -> p1.y - 1;
	  }
	  break;
	case 3:
	  if( peux_bouger_bas( p -> p1, *gr) == 1){
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.x = p -> p1.x + 1;
	    p -> p2.y = p -> p1.y;
	  }
	  break;
	case 4:
	  if( peux_bouger_droite( p -> p1, *gr) == 1){
	    gr -> mat[p -> p2.x][p -> p2.y] = 0;
	    p -> p2.x = p -> p1.x;
	    p -> p2.y = p -> p1.y + 1;
	  }
	  break;
	}
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
	  if( d == 1){
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
            if( (peux_bouger_gauche( p->p2, *gr) == 1 &&  peux_bouger_gauche( p->p1, *gr) == 1 ) || (peux_bouger_gauche( p->p1, *gr) == 1 && p -> p2.x == -1) ){
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
      if( peux_bouger_gauche( *ptmp, *gr ) == 1 ){
	gr -> mat[ptmp -> x][ptmp -> y] = 0;
	ptmp -> y -= 1;
      }
    }
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
}

void deplacement(c_poyo *p, grille *gr){
  static int tmp_passer = 0;
  int tmp_act, attente;
  tmp_act = MLV_get_time(), attente = 150;
  if( MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED ){
      
    if( tmp_act - tmp_passer >= attente ){
        
      pivot_gauche(p, gr);
      pivot_droit(p, gr);
      deplacement_droit(p, gr);
      deplacement_gauche(p, gr);
      deplacement_bas(p, gr);

      tmp_passer = tmp_act;
    }
  }
}



/* -------------------------------- fin des definition de deplacement -------------------------------------*/

/*
int destruction(grille *gr){ renvoie le nombre de poyo detruits 
  int i, j, suite = 0, couleur;
  coordonne *position;
  for( i = 0 ; i < gr -> n ; i++ ){
    for( j = 0 ; j < gr -> m ; j++ ){
      if( gr -> mat[i][j] != 0){

	couleur = gr -> mat[i][j];
	suite++;
	p
      */



/* très content de cette fonction */
void est_a_coter(poyo *p, grille *gr, coordonne *tcoord, int *indice){
    int i;
    coordonne tmp;
    int coord[4][2]={ { -1, 0 }, /* poyo haut */
                    { 1, 0 },  /* poyo bas */
                    { 0, -1 }, /* poyo gauche */
                    { 0, 1} };  /* poyo droit */

    for( i = 0 ; i < 4 ; i++ ){
        tmp.x = p -> x + coord[i][0];
        tmp.y = p -> y + coord[i][1];
    }
    if( ( tmp.x > 0 && tmp.x < gr -> n - 1 ) && ( tmp.y > 0 && tmp.y < gr -> m - 1 ) && ( gr -> mat[ tmp.x ][ tmp.y ] == p -> couleur ) ){
        tcoord[*indice] = tmp;
        *indice += 1;
    }
    
}
