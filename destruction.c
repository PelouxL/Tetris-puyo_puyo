#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "ini_poyo.h"
#include <MLV/MLV_all.h>



int est_deja_visiter( coordonne *est_visiter, int taille_visiter, coordonne coord){
    int i;
    for( i = 0 ; i < taille_visiter ; i++ ){
        if ( est_visiter[i].x == coord.x && est_visiter[i].y == coord.y ){
            return 1;
        }
    }
    return 0;
}


void fusion_coord(coordonne *tcord1, coordonne *tcord2, int *taille1, int taille2){
  int i, j, ajout;

  for( i = 0 ; i < taille2 ; i++ ){ /* on parcours le deuxième tableau*/
    ajout = 1 ;                     /* on pars du principe qu'on ajoute au debut */
    for( j = 0 ; j < *taille1 ; j++ ){
      if( tcord1[j].x == tcord2[i].x && tcord1[j].y == tcord2[i].y ){
	ajout = 0;                  /* si on trouve le meme indice ajout = 0 donc on ajote rien */
      }
    }
    if( ajout == 1 && *taille1 < 100){
      tcord1[*taille1].x = tcord2[i].x;  /* ajoute = 1 donc on ajoute dans notre tcord 1 */
      tcord1[*taille1].y = tcord2[i].y;
      (*taille1)++;
    }
  }
}
  

/* très content de cette fonction */
int est_a_coter(poyo *p, grille *gr, coordonne *tcoord, coordonne *est_visiter, int taille_visiter){
    int i, indice = 0;
    coordonne tmp;
    int coord[5][2]={
        { 0, 0 },
        { -1, 0 }, /* poyo haut */
        { 1, 0 },  /* poyo bas */
        { 0, -1 }, /* poyo gauche */
        { 0, 1} };  /* poyo droit */

    for( i = 0 ; i < 5 ; i++ ){
        tmp.x = p -> x + coord[i][0];
        tmp.y = p -> y + coord[i][1];
    
        if( ( tmp.x >= 0 && tmp.x < gr -> n ) && ( tmp.y >= 0 && tmp.y < gr -> m  ) && ( gr -> mat[ tmp.x ][ tmp.y ] == p -> couleur ) ){

            
            if (!est_deja_visiter(est_visiter, taille_visiter, tmp)){
                
                printf("Vérification de la case (%d, %d) - ", tmp.x, tmp.y);
                printf("Couleur trouvée: %d, Couleur cible: %d\n", gr->mat[tmp.x][tmp.y], p->couleur);
                tcoord[indice] = tmp;
                indice++;
            }
        }
    }
    return indice;
}

int recup_coord(poyo *p, grille *gr, coordonne *tcord){
    int taille_nouvelle , taille_visiter = 1, indice = 1, i;
    coordonne est_visiter[100], nouvelle_coord[100];
    poyo tmp;

    
    est_visiter[0].x = p -> x;
    est_visiter[0].y = p -> y;

    tcord[0].x = est_visiter[0].x;
    tcord[0].y = est_visiter[0].y;
    
    do {
        taille_nouvelle = 0;
        
        for( i = 0 ; i < indice ; i++){
            tmp.x = tcord[i].x;
            tmp.y = tcord[i].y;
            tmp.couleur = p -> couleur;

            taille_nouvelle = est_a_coter( &tmp, gr, nouvelle_coord, est_visiter, taille_visiter);
            fusion_coord(tcord, nouvelle_coord, &indice, taille_nouvelle);

            fusion_coord(est_visiter, nouvelle_coord, &taille_visiter, taille_nouvelle);
            
        }
            
    } while( taille_nouvelle > 0 && indice < 100 );
          

    return indice;
}


/* penser a comment gerer le score */
int destruction(coordonne *tcord, grille *gr, int taille_t){
  int i;
  if( taille_t >= 4 ){
    printf("Destruction d'un groupe de %d Poyos.\n", taille_t);
    for( i = 0 ; i < taille_t ; i++){
      printf("(%d, %d)\n", tcord[i].x, tcord[i].y);
      gr -> mat[tcord[i].x][tcord[i].y] = 0;
    }
  }else{
    return 0;
  }
  return taille_t;
}

void chutte_destruction(grille *gr){
  int i, j, k;
  /* on verifie pour chaque case du tableau */
  for( i = gr -> n - 2 ; i >= 0  ; i-- ){ 
    for( j = gr -> m - 1 ; j >= 0 ; j-- ){

      /* si n tombe sur un poyo alors */
      if( gr -> mat[i][j] != 0 ){
	k = i;
	/* on regarde si dessous la piece peux descendre */
	while( (k + 1) < gr -> n && gr -> mat[k + 1][j] == 0 ){
	  gr -> mat[k + 1][j] =  gr -> mat[k][j];
	  gr -> mat[k][j] = 0;
	  k++;
 
	}
      }
    }
  }
}

int post_destruction( grille *gr ){
  int taille_tcordall, detruite = 0, i, j;
  coordonne tcordall[100];
  poyo ptmp;

  for ( i = 0; i < gr -> n ; i++ ) {
    for ( j = 0; j < gr -> m ; j++ ) {
      if (gr -> mat[i][j] > 0) { /* Vérifie la présence d'un poyo */
	ptmp.x = i;
	ptmp.y = j;
	ptmp.couleur = gr -> mat[i][j];
	taille_tcordall = recup_coord(&ptmp, gr, tcordall);
	if(taille_tcordall >=4){
	  detruite += destruction(tcordall, gr, taille_tcordall);
	  chutte_destruction(gr);
	 
	}
      }
    }
  }
  return detruite;
}

int chute_et_destruction(c_poyo *tpoyo, grille *gr){
  int nb_dest1, nb_dest2, taille_tcord1 = 0, taille_tcord2 = 0, scorefac = 1, scoredest = 0, tmprecup, tot = 0;
  coordonne tcord1[100],tcord2[100];
    
  /* principe des coordonnées et de la destruction */
  if(tpoyo[0].p1.pos == 1 && tpoyo[0].p2.pos == 1 ){
    nb_dest1 = 0;
    nb_dest2 = 0;
    taille_tcord1 = recup_coord(&tpoyo[0].p1, gr, tcord1);           
    nb_dest1 = destruction(tcord1, gr, taille_tcord1);
    taille_tcord2 = recup_coord(&tpoyo[0].p2, gr, tcord2);
    nb_dest2 = destruction(tcord2, gr, taille_tcord2);
    scoredest = nb_dest1 + nb_dest2;

    /* verifie que si l'on detruit des poyos alors une chute se fait*/
    if( nb_dest1 > 0 || nb_dest2 > 0){
      chutte_destruction(gr);
      
      /* cette boucle permet de detruire tout les nouveau groupe causer par une chute */
      while( (tmprecup = post_destruction(gr)) > 0){
	MLV_actualise_window();
	scorefac += 1;
	scoredest += tmprecup;
	/* il faut actualiser entre les destrcution */
	/* flemme pour l'instant */
	MLV_wait_milliseconds(200);

      }
    }
 
  }
  tot = scorefac * scoredest;
  return tot;
}
	      
	    
