#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "ini_poyo.h"



void fusion_coord(coordonne *tcord1, coordonne *tcord2, int *taille1, int taille2){
  int i, j, ajout;

  for( i = 0 ; i < taille2 ; i++ ){ /* on parcours le deuxième tableau*/
    ajout = 1 ;                     /* on pars du principe qu'on ajoute au debut */
    for( j = 0 ; j < *taille1 ; j++ ){
      if( tcord1[j].x == tcord2[i].x && tcord1[j].y == tcord2[i].y ){
	ajout = 0;                  /* si on trouve le meme indice ajout = 0 donc on ajote rien */
      }
    }
    if( ajout == 1){
      tcord1[*taille1].x = tcord2[i].x;  /* ajoute = 1 donc on ajoute dans notre tcord 1 */
      tcord1[*taille1].y = tcord2[i].y;
      (*taille1) +=1;
    }
  }
}
  

/* très content de cette fonction */
int est_a_coter(poyo *p, grille *gr, coordonne *tcoord){
  int i, indice = 0;
    coordonne tmp;
    int coord[4][2]={ { -1, 0 }, /* poyo haut */
                    { 1, 0 },  /* poyo bas */
                    { 0, -1 }, /* poyo gauche */
                    { 0, 1} };  /* poyo droit */

    for( i = 0 ; i < 4 ; i++ ){
      tmp.x = p -> x + coord[i][0];
      tmp.y = p -> y + coord[i][1];
    
      if( ( tmp.x > 0 && tmp.x < gr -> n - 1 ) && ( tmp.y > 0 && tmp.y < gr -> m - 1 ) && ( gr -> mat[ tmp.x ][ tmp.y ] == p -> couleur ) ){
        tcoord[indice] = tmp;
        indice += 1;
      }
    }
    return indice;
}


void recup_coord(poyo *p, grille *gr, coordonne *tcord){
  int taille_nouvelle , taille_visiter = 0, indice = 0, i, j, k, existe = 0;
  coordonne est_visiter[100], nouvelle_coord[100];
  poyo tmp;
  

  est_visiter[taille_visiter].x = p -> x;
  est_visiter[taille_visiter].y = p -> y;

  tcord[indice].x = p -> x;
  tcord[indice].y = p ->y;
  indice += 1;
  
  do {
    taille_nouvelle = 0;

    for( i = 0 ; i < taille_visiter ; i++ ){
      tmp.x = est_visiter[i].x;
      tmp.y = est_visiter[i].y;
      tmp.couleur = p -> couleur;

      taille_nouvelle = est_a_coter(&tmp, gr, nouvelle_coord);
      
      fusion_coord(tcord, nouvelle_coord, &indice, taille_nouvelle);

      for( j = 0 ; j < taille_nouvelle ; j++ ){
	existe = 0;
	for( k = 0 ; k < taille_visiter ; k++ ){
	  if( nouvelle_coord[j].x == est_visiter[k].x && nouvelle_coord[j].y == est_visiter[k].y ){
	    existe = 1;
	  }
	}
	if( existe == 0 ){
	  est_visiter[taille_visiter] = nouvelle_coord[j];
	  taille_visiter += 1;
	}
      }
    }
    
  }while ( taille_nouvelle > 0);

}
