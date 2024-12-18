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
#include "menu.h"
#include "animation.h"

void jeu(grille *gr, joueur *je, c_poyo tpoyo[4], c_poyo *ptmp){
  int temps, duree, tmpscore = 0, vitesse, temps_ecoule, dest, est_save = 0;
  MLV_Image *images[NUM_IMAGES], *croix[NUM_CROIX];
  hms chrono;
  struct timespec debut, fin, maintenant, dernier_avancement;
  
  ini_chrono( &chrono);
  MLV_clear_window(MLV_COLOR_BEIGE);
  clock_gettime( CLOCK_REALTIME, &dernier_avancement );
  charger_croix( croix );
  charger_img( images );
  
  while(1){

    dest = 0;
    /* permet de gerer le framrate */
    clock_gettime( CLOCK_REALTIME, &debut );

    /* permet de gérer le temps passer entre chaque avancement */
    clock_gettime( CLOCK_REALTIME, &maintenant );


    if( pause_jeu(je, gr, tpoyo, ptmp) == 0){
      return ;
    }
      
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
      est_save = 0;
      roulement_poyo(tpoyo, gr);
    }
    temps_ecoule = (maintenant.tv_sec - dernier_avancement.tv_sec) * 1000 + (maintenant.tv_nsec - dernier_avancement.tv_nsec) / 1000000;
        
    /* gestion de la vitesse de chutte des pieces */
    if (temps_ecoule >= vitesse) {
      avancement_piece(&tpoyo[0], gr);
      dernier_avancement = maintenant;
    }

    /* affichage de la grille et des poyos */
    aff_etat(*gr, *je, chrono, tpoyo[0], images, croix);
    aff_poyos(tpoyo, ptmp, images);

    deplacement(&tpoyo[0], gr);
    *ptmp = sauvegarde_poyos(tpoyo, *ptmp, gr, &est_save);
    
    actualisation_poyo(&tpoyo[0], gr);

    /* principe des coordonnées, destruction et destrucion */
    tmpscore = chute_et_destruction(&tpoyo[0], gr);
    if( tmpscore > 0 ){
      dest = 1;
      calcule_score(tmpscore, je, chrono);
    }

    /* on verifie que la partie n'est pas fini */
    if( fin_solo( tpoyo[0], *je, *gr, dest) == 1){
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
    

  liberer_images(images);
}


void jeu_1vs1(grille *gr1, grille *gr2, joueur *je1, joueur *je2, c_poyo tpoyo1[4], c_poyo tpoyo2[4]){
    int temps, duree, tmpscore1 = 0, tmpscore2 = 0, vitesse, temps_ecoule, dest1, dest2, est_save1 = 0, est_save2 = 0;
    c_poyo ptmp1, ptmp2;
    hms chrono;
    MLV_Image *images[NUM_IMAGES_1VS1], *croix[NUM_CROIX];
    struct timespec debut, fin, maintenant, dernier_avancement;

    chrono.milis = 0;
    chrono.secondes = 0;
    chrono.minutes = 0;
    chrono.heures = 0;
  
    initialisation_cpoyo_vide(&ptmp1);
    initialisation_cpoyo_vide(&ptmp2);
    MLV_clear_window(MLV_COLOR_BLACK);
    clock_gettime( CLOCK_REALTIME, &dernier_avancement );
    charger_croix( croix );
    charger_img_1vs1( images );
    
    while(1){
      /* permet de gerer le framrate */
      clock_gettime( CLOCK_REALTIME, &debut );
      
      dest1 = 0;
      dest2 = 0;

      if( pause_jeu_1vs1() == 0){
	return ;
      }

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
            est_save1 = 0;
        }

        if( tpoyo2[0].p1.pos == 1 && tpoyo2[0].p2.pos == 1 ){
            roulement_poyo(tpoyo2, gr2);
            est_save2 = 0;
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
        aff_1vs1_etat( *gr1, *gr2, *je1, *je2, chrono, tpoyo1[0], tpoyo2[0], images, croix );
    
        /* aff_poyos(tpoyo, &ptmp); */
        aff_1vs1_poyos(tpoyo1, tpoyo2, &ptmp1, &ptmp2, images);

        deplacement_j1(&tpoyo1[0], gr1);
        deplacement_j2(&tpoyo2[0], gr2);
    
        ptmp1 = sauvegarde_poyos_j1(tpoyo1, ptmp1, gr1, &est_save1);
        ptmp2 = sauvegarde_poyos_j2(tpoyo2, ptmp2, gr2, &est_save2);
        
        actualisation_poyo(&tpoyo1[0], gr1);
        actualisation_poyo(&tpoyo2[0], gr2);

        /* principe des coordonnées, destruction et destrucion */
        tmpscore1 = chute_et_destruction(&tpoyo1[0], gr1);
        tmpscore2 = chute_et_destruction(&tpoyo2[0], gr2);

    
        if( tmpscore1 > 0 ){
            dest1 = 1;
            appliquer_malus(tmpscore1, gr2, &tpoyo2[0]);
            calcule_score(tmpscore1, je1, chrono);   
        }
        if( tmpscore2 > 0 ){
            dest2 = 1;
            appliquer_malus(tmpscore2, gr1, &tpoyo1[0]);
            calcule_score(tmpscore2, je2, chrono);   
        }
        
        if( fin_1vs1( tpoyo1[0], tpoyo2[0], *je1, *je2, *gr1, *gr2, dest1, dest2) == 1){
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
    liberer_images_1vs1(images);

}
