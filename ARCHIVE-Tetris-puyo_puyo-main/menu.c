#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "ini_poyo.h"
#include "jeu.h"
#include "affichage_mlv.h"
#include "destruction.h"


int verif(bouton bouton, int coord_x, int coord_y){
    if((coord_x > bouton.x && coord_x < bouton.x + bouton.largeur) && (coord_y > bouton.y && coord_y < bouton.y + bouton.hauteur)){
        return 1;
    }
    return 0;
}



void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police){
    int largeur, hauteur;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &largeur, &hauteur);
    bouton -> x = x - largeur/2;
    bouton -> y = y;
    bouton -> hauteur = hauteur;
    bouton -> largeur = largeur;
    strcpy(bouton -> txt, message);    
}

void afficher_text(bouton bouton , MLV_Font *police){
    MLV_draw_adapted_text_box_with_font(bouton.x, bouton.y, bouton.txt, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}



void menu(bouton t_bouton_menu[4]){
    char *nom_bouton[4] = {"START", "SAVE", "SCORE", "EXIT"}; 
    int text_width, text_height, i;
    MLV_Font *police;

    MLV_clear_window(MLV_COLOR_BEIGE);

    police = MLV_load_font("squaretype_b.ttf", 90);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("PUYO PUYO", police, 10, &text_width, &text_height); /* on récup la taille du texte écrit avec la largueur (width) et la hauteur (height) je traduis on sait jamais :) */
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3 /* pour le mettre en haut */, "PUYO PUYO", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    police = MLV_load_font("squaretype_b.ttf", 60); /* je change la taille du texte pour faire une diff avec le titre */

    /* bouton menu départ */
    for( i = 0 ; i < 4 ; i++ ){
        cree_bouton(&t_bouton_menu[i], nom_bouton[i], LX / 2, 200 + i * 100, police); /* le 200 c'est pour faire commencer en dessous du titre et le 100 c'est le décalage entre les boutons */
        afficher_text(t_bouton_menu[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}



void menu_save(bouton t_bouton_save[5]){
    char *nom_bouton_save[5] = {"SAVE 1", "SAVE 2", "SAVE 3", "SAVE 4", "BACK"};
    int text_width, text_height, i;
    MLV_Font *police;
        
    MLV_clear_window(MLV_COLOR_BEIGE);

    police = MLV_load_font("squaretype_b.ttf", 90);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("SAVE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 4, "SAVE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    police = MLV_load_font("squaretype_b.ttf", 50);
    
    /* bouton save */
    for( i = 0 ; i < 5 ; i++){
        cree_bouton(&t_bouton_save[i], nom_bouton_save[i], LX / 2, 150 + i * 100, police);
        afficher_text(t_bouton_save[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}


int charger_save(char *nom, joueur *jr, grille *gr){
    FILE * f;
    int i, j;
    if((f = fopen(nom, "r")) == NULL){
        printf("Erreur ouverture f \n");
        return -1;
    }

    if (fscanf(f, "%s %d", jr -> pseudo, &jr -> score) != 2){
        printf("Erreur : lecture pseudo ou score \n");
        fclose(f);
        return -1;
    }
    
    if(fscanf(f, "%d %d %d ", &gr -> n, &gr -> m, &gr -> niveau) != 3){
        printf("Erreur lecture dimension grille \n");
        fclose(f);
        return -1;
    }

    for( i = 0; i < gr -> n; i++){
        for( j = 0; j < gr -> m; j++){
            if(fscanf(f, "%d,", &gr -> mat[i][j]) != 1){
                printf("Erreur lecture case \n");
                fclose(f);
                return -1;
            }
        }
    }
    fclose(f);
    return 1;
}

int save_partie(char *nom, joueur *jr, grille *gr){
    FILE *f;
    int i, j;
    if((f = fopen(nom, "w")) == NULL){
        return -1;
    }

    fprintf(f, "%s\n", jr -> pseudo);
    fprintf(f, "%d\n", jr -> score);

    fprintf(f, "%d %d %d\n", gr -> n, gr -> m, gr -> niveau);

    for( i = 0; i < gr -> n; i++){
        for( j = 0; j < gr -> m; j++){
            fprintf(f, "%d ", gr -> mat[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 1;
}  

void menu_score(bouton *retour){
    char *nom_bouton_score[10] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"};
    int scores[10] = {1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009};
    char affichage[100];
    char *pseudos[10] = {"Feur1", "Feur2", "Feur3", "Feur4", "Feur5", "Feur6", "Feur7", "Feur8", "Feur9", "Feur10"};
    char *nom_bouton_retour[1] = {"RETOUR"};
    int text_width, text_height, i, k;
    MLV_Font *police;

    MLV_clear_window(MLV_COLOR_BEIGE);

    /* Police */
    police = MLV_load_font("squaretype_b.ttf", 40);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("MEILLEURS SCORES", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "MEILLEURS SCORES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    
    police = MLV_load_font("squaretype_b.ttf", 30);

    k = 0;
    
    for( i = 0 ; i < 10 ; i++ ){
        sprintf(affichage, "%s   // Score =  %d //  Pseudo = %s", nom_bouton_score[i], scores[i], pseudos[i]);
        MLV_get_size_of_adapted_text_box_with_font(affichage, police, 10, &text_width, &text_height);
        MLV_draw_adapted_text_box_with_font( LX / 5, text_height / 3 + 80 + k, affichage, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
        k += 55;
    }

    police = MLV_load_font("squaretype_b.ttf", 30);

    cree_bouton(retour, nom_bouton_retour[0],
                60, /* pour pas que le bouton retour soit trop à gauche */
                0, /* pour la hauteur, pas besoin d'en mettre pour que ce soit tout en haut*/
                police);
    afficher_text(*retour, police);

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_pause(bouton t_bouton_pause[3]){
    char *nom_bouton_pause[3] = {"RESTART", "SAVE", "QUIT"};
    MLV_Font *police;
    int text_width, text_height, i;

    MLV_clear_window(MLV_COLOR_BEIGE);
    police = MLV_load_font("squaretype_b.ttf", 90);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("PAUSE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "PAUSE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
        
    police = MLV_load_font("squaretype_b.ttf", 50);
        
    /* bouton pause */
    for( i = 0 ; i < 3 ; i++){
        cree_bouton(&t_bouton_pause[i], nom_bouton_pause[i], LX / 2, 150 + i * 100, police);
        afficher_text(t_bouton_pause[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

int clic_bouton(bouton t_bouton[], int longueur){
    int i, s_x, s_y;

    MLV_wait_mouse(&s_x, &s_y);
    for(i = 0; i < longueur; i++){
        if(verif(t_bouton[i], s_x, s_y)){
            return i;
        }
    }
    return -1;
}

void fonctionnement(){
    bouton t_bouton_menu[4], t_bouton_save[5];
    bouton retour;
    int pressed; /* bouton pressé */
    int n = 10, m = 8, ok = 1;
    int retour_menu_p = 1;
    int pause = 1;
    grille gr;
    joueur j;
    c_poyo tpoyo[4];


    menu(t_bouton_menu);

    while(ok == 1){
        menu(t_bouton_menu);
        pressed = clic_bouton(t_bouton_menu, 4);

        switch(pressed){
        case 0:
            printf("Début jeu \n");
            gr = initialisation_grille(n, m);
            ini_poyo_chaine(tpoyo, 4);
            jeu(&gr, &j, tpoyo);
            

            /*             pressed = clic_bouton(t_bouton_pause, 3); */
            /*             if(pressed == 0){ */
            /*                 gr = initialisation_grille(n, m); */
            /*                 ini_poyo_chaine(tpoyo, 4); */
            /*             } */
            /*             else if(pressed == 1){ */
            /*                 printf("Save \n"); */
            /*             } */
            /*             else if(pressed == 2){ */
            /*                 printf("Au revoir \n"); */
            /*                 MLV_free_window(); */
            /*                 exit(EXIT_SUCCESS); */
            /*             } */
            /*             pause = 1; */
            /*         } */
            /*     } */
            /* } */
            
            /* while(1){ */
            /*     if(pause == 1){ */
            /* /\*         if( MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED){ *\/ */
            /* /\*             printf("FEUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUURS \n"); *\/ */
            /* /\*             pause = 0; *\/ */
            /* /\*             MLV_clear_window(MLV_COLOR_BEIGE); *\/ */
            /* /\*             menu_pause(t_bouton_pause); *\/ */
                        
            /* /\*         } *\/ */
            /* /\*     } *\/ */
            /*         jeu(&gr, &j, tpoyo); */

            /*         event = MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); */
            /*         if(event == MLV_KEY){ */
            /*             if(touche == MLV_KEYBOARD_ESCAPE){ */
            /*                 pause = 0; */
            /*                 MLV_clear_window(MLV_COLOR_BEIGE); */
            /*                 menu_pause(t_bouton_pause); */
            /*                 MLV_actualise_window(); */
            /*             } */
            /*         } */
            /*     } */
            /*     else { */
                    
                    /*  if(pause == 0){ */
                   /*  pressed = clic_bouton(t_bouton_save, 3); */
            /*         MLV_actualise_window(); */
                    
            /*         if(pause == 0){ */
            /*             pause = 1; */
            /*         } */
            /*         else if(pressed == 1){ */
            /*             printf("on enregistre \n"); */
            /*         } */
            /*         else if(pressed == 2){ */
            /*             menu(t_bouton_menu); */
            /*         } */
            /*     } */
            /* } */
            
            break;
            
        case 1:
            printf("Menu save \n");
            menu_save(t_bouton_save);
            while(retour_menu_p == 1){
                pressed = clic_bouton(t_bouton_save, 5);
                MLV_actualise_window();
                                  
                if(pressed == 0){
                    printf("Save 1 \n");
                    if(charger_save("save1.txt", &j, &gr) == 1){
                        ini_poyo_chaine(tpoyo, 4);
                        jeu(&gr, &j, tpoyo);
                    }
                }
                else if(pressed == 1){
                    printf("Save 2 \n");
                    if(charger_save("save2.txt", &j, &gr) == 1){
                        ini_poyo_chaine(tpoyo, 4);
                        jeu(&gr, &j, tpoyo);
                    }
                }
                else if(pressed == 2){
                    printf("Save 3 \n");
                    if(charger_save("save3.txt", &j, &gr ) == 1){
                        ini_poyo_chaine(tpoyo, 4);
                        jeu(&gr, &j, tpoyo);
                    }
                }
                else if(pressed == 3){
                    printf("Save 4 \n");
                    if(charger_save("save4.txt", &j, &gr) == 1){
                        ini_poyo_chaine(tpoyo, 4);
                        jeu(&gr, &j, tpoyo);
                    }
                }
                else if(pressed == 4){
                    printf("Menu p \n");
                    retour_menu_p = 0;
                }
            }
                
                /* pressed = clic_bouton(&retour, 1); */
                /* if(pressed == 0){ */
                /*     retour_menu_p = 0; */
                /* } */
            /* } */
            break;
            
        case 2:
            printf("Menu score \n");
            menu_score(&retour);
            while(retour_menu_p == 1){
                pressed = clic_bouton(&retour, 1);
                if(pressed == 0){
                    retour_menu_p = 0;
                }
            }
            break;
        case 3:
            printf("Au revoir \n");
            MLV_free_window();
            exit(EXIT_SUCCESS);
        }
        retour_menu_p = 1;
    }
    MLV_free_window();  
}
