#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "ini_poyo.h"
#include "affichage_mlv.h"
#include "destruction.h"
#include "chrono.h"

void jeu(grille *gr, joueur *je, c_poyo tpoyo[4]){
  int temps, duree ;
  c_poyo ptmp;
  hms chrono;
  struct timespec debut, fin, maintenant, dernier_avancement, chrono_deb, chrono_fin;
  chrono.secondes = 0;
  chrono.minutes = 0;
  chrono.heures = 0;
    
  

  initialisation_cpoyo_vide(&ptmp);   
  MLV_clear_window(MLV_COLOR_BLACK);
  clock_gettime( CLOCK_REALTIME, &dernier_avancement );
  clock_gettime( CLOCK_REALTIME, &chrono_deb);
    
  while(1){
    /* permet de gerer le framrate */
    clock_gettime( CLOCK_REALTIME, &debut );

    /* permet de gérer le temps passer entre chaque avancement */
    clock_gettime( CLOCK_REALTIME, &maintenant );

    clock_gettime( CLOCK_REALTIME, &chrono_fin);

    /* gestion de l'avancement du chronometre */
    if(( chrono_fin.tv_sec - chrono_deb.tv_sec ) > 1 ||  ( (chrono_fin.tv_sec - chrono_deb.tv_sec) == 1 && chrono_fin.tv_nsec >= chrono_deb.tv_nsec) ){
      chronometre( &chrono);
      chrono_deb = chrono_fin;
    }

    if( tpoyo[0].apparait == 0 ){
      apparition_piece(&tpoyo[0], gr);
    }
    if( tpoyo[0].p1.pos == 1 && tpoyo[0].p2.pos == 1 ){
      roulement_poyo(tpoyo, gr);
    }

	
    if(( maintenant.tv_sec - dernier_avancement.tv_sec ) > 1 ||  ( (maintenant.tv_sec - dernier_avancement.tv_sec) == 1 && maintenant.tv_nsec >= dernier_avancement.tv_nsec) ){
      avancement_piece(&tpoyo[0], gr);
      dernier_avancement = maintenant;
    }
    
    aff_etat(*gr, *je, chrono);
    aff_poyos(tpoyo, &ptmp);
    
    printf("\n");

    deplacement(&tpoyo[0], gr);
    ptmp = sauvegarde_poyos(tpoyo, ptmp, gr);
    
    affiche_c_poyo(&tpoyo[0]);
    actualisation_poyo(&tpoyo[0], gr);

    /* principe des coordonnées et de la destruction */
    je -> score += chute_et_destruction(&tpoyo[0], gr);

    clock_gettime(CLOCK_REALTIME, &fin );
    
    /* Framerate */
    duree = ((fin.tv_sec - debut.tv_sec) * 1000) + ((fin.tv_nsec - debut.tv_nsec) / 1000000);
    temps = 16 - duree ;
    if(temps > 0){
      MLV_wait_milliseconds(temps);
    }
    MLV_actualise_window();
  }
    
}
