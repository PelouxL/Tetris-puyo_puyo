#ifndef _INI_POYO_C_
#define _INI_POYO_C_
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "pieces.h"
#include <MLV/MLV_all.h>

/* affiche la structure dun poyo sur le terminal */
void affiche_c_poyo(c_poyo *p){
    printf("voici la couleur %d le x %d et le y %d\n p2 %d %d et %d\n", p -> p1.couleur, p -> p1.x, p -> p1.y , p -> p2.couleur, p -> p2.x, p -> p2.y);
}

/* initialise la structure d'un poyo */
void initialisation_cpoyo(c_poyo *cp){
    /* 0 = vide , 1 = red, 2 = green, 3 = blue, 4 = yellow, 5 = purple */
    cp -> p1.couleur = (rand()%5)+1;
    cp -> p2.couleur = (rand()%5)+1;
    cp -> p1.x = 0; 
    cp -> p1.y = 0;
    cp -> p1.pos = 0;
    cp -> p2.x = -1;
    cp -> p2.y = -1;
    cp -> p2.pos = 0;
    cp -> apparait = 0;
    cp -> p1.fantome = 0;
    cp -> p2.fantome = 0;

}

/* initialise la structure d'un poyo vide */
void initialisation_cpoyo_vide(c_poyo *cp){
    /* 0 = vide , 1 = red, 2 = green, 3 = blue */
    cp -> p1.couleur = 0;
    cp -> p2.couleur = 0;
    cp -> p1.x = 0; 
    cp -> p1.y = 0;
    cp -> p1.pos = 0;
    cp -> p2.x = -1;
    cp -> p2.y = -1;
    cp -> p2.pos = 0;
    cp -> apparait = 0;
    cp -> p1.fantome = 0;
    cp -> p2.fantome = 0;


}

/* initialise le tpoyo */
void ini_poyo_chaine(c_poyo *tpoyo, int n){
    int i;
    for(i = 0 ; i < n ; i++){
        initialisation_cpoyo(&tpoyo[i]);
    }
}

/* fais un decalage a gauche du tpoyo */
void decalage_gauche(c_poyo *tpoyo, int n){ /* n correspond a la taille de t */
    int i;
    for( i = 0 ; i < n - 1 ; i++ ){
        tpoyo[i] = tpoyo[i + 1];
    }
}

/* fais la creation du poyo 4 et le decalage */
void roulement_poyo(c_poyo *tpoyo, grille *gr){
    if( tpoyo[0].apparait == 0 ){
        apparition_piece(&tpoyo[0], gr);
    }
    decalage_gauche(tpoyo, 4);
    initialisation_cpoyo(&tpoyo[3]);
}

#endif