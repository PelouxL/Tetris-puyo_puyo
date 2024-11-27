#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"

/* definition d'un chronometre */

void chronometre(hms * chrono){
    if( chrono -> milis < 59){
        chrono -> milis += 1;
    }else{
        chrono -> milis = 0;
        chrono -> secondes += 1;
        if( chrono -> secondes < 59 ){
            chrono -> secondes += 1;
        }else{
            chrono -> secondes = 0;
            chrono -> minutes += 1;
            if( chrono -> minutes > 59 ){
                chrono -> heures += 1;
            }
        }
    }
}

/* void gestion_vitesse_grille(grille *gr, hms chrono, float vitesse){ */
    
    

    
    
