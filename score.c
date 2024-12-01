#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ini_poyo.h"
#include "pieces.h"



/* permet de calculer le score max par rapport au temps */
void calcule_score(int destruction, joueur *je, hms chrono){
    int total = 0;
    total = chrono.milis + chrono.secondes + destruction *(chrono.minutes * 1.5) + 100000 * chrono.heures;
    if(je -> score + total < 999999999 ){
      je -> score += total;
    }
}

/*-------- fonction permettant de gerer les nouveaux score ------*/

/* permet de recupperer le score dans un tableau tjoueur */
int recup_score( char *nom, tjoueur *je_score ){
    int i;
    FILE  *fichier;

    if( (fichier = fopen( nom, "r")) == NULL ){
        printf("Erreur lors de l'ouverture\n");
        return -1;
    }
    for( i = 0 ; i < 10 ; i++ ){
        if( (fscanf( fichier, "%s %d", je_score[i] -> pseudo, &je_score[i] -> score) ) != 2){
            printf("erreur lors de la reccuperation\n");
            return -1;
        }
    }
    fclose(fichier);
    return 1;
}


/* fonction de permutation de deux variable joueur */
int echange_joueur_score(joueur *j1, joueur *j2){
    joueur tmp;
    tmp.score = 0;
    tmp.pseudo ="temporaire";
    
    if( (strcpy(tmp.pseudo, j1 -> pseudo)) == NULL ){
        printf("Erreur lors du deplacement\n");
        return -1;
    }
    tmp.score = j1 -> score;

    if( (strcpy(j1 -> pseudo, j2 -> pseudo)) == NULL ){
        printf("Erreur lors du deplacement\n");
        return -1;
    }
    j1 -> score = j2 -> score;

    if( (strcpy(j2 -> pseudo, tmp.pseudo)) == NULL ){
        printf("Erreur lors du deplacement\n");
        return -1;
    }
    j2 -> score = tmp.score;
    return 1;

}
    


/* tri la liste des score et renvoie 1 ou -1 en cas d'erreurs */
int tri_insertion( char *nom, joueur nouveau_score, tjoueur *je_score ){
    /* on va peut-être devoir ne pas ouvrir le file ici */
    FILE *fichier;
    int i, j;

    if( (fichier = fopen( nom, "w+")) == NULL ){
        printf("erreur lros de l'overture\n");
        return -1;
    }
    
    /* tri du score */
    for ( i = 0 ; i < 10 ; i++ ){
        if( je_score[i] -> score  < nouveau_score.score ){
            for( j = i ; j < 9 ; j++ ){
                /* on verifie qu'il n'y est pas de pb dans l'echange de position */
                if (echange_joueur_score(je_score[i+1], je_score[i]) == -1 ){
                    printf("Erreur lors du deplacement de score\n");
                    return -1;
                }
            }
            /* on place notre score au bonne endroit */
            if( echange_joueur_score(je_score[i], &nouveau_score) == -1 ){
                printf("Erreur lors du deplacement de score\n");
                return -1;
            }
        }
    }
    /* ecriture sur le fichier */
    for( i = 0 ; i < 10 ; i ++ ){
        fprintf( fichier, "%s %d\n", je_score[i] -> pseudo, je_score[i] -> score);
    }
    
    fclose(fichier);
    return 1;
    
}

/* --------------------------------------------------- */
/* ------------------- peut-être le changer de module ? -------*/
void creation_malus(c_poyo *poyo_piege, grille *gr, int absisse){
  initialisation_cpoyo_vide( poyo_piege);
  poyo_piege -> p1.couleur = 6;
  poyo_piege -> p2.couleur = 6;
  poyo_piege -> p2.x = gr -> n - 2;
  poyo_piege -> p1.x = gr -> n - 1;
  poyo_piege -> p2.y = absisse;
  poyo_piege -> p1.y = absisse;
  poyo_piege -> p2.fantome = 1;
  poyo_piege -> p1.fantome = 1;
}

void decalage(int absisse, grille *gr){
  int i, tmp;
  for( i = 1 ; i <  gr -> n ; i++){
    if( gr -> mat[i][absisse] != 0){
      tmp = gr -> mat[i][absisse];
      gr -> mat[i - 2][absisse] = tmp;
      gr -> mat[i][absisse] = 0;
    }
  }
}


void appliquer_malus(int score, grille *gr){
  int absisse;
  c_poyo poyo_piege;
  absisse = rand()%( gr -> m -1);
  if( score >= 16 ){
    creation_malus( &poyo_piege, gr, absisse);
    affiche_c_poyo( &poyo_piege );
    decalage( absisse, gr );
    poyo_piege.apparait = 1;
    actualisation_poyo( &poyo_piege, gr);
  }
}


    
