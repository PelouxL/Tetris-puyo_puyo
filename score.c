#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void calcule_score(int destruction, joueur *je, hms chrono){
    int total = 0;
    total = chrono.milis + chrono.secondes + destruction *(chrono.minutes * 1.5) + 100000 * chrono.heures;
    je -> score += total;
}

int recup_score( char *nom, int *score[10] ){
    int i;
    FILE * fichier;

    if( fichier = fopen( nom, 'r') == NULL ){
        printf("Erreur lors de l'ouverture\n");
        return -1;
    }
    for( i = 0 ; i < 10 ; i++ ){
        if( (fscanf( fichier, "%d", score[i]) ) !=10){
            printf("erreur lors de la reccuperation\n");
            return -1;
        }
    }
    fclose(fichier);
    return 1;
}

int tri_insertion( int score, int *tabscore[10] ){
    /* on va peut-être devoir ne pas ouvrir le file ici */
    FILE * fichier;
    int i, tmp;

    if( fichier = fopen( nom, "w+") == NULL ){
        printf("erreur lros de l'overture\n");
        return -1;
    }
    
    for ( i = 0 ; i < 10 ; i++ ){
        if( tabscore[i] < score ){
            for( j = i ; j < 9 ; j++ ){
                tabscore[j + 1] = tabscore[i];
            }
            tabscore[i] = score;
        }
    }
    return 1;
}
       