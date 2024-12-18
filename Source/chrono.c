#ifndef _CHRONO_C_
#define _CHRONO_C_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"
#include "math.h"

/* definition d'un chronometre */
void chronometre(hms * chrono){
    if( chrono -> milis < 59){
        chrono -> milis += 1;
    }else{
        chrono -> milis = 0;
        chrono -> secondes += 1;
        if( chrono -> secondes > 59 ){
            chrono -> secondes = 0;
            chrono -> minutes += 1;
            if(chrono->minutes == 60){  
                chrono->minutes = 0; 
                chrono->heures += 1;
            }
    
        }
    }
}

/* inttialisation du type chrono */
void ini_chrono( hms *chrono){
    chrono -> milis = 0;
    chrono -> secondes = 0;
    chrono -> minutes = 0;
    chrono -> heures = 0;
}

/* toutes les 30s augmente le niveau de la grille */
void gestion_niveau_grille(grille *gr, hms chrono){
    static int dernier_avancement = 0;
    int temps_ecoule;
    if( gr -> niveau < 50){
        temps_ecoule = chrono.secondes + chrono.minutes * 60 + chrono.heures * 3600;   
        if (temps_ecoule - dernier_avancement >= 30) {
            gr->niveau += 1;           
            dernier_avancement = temps_ecoule;  
        }
    }
}


/* accelere la vitesse de jeu */
int gestion_vitesse_grille(grille *gr){
    int vitesse;
    vitesse = 1000 - (pow(gr -> niveau,0.75) * 100);
    return vitesse;
}

#endif


    
    
