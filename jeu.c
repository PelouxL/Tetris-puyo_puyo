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
#include "score.h"
#include "deplacement_1vs1.h"
#include "fin_partie.h"

void jeu(grille *gr, joueur *je, c_poyo tpoyo[4]){
    int temps, duree, tmpscore = 0, vitesse, temps_ecoule;
    c_poyo ptmp;
    hms chrono;
    struct timespec debut, fin, maintenant, dernier_avancement;
    
    chrono.secondes = 0;
    chrono.minutes = 0;
    chrono.heures = 0;
    initialisation_cpoyo_vide(&ptmp);   
    MLV_clear_window(MLV_COLOR_BLACK);
    clock_gettime( CLOCK_REALTIME, &dernier_avancement );
    
    while(1){
        /* permet de gerer le framrate */
        clock_gettime( CLOCK_REALTIME, &debut );

        /* permet de gérer le temps passer entre chaque avancement */
        clock_gettime( CLOCK_REALTIME, &maintenant );


        /* gestion de l'avancement du temps, attention le jeu tourne a 60 fps donc ça marche mais*/
        /* si la cadence vient a changer sa posera un problème */
        chronometre( &chrono);

        /* gestion de la valeur de la vitesse */
        gestion_niveau_grille(gr, chrono);
        vitesse = gestion_vitesse_grille(gr);
        
        if( tpoyo[0].apparait == 0 ){
            apparition_piece(&tpoyo[0], gr);
        }
        if( tpoyo[0].p1.pos == 1 && tpoyo[0].p2.pos == 1 ){
            roulement_poyo(tpoyo, gr);
        }
        temps_ecoule = (maintenant.tv_sec - dernier_avancement.tv_sec) * 1000 + (maintenant.tv_nsec - dernier_avancement.tv_nsec) / 1000000;
        
	/* gestion de la vitesse de chutte des pieces */
       if (temps_ecoule >= vitesse) {
                avancement_piece(&tpoyo[0], gr);
                dernier_avancement = maintenant;
            }

        /* affichage de la grille et des poyos */
        aff_etat(*gr, *je, chrono);
        aff_poyos(tpoyo, &ptmp);
    
        printf("\n");

        deplacement(&tpoyo[0], gr);
        ptmp = sauvegarde_poyos(tpoyo, ptmp, gr);
    
        affiche_c_poyo(&tpoyo[0]);
        actualisation_poyo(&tpoyo[0], gr);

        /* principe des coordonnées, destruction et destrucion */
        tmpscore = chute_et_destruction(&tpoyo[0], gr);
        if( tmpscore > 0 ){
            calcule_score(tmpscore, je, chrono);
        }

	/* on verifie que la partie n'est pas fini */
	if( fin_solo( tpoyo[0], *je, *gr) == 1 ){
	  printf(" et la ???? \n");
	  return ;
	}
        
	
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


void jeu_1vs1(grille *gr1, grille *gr2, joueur *je1, joueur *je2, c_poyo tpoyo1[4], c_poyo tpoyo2[4]){
  int temps, duree, tmpscore1 = 0, tmpscore2 = 0, vitesse, temps_ecoule;
  c_poyo ptmp1, ptmp2;
  hms chrono;
  struct timespec debut, fin, maintenant, dernier_avancement;
    
  chrono.secondes = 0;
  chrono.minutes = 0;
  chrono.heures = 0;
  
  initialisation_cpoyo_vide(&ptmp1);
   initialisation_cpoyo_vide(&ptmp2);
  MLV_clear_window(MLV_COLOR_BLACK);
  clock_gettime( CLOCK_REALTIME, &dernier_avancement );
    
  while(1){
    /* permet de gerer le framrate */
    clock_gettime( CLOCK_REALTIME, &debut );

    /* permet de gérer le temps passer entre chaque avancement */
    clock_gettime( CLOCK_REALTIME, &maintenant );


    /* gestion de l'avancement du temps, attention le jeu tourne a 60 fps donc ça marche mais*/
    /* si la cadence vient a changer sa posera un problème */
    chronometre( &chrono);

    /* gestion de la valeur de la vitesse , on 1vs 1 on peux se baser sur la meme grille*/
    gestion_niveau_grille(gr1, chrono);
    gestion_niveau_grille(gr2, chrono);
    vitesse = gestion_vitesse_grille(gr1);
        
    if( tpoyo1[0].apparait == 0 ){
      apparition_piece(&tpoyo1[0], gr1);
    }
     if( tpoyo2[0].apparait == 0 ){
      apparition_piece(&tpoyo2[0], gr2);
    }

     /* -------------- gere le roulement des poyos des 2 joueurs */
     
    if( tpoyo1[0].p1.pos == 1 && tpoyo1[0].p2.pos == 1 ){
      roulement_poyo(tpoyo1, gr1);
    }

     if( tpoyo2[0].p1.pos == 1 && tpoyo2[0].p2.pos == 1 ){
      roulement_poyo(tpoyo2, gr2);
    }

     /* -------------------------------------------------------*/
    temps_ecoule = (maintenant.tv_sec - dernier_avancement.tv_sec) * 1000 + (maintenant.tv_nsec - dernier_avancement.tv_nsec) / 1000000;
        
    /* gestion de la vitesse de chutte des pieces */
    if (temps_ecoule >= vitesse) {
      avancement_piece(&tpoyo1[0], gr1);
      avancement_piece(&tpoyo2[0], gr2);
      dernier_avancement = maintenant;
    }

    /* affichage de la grille et des poyos */
    aff_grille( *gr1);
    aff_1vs1_etat( *gr1, *gr2, *je1, *je2, chrono );
    
    /* aff_poyos(tpoyo, &ptmp); */
    aff_1vs1_poyos(tpoyo1, tpoyo2, &ptmp1, &ptmp2);
    
    printf("\n");

    deplacement_j1(&tpoyo1[0], gr1);
    deplacement_j2(&tpoyo2[0], gr2);
    
    ptmp1 = sauvegarde_poyos_j1(tpoyo1, ptmp1, gr1);
    ptmp2 = sauvegarde_poyos_j2(tpoyo2, ptmp2, gr2);

    /* c koi ca deja */
    affiche_c_poyo(&tpoyo1[0]);
    
    actualisation_poyo(&tpoyo1[0], gr1);
    actualisation_poyo(&tpoyo2[0], gr2);

    /* principe des coordonnées, destruction et destrucion */
    tmpscore1 = chute_et_destruction(&tpoyo1[0], gr1);
    tmpscore2 = chute_et_destruction(&tpoyo2[0], gr2);

    
    if( tmpscore1 > 0 ){
      appliquer_malus(tmpscore1, gr2);
      calcule_score(tmpscore1, je1, chrono);   
    }
     if( tmpscore2 > 0 ){
       appliquer_malus(tmpscore2, gr1);
      calcule_score(tmpscore2, je2, chrono);   
    }

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
