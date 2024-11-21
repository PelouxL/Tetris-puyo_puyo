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

void jeu(grille *gr, joueur *je, c_poyo tpoyo[4]){
    int taille_tcord1 = 0, taille_tcord2 = 0, temps, duree , nb_dest1 = 0, nb_dest2 = 0;
    coordonne tcord1[100],tcord2[100];
    c_poyo ptmp;
    
    struct timespec debut, fin, maintenant, dernier_avancement;

    initialisation_cpoyo_vide(&ptmp);
    aff_jeu();
   
  
    clock_gettime( CLOCK_REALTIME, &dernier_avancement );
  
    while(1){
        /* permet de de gerer le framrate */
        clock_gettime( CLOCK_REALTIME, &debut );

        /* permet de gérer le temps passer entre chaque avancement */
        clock_gettime( CLOCK_REALTIME, &maintenant );

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
    
        /* aff_grille(*gr); */
        aff_etat(*gr, *je);
        aff_poyos(tpoyo, &ptmp);
    
        printf("\n");

        deplacement(&tpoyo[0], gr);
        ptmp = sauvegarde_poyos(tpoyo, ptmp, gr);
    
        affiche_c_poyo(&tpoyo[0]);
        actualisation_poyo(&tpoyo[0], gr);

        /* principe des coordonnées et de la destruction */
        if(tpoyo[0].p1.pos == 1 && tpoyo[0].p2.pos == 1 ){
            nb_dest1 = 0;
            nb_dest2 = 0;
            taille_tcord1 = recup_coord(&tpoyo[0].p1, gr, tcord1);           
            nb_dest1 = destruction(tcord1, gr, taille_tcord1);
            taille_tcord2 = recup_coord(&tpoyo[0].p2, gr, tcord2);
            nb_dest2 = destruction(tcord2, gr, taille_tcord2);
            

            /* verifie que si l'on detruit des poyos alors une chute se fait*/
            if( nb_dest1 > 0 || nb_dest2 > 0){
                chutte_destruction(gr);
                /* cette boucle permet de detruire tout les nouveau groupe causer par une chute */
                while( post_destruction(gr)){
                    MLV_wait_milliseconds(200);
                }
            }
 
        }
    

        clock_gettime(CLOCK_REALTIME, &fin );
    
        /* Framerate */
        duree = ((fin.tv_sec - debut.tv_sec) * 1000) + ((fin.tv_nsec - debut.tv_nsec) / 1000000);
        temps = 41 - duree ;
        if(temps > 0){
            MLV_wait_milliseconds(temps);
        }
        if(temps > 50){
            printf("%d\n", temps);
        }
        MLV_actualise_window();
    }
    
}
