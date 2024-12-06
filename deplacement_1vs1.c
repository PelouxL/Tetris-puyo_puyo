#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "pieces.h"
#include "ini_poyo.h"


/* --------------------------- definition des fonction de deplacement du j1  ------------------------- */

void pivot_droit_j1(c_poyo *p, grille *gr){
  int d;
  d = disposition(*p);
  if( MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED ){
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

void pivot_gauche_j1(c_poyo *p, grille *gr){
  int d;
  d = disposition(*p);
  if( MLV_get_keyboard_state(MLV_KEYBOARD_a) == MLV_PRESSED ){
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

void deplacement_droit_j1( c_poyo *p, grille *gr){
  int d;
  poyo *ptmp = &p -> p1;

  if( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED ){
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



void deplacement_gauche_j1( c_poyo *p, grille *gr){
  int d;
  poyo *ptmp = &p -> p1;

  if( MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED ){
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


void deplacement_bas_j1( c_poyo *p, grille *gr){
  int d;
  poyo *ptmp = &p -> p1;

  if( MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED ){
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

void deplacement_j1(c_poyo *p, grille *gr){
    static int tmp_passer = 0;
    int tmp_act, attente;
    tmp_act = MLV_get_time(), attente = 150;
    if( MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_a) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED ){
      
        if( tmp_act - tmp_passer >= attente ){
        
            pivot_gauche_j1(p, gr);
            pivot_droit_j1(p, gr);
            deplacement_droit_j1(p, gr);
            deplacement_gauche_j1(p, gr);
            deplacement_bas_j1(p, gr);

            tmp_passer = tmp_act;
        }
    }
}

c_poyo sauvegarde_poyos_j1(tc_poyo *tpoyo, c_poyo poyo_sauvegarde, grille *gr, int *est_save1){
    c_poyo cptmp;
    static int tmp_passer = 0;
    int tmp_act, attente;
    tmp_act = MLV_get_time(), attente = 500;
    /* permet de savoir quel poyo va être vide */
    
    if( MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED && *est_save1 == 0){
              *est_save1 = 1;
        if( tmp_act - tmp_passer >= attente ){

            /* si rien dans la sauvegarde alors on recup juste la pieces */
            /* et on applique le roulement de poyo */
            if( poyo_sauvegarde.p1.couleur == 0 && poyo_sauvegarde.p2.couleur == 0){
                /* geres les cas ou les pieces ne sont pas complète */
                if(tpoyo[0] -> p1.pos == 1 && tpoyo[0] -> p2.pos == 0){
                    poyo_sauvegarde.p1 = tpoyo[0] -> p2;
                    poyo_sauvegarde.p2.couleur = 0;
                    poyo_sauvegarde .p2.fantome = 1;
                    gr->mat[tpoyo[0] -> p2.x][tpoyo[0] -> p2.y] = 0; 
                    roulement_poyo(tpoyo, gr);
                }
                else if(tpoyo[0] -> p1.pos == 0 && tpoyo[0] -> p2.pos == 1){
                    poyo_sauvegarde.p1 = tpoyo[0] -> p1;
                    poyo_sauvegarde.p2.couleur = 0;
                    poyo_sauvegarde.p2.fantome = 1;
                    gr->mat[tpoyo[0] -> p1.x][tpoyo[0] -> p1.y] = 0;  
                    roulement_poyo(tpoyo, gr);
                }
                else{
                    poyo_sauvegarde = *tpoyo[0];
                    gr -> mat[ tpoyo[0] -> p1.x ][tpoyo[0] -> p1.y ] = 0;
                    gr -> mat[ tpoyo[0] -> p2.x ][tpoyo[0] -> p2.y ] = 0;
                    roulement_poyo(tpoyo, gr);
                }
            }else{
                /* deux pieces imcomplette s'echange */
                if ( (poyo_sauvegarde.p2.couleur == 0 || poyo_sauvegarde.p1.couleur == 0 ) && tpoyo[0] -> p2.pos == 1) {
                    cptmp.p1 = tpoyo[0] -> p1;
                    cptmp.p2.couleur = 0;
                    cptmp.p2.fantome = 1;
                    gr->mat[tpoyo[0] -> p1.x][tpoyo[0] -> p1.y] = 0;
                    *tpoyo[0] = poyo_sauvegarde;
                    poyo_sauvegarde = cptmp;
                   
                
                }
                /* deux pieces imcomplette s'echange */
                else if( (poyo_sauvegarde.p1.couleur == 0 ||  poyo_sauvegarde.p1.couleur == 0 ) && tpoyo[0] -> p1.pos == 1) {
                    cptmp.p1 = tpoyo[0] -> p2;
                    cptmp.p2.couleur = 0;
                    cptmp.p2.fantome = 1;
                    gr->mat[tpoyo[0] -> p2.x][tpoyo[0] -> p2.y] = 0;
                    *tpoyo[0] = poyo_sauvegarde;
                    poyo_sauvegarde = cptmp;
                  
                }
                /*  pieces complète save s'echange avec incomplete */
                else if( tpoyo[0] -> p1.pos == 1 || tpoyo[0] -> p2.pos == 1){
                    if( tpoyo[0] -> p1.pos == 0){
                        cptmp.p1 = tpoyo[0] -> p1;
                        cptmp.p2.couleur = 0;
                        cptmp.p2.fantome = 1;
                        gr->mat[tpoyo[0] -> p1.x][tpoyo[0] -> p1.y] = 0;
                        *tpoyo[0] = poyo_sauvegarde;
                        poyo_sauvegarde = cptmp;
                    }
                    else if( tpoyo[0] -> p2.pos == 0){
                        cptmp.p1 = tpoyo[0]-> p2;
                        cptmp.p2.couleur = 0;
                        cptmp.p2.fantome = 1;
                        gr->mat[tpoyo[0] -> p2.x][tpoyo[0] -> p2.y] = 0;
                        *tpoyo[0] = poyo_sauvegarde;
                        poyo_sauvegarde = cptmp;
                    }             
                }
                else{
                    cptmp = *tpoyo[0];
                    gr -> mat[ tpoyo[0] -> p1.x ][tpoyo[0] -> p1.y ] = 0;
                    gr -> mat[ tpoyo[0] -> p2.x ][tpoyo[0] -> p2.y ] = 0;
                    *tpoyo[0] = poyo_sauvegarde;
                    poyo_sauvegarde = cptmp;
                }
            }
           
            tmp_passer = tmp_act;
        }
    }
    poyo_sauvegarde.apparait = 0;
    poyo_sauvegarde.p1.x = 0;
    poyo_sauvegarde.p1.y = 0;
    poyo_sauvegarde.p2.x = -1;
    poyo_sauvegarde.p2.y = -1;
    return poyo_sauvegarde;
}
        

/* --------------------------------------------------- deplacement pour le deuxième joueur */



void pivot_droit_j2(c_poyo *p, grille *gr){
  int d;
  d = disposition(*p);
  if( MLV_get_keyboard_state(MLV_KEYBOARD_p) == MLV_PRESSED ){
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

void pivot_gauche_j2(c_poyo *p, grille *gr){
  int d;
  d = disposition(*p);
  if( MLV_get_keyboard_state(MLV_KEYBOARD_o) == MLV_PRESSED ){
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

void deplacement_droit_j2( c_poyo *p, grille *gr){
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



void deplacement_gauche_j2( c_poyo *p, grille *gr){
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


void deplacement_bas_j2( c_poyo *p, grille *gr){
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

void deplacement_j2(c_poyo *p, grille *gr){
    static int tmp_passer = 0;
    int tmp_act, attente;
    tmp_act = MLV_get_time(), attente = 150;
    if( MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_o) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_p) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED ){
      
        if( tmp_act - tmp_passer >= attente ){
        
            pivot_gauche_j2(p, gr);
            pivot_droit_j2(p, gr);
            deplacement_droit_j2(p, gr);
            deplacement_gauche_j2(p, gr);
            deplacement_bas_j2(p, gr);

            tmp_passer = tmp_act;
        }
    }
}

c_poyo sauvegarde_poyos_j2(tc_poyo *tpoyo, c_poyo poyo_sauvegarde, grille *gr, int *est_save2 ){
  c_poyo cptmp;
  static int tmp_passer = 0;
  int tmp_act, attente;
  tmp_act = MLV_get_time(), attente = 500;
  /* permet de savoir quel poyo va être vide */
    
  if( MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED && *est_save2 == 0){

    *est_save2 = 1;
    if( tmp_act - tmp_passer >= attente ){

      /* si rien dans la sauvegarde alors on recup juste la pieces */
      /* et on applique le roulement de poyo */
      if( poyo_sauvegarde.p1.couleur == 0 && poyo_sauvegarde.p2.couleur == 0){
	/* geres les cas ou les pieces ne sont pas complète */
	if(tpoyo[0] -> p1.pos == 1 && tpoyo[0] -> p2.pos == 0){
	  poyo_sauvegarde.p1 = tpoyo[0] -> p2;
	  poyo_sauvegarde.p2.couleur = 0;
	  poyo_sauvegarde .p2.fantome = 1;
	  gr->mat[tpoyo[0] -> p2.x][tpoyo[0] -> p2.y] = 0; 
	  roulement_poyo(tpoyo, gr);
	}
	else if(tpoyo[0] -> p1.pos == 0 && tpoyo[0] -> p2.pos == 1){
	  poyo_sauvegarde.p1 = tpoyo[0] -> p1;
	  poyo_sauvegarde.p2.couleur = 0;
	  poyo_sauvegarde.p2.fantome = 1;
	  gr->mat[tpoyo[0] -> p1.x][tpoyo[0] -> p1.y] = 0;  
	  roulement_poyo(tpoyo, gr);
	}
	else{
	  poyo_sauvegarde = *tpoyo[0];
	  gr -> mat[ tpoyo[0] -> p1.x ][tpoyo[0] -> p1.y ] = 0;
	  gr -> mat[ tpoyo[0] -> p2.x ][tpoyo[0] -> p2.y ] = 0;
	  roulement_poyo(tpoyo, gr);
	}
      }else{
	/* deux pieces imcomplette s'echange */
	if ( (poyo_sauvegarde.p2.couleur == 0 || poyo_sauvegarde.p1.couleur == 0 ) && tpoyo[0] -> p2.pos == 1) {
	  cptmp.p1 = tpoyo[0] -> p1;
	  cptmp.p2.couleur = 0;
	  cptmp.p2.fantome = 1;
	  gr->mat[tpoyo[0] -> p1.x][tpoyo[0] -> p1.y] = 0;
	  *tpoyo[0] = poyo_sauvegarde;
	  poyo_sauvegarde = cptmp;
                   
                
	}
	/* deux pieces imcomplette s'echange */
	else if( (poyo_sauvegarde.p1.couleur == 0 ||  poyo_sauvegarde.p1.couleur == 0 ) && tpoyo[0] -> p1.pos == 1) {
	  cptmp.p1 = tpoyo[0] -> p2;
	  cptmp.p2.couleur = 0;
	  cptmp.p2.fantome = 1;
	  gr->mat[tpoyo[0] -> p2.x][tpoyo[0] -> p2.y] = 0;
	  *tpoyo[0] = poyo_sauvegarde;
	  poyo_sauvegarde = cptmp;
                  
	}
	/*  pieces complète save s'echange avec incomplete */
	else if( tpoyo[0] -> p1.pos == 1 || tpoyo[0] -> p2.pos == 1){
	  if( tpoyo[0] -> p1.pos == 0){
	    cptmp.p1 = tpoyo[0] -> p1;
	    cptmp.p2.couleur = 0;
	    cptmp.p2.fantome = 1;
	    gr->mat[tpoyo[0] -> p1.x][tpoyo[0] -> p1.y] = 0;
	    *tpoyo[0] = poyo_sauvegarde;
	    poyo_sauvegarde = cptmp;
	  }
	  else if( tpoyo[0] -> p2.pos == 0){
	    cptmp.p1 = tpoyo[0]-> p2;
	    cptmp.p2.couleur = 0;
	    cptmp.p2.fantome = 1;
	    gr->mat[tpoyo[0] -> p2.x][tpoyo[0] -> p2.y] = 0;
	    *tpoyo[0] = poyo_sauvegarde;
	    poyo_sauvegarde = cptmp;
	  }             
	}
	else{
	  cptmp = *tpoyo[0];
	  gr -> mat[ tpoyo[0] -> p1.x ][tpoyo[0] -> p1.y ] = 0;
	  gr -> mat[ tpoyo[0] -> p2.x ][tpoyo[0] -> p2.y ] = 0;
	  *tpoyo[0] = poyo_sauvegarde;
	  poyo_sauvegarde = cptmp;
	}
      }
           
      tmp_passer = tmp_act;
    }
  }
  poyo_sauvegarde.apparait = 0;
  poyo_sauvegarde.p1.x = 0;
  poyo_sauvegarde.p1.y = 0;
  poyo_sauvegarde.p2.x = -1;
  poyo_sauvegarde.p2.y = -1;
  return poyo_sauvegarde;
}
